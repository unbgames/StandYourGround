#ifndef SIDE_ITEM_BAR_H
#define SIDE_ITEM_BAR_H

#include "Text.h"
#include "Component.h"
#include "Sprite.h"

class SideItemBar : public Component {
    public:
        SideItemBar(GameObject& associated);

        void Update(float dt);
        void Render();
        bool Is(std::string type);
        std::string Type();
        void NotifyCollision(GameObject &other);
    private:
        int berry;
        Text* berryAmount;

        int cipo;
        Text* cipoAmount;

        int galho;
        Text* galhoAmount;

        std::vector<GameObject*> itemList;
        std::vector<Sprite*> spriteItemList;
        std::vector<Text*> textItemList;
};

#endif