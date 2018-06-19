#include "../include/MenuItem.h"

MenuItem::MenuItem(GameObject& associated, std::string option, std::function<void()> func) : text(new Text(associated, 
                                                                "./assets/font/Call me maybe.ttf", 
                                                                50, TextStyle::SOLID, option, {0, 0, 0, 0})), 
                                                                action(func) , option(option){

}

void MenuItem::Selected() {
    text->SetColor({0, 0, 0, 0});
}

void MenuItem::Deselected() {
    text->SetColor({1, 1, 0, 0});
}

void MenuItem::Chosen() {
    this->action();
}