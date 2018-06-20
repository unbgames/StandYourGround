#ifndef ITEM_H
#define ITEM_H

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"

enum  ItemType {
    cipo,
    berry,
    galho,
    flor,
};

class Item : public Component {
    public:
        Item(GameObject& associated, ItemType type);

        void Update(float dt);
        void Render();
        bool Is(std::string type);
        std::string Type();
        void NotifyCollision(GameObject &other);
        ItemType type;
    private:
        std::string name;
        bool pickable;
        Sprite* pick;
};

#endif