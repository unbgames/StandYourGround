#ifndef MINION_H
#define MINION_H

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

#include <queue>
#include <memory>
#include <random>

class Minion : public Component {
public:
    Minion(GameObject &associated, GameObject &alienCenter, float arcOffsetDeg  = 0);
    ~Minion();

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    std::string Type();
    void Shoot(Vec2 pos);
    void NotifyCollision(GameObject &other);

private:
    GameObject &alienCenter;
    float arc;
    std::random_device randDevice;
    std::mt19937 randGen;
};

#endif /* MINION_H */
