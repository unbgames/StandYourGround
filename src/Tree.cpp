#include "../include/Tree.h"
#include "../include/InputManager.h"
#include "../include/Sprite.h"
#include "../include/Elfa.h"

Tree::Tree(GameObject& associated) : Component(associated), hp(100), hitable(false), timeToLoseHp(0.35) {
    Sprite *treeSprite = new Sprite(associated, "./assets/map/tilemap_arvore_v2.png", 5, 0);
    treeSprite->SetScale({4, 4});
    treeSprite->SetFrame(3);
    associated.AddComponent(treeSprite);
    associated.box.SetSize(treeSprite->GetWidth(), treeSprite->GetHeight());
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
