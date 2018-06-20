#include "../include/MenuItem.h"

MenuItem::MenuItem(GameObject& associated, std::string option, std::function<void()> func) : text(new Text(associated, 
                                                                "./assets/font/pixel.ttf", 
                                                                80, TextStyle::SOLID, option, {0, 0, 0, 255})), 
                                                                action(func) , option(option){

}

void MenuItem::Selected() {
    text->SetColor({255, 0, 0, 255});
}

void MenuItem::Deselected() {
    text->SetColor({0, 0, 0, 255});
}

void MenuItem::Chosen() {
    std::cout << "Escolheu: " << option << std::endl;
    this->action();
}

void MenuItem::Render() {
    text->RenderNoCam();
}

float MenuItem::GetTextWidth() {
    return text->GetBox().GetW();
}