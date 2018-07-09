#include "../include/Tree.h"
#include "../include/InputManager.h"
#include "../include/Sprite.h"
#include "../include/Elfa.h"
#include "../include/Game.h"
#include "../include/Forest.h"

Tree::Tree(GameObject& associated, int type, int status) : Component(associated), hp(status*30), hitable(false), timeToLoseHp(0.1*5) {
    std::string sprite;
    if (type == 0) {
        sprite = "./assets/map/tilemap_arvore_v2.png";
    } else {
        sprite = "./assets/map/tilemap_arvore_v2.png";
    }
    Sprite *treeSprite = new Sprite(associated, sprite , 5, 0);
    std::cout << status << std::endl;
    treeSprite->SetFrame(status);
    treeSprite->SetScale({4, 4});
    treeSprite->SetFrame(status);
    associated.AddComponent(treeSprite);
    associated.box.SetSize(treeSprite->GetWidth(), treeSprite->GetHeight());
    AddSound("chopp", "./assets/audio/chopp2.wav");
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
        // int reducer = int(Vec2::EuclidianDist(orcPos, elfPos) / 5);
        // std::cout<<"PLAY SOUND at "<< reducer <<std::endl;

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
        /*auto &state = Game::GetInstance().GetCurrentState();
        auto expObj = std::make_shared<GameObject>();
        Sprite *expSpr = new Sprite(*expObj, "./assets/img/penguindeath.png", 5, 0.1, 0.5);
        expObj->box.SetSize(expSpr->GetWidth(), expSpr->GetHeight());
        expObj->box.SetCenter(associated.box.Center());
        Sound *expSnd = new Sound(*expObj, "./assets/audio/boom.wav");
        expObj->AddComponent(expSpr);
        expObj->AddComponent(expSnd);
        state.AddObject(expObj);
        expSnd->Play();
        std::cout << "BOOM" << std::endl;*/
    }
    //hitable = false;
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
