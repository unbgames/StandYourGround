#ifndef PENGUINBODY_H
#define PENGUINBODY_H

#include <SDL2/SDL.h>

#include "Component.h"
#include "GameObject.h"
#include "Rect.h"

#include <memory>

class PenguinBody : public Component {
public:
    PenguinBody(GameObject &associated);
    ~PenguinBody();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    std::string Type();
    void NotifyCollision(GameObject &other);

    static PenguinBody *player;

private:
    std::weak_ptr<GameObject> pcannon;
    Vec2 speed;
    const float linearSpeed;
    float angle;
    int hp;
};

#endif /* PENGUINBODY_H */
