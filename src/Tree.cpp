#include "../include/Tree.h"
#include "../include/InputManager.h"
#include "../include/Sprite.h"
#include "../include/Elfa.h"
#include "../include/Game.h"

Tree::Tree(GameObject& associated) : Component(associated), hp(100), hitable(false), timeToLoseHp(0.1*5) {
    Sprite *treeSprite = new Sprite(associated, "./assets/map/tilemap_arvore_v2.png", 5, 0);
    treeSprite->SetScale({4, 4});
    treeSprite->SetFrame(3);
    associated.AddComponent(treeSprite);
    associated.box.SetSize(treeSprite->GetWidth(), treeSprite->GetHeight());
    AddSound("chopp", "./assets/audio/chopp.mp3");
}
Tree::~Tree() {
}

void Tree::Update(float dt) {
    InputManager& inp = InputManager::GetInstance();
    if(inp.IsKeyDown(SPACE_KEY) && hitable) {
        hitTime.Update(dt);
        if(hitTime.Get() > timeToLoseHp) {
            hitTime.Restart();
            hp -= 20;
            std::cout << "ARVORE TOMOU 20 DE DANO, RESTA " << hp << std::endl;

            Vec2 treePos = associated.box.Origin();
            Elfa* elfaPtr = Elfa::elfa;
            Vec2 elfPos = elfaPtr->Origin();
            int reducer = int(std::pow(Vec2::EuclidianDist(treePos, elfPos), 2) / 4000);
            // int reducer = int(Vec2::EuclidianDist(orcPos, elfPos) / 5);
            // std::cout<<"PLAY SOUND at "<< reducer <<std::endl;

            PlaySound("chopp", 128 - std::min(reducer, 128));

        }
    }
    else {
        hitTime.Restart();
    }

    const Rect &rect = associated.box;
    auto sprite = (Sprite *) associated.GetComponent("Sprite");
    if (rect.Contains(Elfa::elfa->BottomLeft()) || rect.Contains(Elfa::elfa->BottomRight())) {
        sprite->Opacity(50);
    } else {
        sprite->Opacity(100);
    }

    if(hp <= 0) {
        associated.RequestDelete();
        auto &state = Game::GetInstance().GetCurrentState();
        auto expObj = std::make_shared<GameObject>();
        Sprite *expSpr = new Sprite(*expObj, "./assets/img/penguindeath.png", 5, 100, 10);
        expObj->box.SetSize(expSpr->GetWidth(), expSpr->GetHeight());
        expObj->box.SetCenter(associated.box.Center());
        Sound *expSnd = new Sound(*expObj, "./assets/audio/boom.wav");
        expObj->AddComponent(expSpr);
        expObj->AddComponent(expSnd);
        state.AddObject(expObj);
        expSnd->Play();
        std::cout << "BOOM" << std::endl;
    }
    //hitable = false;
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
        std::cout << "COLIDIU" << std::endl;
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
