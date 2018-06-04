#ifndef ITEM_H
#define ITEM_H

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"

class Item : public Component {
    public:
        Item(GameObject& associated);

        void Update(float dt);
        void Render();
        bool Is(std::string type);
        std::string Type();
        void NotifyCollision(GameObject &other);
    private:
        std::string name;
        bool pickable;
        Sprite* pick;
};

#endif