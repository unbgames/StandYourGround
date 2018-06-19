#include "../include/Menu.h"
#include "../include/InputManager.h"

Menu::Menu(GameObject& associated) : Component(associated), selection(0) {
    associated.box.SetSize(200, 300);
    associated.box.SetOrigin(400, 400);
}

void Menu::AddOption(MenuItem* item) {
    items.emplace_back(item);
}

void Menu::Update(float dt) {
    InputManager& inp = InputManager::GetInstance();
    items[selection]->Deselected();
    if(inp.KeyPress(UP_ARROW_KEY)) {
        selection = selection > 0 ? --selection : 0;
    }
    else if(inp.KeyPress(DOWN_ARROW_KEY)) {
        selection = selection < items.size() - 1 ? ++selection : selection;
    }
    items[selection]->Selected();
    if(inp.KeyPress(SDLK_KP_ENTER)) {
        items[selection]->Chosen();
    }
}

void Menu::Render() {
    for(int i = 0; i < items.size(); i++) {
        items[i]->text->Render();
    }
}

bool Menu::Is(std::string type) {
    return type == "Menu";
}

std::string Menu::Type() {
    return "Menu";
}

void Menu::NotifyCollision(GameObject &other) {

}