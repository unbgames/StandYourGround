#include "../include/Item.h"
#include "../include/InputManager.h"
#include "../include/Bag.h"

Item::Item(GameObject& associated, ItemType type) : Component(associated), 
                                     pickable(false),
                                     pick(new Sprite(associated, "./assets/img/items/pickable.png")), type(type) {
    pick->SetScale({0.2, 0.2});
    pick->SetOffset({associated.box.GetW()/2 - 10, -(associated.box.GetH()/2 + 30)});
    associated.AddComponent(pick);
    pick->Hide();
}

void Item::Update(float dt) {
    if(pickable) {
        InputManager& inp = InputManager::GetInstance();
        if(inp.KeyPress(SDLK_e)) {
            std::cout << "Picked Item" << std::endl;
            Bag::PickItem(type);
            associated.RequestDelete();
        }
    }
    pickable = false;
    pick->Hide();
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
        pick->Show();
    }
}