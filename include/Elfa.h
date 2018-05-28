#ifndef ELFA_H
#define ELFA_H

#include "GameObject.h"
#include "Component.h"
#define VELOCIDADE 3

class Elfa : public Component{
    public:
        Elfa(GameObject& associated);
        ~Elfa();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        std::string Type();
        void NotifyCollision(GameObject &other);
        
        std::string GetState();

        static Elfa* elfa;
    private:
        int hp;
        std::string direction; // esquerda ou direita
        std::string facing; // costa ou frente
        std::string movement; // idle ou run
};

#endif