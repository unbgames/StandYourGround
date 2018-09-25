#ifndef MENU_H
#define MENU_H

#include "Component.h"
#include "MenuItem.h"

class Menu : public Component {
    public:
        Menu(GameObject& associated);
        void AddOption(std::string option, std::function<void()> func);

        void Update(float dt);
        void Render();
        bool Is(std::string type);
        std::string Type();
        void NotifyCollision(GameObject &other);
    private:
        int selection;
        float nextOptionPosition;
        std::vector<MenuItem*> items;
};

#endif
