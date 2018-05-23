#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

#include <SDL2/SDL.h>

#include "Component.h"
#include "GameObject.h"
#include "Rect.h"
#include "Timer.h"

#define COOLDOWN 0.5

class PenguinCannon : public Component {
public:
    PenguinCannon(GameObject &associated, GameObject &penguinBody);
    ~PenguinCannon();

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    std::string Type();
    void Shoot();
    void NotifyCollision(GameObject &other);

private:
    GameObject &pbody;
    float angle;
    Timer timer;
};

#endif /* PENGUINCANNON_H */
