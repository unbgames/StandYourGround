#ifndef ORC_H
#define ORC_H

#include "GameObject.h"
#include "Component.h"
#include "Timer.h"

const float ORC_VELOCITY = 100;

class Orc : public Component {
    public:
        Orc(GameObject& associated);
        ~Orc();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        std::string Type();
        void NotifyCollision(GameObject &other);
        
        std::string GetState();

        static Orc* orc;
    private:
        int hp;
        std::string direction; // esquerda ou direita
        std::string facing; // costa ou frente
        std::string movement; // idle ou run

        float velX, velY;
};

#endif