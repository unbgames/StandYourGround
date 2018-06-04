#include "../include/Tree.h"

Tree::Tree(GameObject& associated) : Component(associated), hp(100) {

}

void Tree::Update(float dt) {

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

}