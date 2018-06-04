#ifndef TREE_H
#define TREE_H

#include "Component.h"
#include "GameObject.h"

class Tree : public Component {
    public:
        Tree(GameObject& associated);

        void Update(float dt);
        void Render();
        bool Is(std::string type);
        std::string Type();
        void NotifyCollision(GameObject &other);
    private:
        int hp;
};

#endif