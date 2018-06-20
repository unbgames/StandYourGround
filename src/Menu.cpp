#include "../include/Menu.h"
#include "../include/InputManager.h"
#include "../include/Game.h"

Menu::Menu(GameObject& associated) : Component(associated), selection(0) {
    nextOptionPosition = SCREEN_HEIGHT*0.3;
}

void Menu::AddOption(std::string option, std::function<void()> func) {
    GameObject *goMenuItem = new GameObject();
    MenuItem* menuItem = new MenuItem(*goMenuItem, option, func);
    goMenuItem->layer = 2;
    goMenuItem->box.SetOrigin({SCREEN_WIDTH/2 - menuItem->GetTextWidth()/2, 
                               nextOptionPosition});
    items.emplace_back(menuItem);
    nextOptionPosition += 60;
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
    if(inp.KeyPress(SDLK_RETURN)) {
        items[selection]->Chosen();
    }
}

void Menu::Render() {
    for(int i = 0; i < items.size(); i++) {
        items[i]->Render();
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