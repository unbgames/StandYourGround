#include "../include/Tree.h"
#include "../include/InputManager.h"

Tree::Tree(GameObject& associated) : Component(associated), hp(100), hitable(false), timeToLoseHp(0.35) {
}

void Tree::Update(float dt) {
    InputManager& inp = InputManager::GetInstance();
    if(inp.IsKeyDown(SPACE_KEY)) {
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
    
    if(hp <= 0) {
        associated.RequestDelete();
    }
    hitable = false;
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
        hitable = true;
    }
}