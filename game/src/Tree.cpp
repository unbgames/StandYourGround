#include "Tree.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Elfa.h"
#include "Game.h"
#include "Forest.h"
#include "Sprite.h"
#include "config.h"

Tree::Tree(GameObject& associated, int type, int status) : Component(associated), hp((status+1)*20), hitable(false), timeToLoseHp(0.1*5) {
    // status += 1;
    std::string sprite;
    if (type == 0) {
        sprite = ASSETS_PATH("/map/arv1.png");
    } else {
        sprite = ASSETS_PATH("/map/arv2.png");
    }

    // std::cout <<"TYPE:"<<type<< " STATUS:"<<status << std::endl;
    treeSprite = new Sprite(associated, sprite , (type == 0)?4:5, 0);
    this->status = status;
    pickCipo = false;
    std::cout << status << std::endl;
    treeSprite->SetFrame(status);
    treeSprite->SetScale({4, 4});
    associated.AddComponent(treeSprite);
    associated.box.SetSize(treeSprite->GetWidth(), treeSprite->GetHeight());
    AddSound("chopp", ASSETS_PATH("/audio/chopp2.wav"));
    gotHit = false;
}
Tree::~Tree() {

}

void Tree::Update(float dt) {
    if(gotHit) {
        Vec2 treePos = associated.box.Origin();
        Elfa* elfaPtr = Elfa::elfa;
        Vec2 elfPos = elfaPtr->Origin();
        int reducer = int(std::pow(Vec2::EuclidianDist(treePos, elfPos), 2) / 4000);
        PlaySound("chopp", 128 - std::min(reducer, 128));
        gotHit = false;
    }

    const Rect &rect = associated.box;
    auto sprite = (Sprite *) associated.GetComponent("Sprite");
    if (rect.Contains(Elfa::elfa->BottomLeft()) || rect.Contains(Elfa::elfa->BottomRight())) {
        sprite->Opacity(50);
    } else {
        sprite->Opacity(100);
    }

    if(hp <= 0) {
        Forest::forest->alertDeleteTree(rect.Origin());
        associated.RequestDelete();
    }
    InputManager& inp = InputManager::GetInstance();
    if(pickCipo) {
        if(inp.KeyPress(SDLK_e)) {
            std::cout << "Picked Cipo From Tree" << std::endl;
            Bag::PickItem(ItemType::cipo);
            this->setStatus(2);
        }
    }
    if(inp.KeyPress(W_KEY) || inp.KeyPress(S_KEY) || inp.KeyPress(A_KEY) || inp.KeyPress(D_KEY))
        pickCipo = false;
}

void Tree::Damage(int damage) {
    gotHit = true;
    hp -= damage;
}
void Tree::Render() {
}

bool Tree::Is(std::string type) {
    return type == "Tree";
}

std::string Tree::Type() {
    return "Tree";
}

void Tree::NotifyCollision(GameObject &other) {
    if(other.GetComponent("Orc") != nullptr) {
        // std::cout << "COLIDIU" << std::endl;
        hitable = true;
    }
    if(other.GetComponent("Elfa") != nullptr) {
        if(GetStatus() == 3) {
            pickCipo = true;
        }
    }
}

void Tree::AddSound(const std::string &key, const std::string &file) {
    Sound *sound = new Sound(associated, file, true);
    if (sound == nullptr) {
        std::cerr << "Tried to add sound, but is problebly does not exists: " << file << std::endl;
        exit(-1);
    }
    associated.AddComponent(sound);
    soundMap[key] = sound;
}

void Tree::PlaySound(const std::string &key, int volume) {
    if (soundMap.find(key) != soundMap.end()) {
        soundMap[key]->SetVolume(volume);
        soundMap[key]->Play();
    } else {
        std::cerr << "Trying to play a sound not in the map: " << key << std::endl;
    }
}

void Tree::setStatus(int newStatus) {
    this->status = status;
    this->treeSprite->SetFrame(newStatus);
}

int Tree::GetStatus() {
    return status;
}
