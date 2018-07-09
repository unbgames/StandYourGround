#ifndef HUD_H
#define HUD_H

#include "Component.h"
#include "GameObject.h"
#include "Elfa.h"
#include "GameTimer.h"

class HUD : public Component {
    public:
        HUD(GameObject& associated, Elfa* player);

        void Update(float dt);
        void Render();
        bool Is(std::string type);
        std::string Type();
        void NotifyCollision(GameObject &other);

        bool GameOver();
    private:
        Elfa* player;
        GameTimer* timer;

        std::vector<GameObject*> hudComponents;
};

#endif