#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>
#include <functional>
#include "GameObject.h"
#include "Text.h"

class MenuItem {
    public:
        MenuItem(GameObject& associated, std::string option, std::function<void()> func);
        void Selected();
        void Deselected();
        void Chosen();
        Text* text;
    private:
        std::string option;
        std::function<void()> action;
};

#endif