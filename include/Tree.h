#ifndef TREE_H
#define TREE_H

#include "Timer.h"
#include "Component.h"
#include "GameObject.h"
#include "Sound.h"

#include <map>

class Tree : public Component {
    public:
        Tree(GameObject& associated);
        ~Tree();

        void Update(float dt);
        void Render();
        bool Is(std::string type);
        std::string Type();
        void NotifyCollision(GameObject &other);
    private:
        int hp;
        bool hitable; // Se o orc consegue bater na arvore
        float timeToLoseHp;
        Timer hitTime;
        std::map<std::string, Sound*> soundMap;

        void AddSound(const std::string &key, const std::string &file);
        void PlaySound(const std::string &key, int volume = 128);
};

#endif
