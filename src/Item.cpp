#include "../include/Item.h"
#include "../include/InputManager.h"

Item::Item(GameObject& associated) : Component(associated), pickable(false) {

}

void Item::Update(float dt) {
    if(pickable) {
        std::cout << "PICKABLE" << std::endl;
        InputManager& inp = InputManager::GetInstance();
        if(inp.IsKeyDown(SDLK_e)) {
            std::cout << "Delete";
            associated.RequestDelete();
        }
    }
    pickable = false;
}

void Item::Render() {
    
}

bool Item::Is(std::string type) {
    return type == "Item";
}

std::string Item::Type() {
    return "Item";
}

void Item::NotifyCollision(GameObject &other) {
    if(other.GetComponent("Elfa") != nullptr) {
        pickable = true;
    }
}