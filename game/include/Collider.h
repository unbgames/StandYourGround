#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vec2.h"
#include "Rect.h"
#include "GameObject.h"
#include "Component.h"
#include <memory>

class Collider : public Component{
public:
    Collider(GameObject &associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
    ~Collider();

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    std::string Type();
    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);

    Rect box;

private:
    Vec2 scale;
    Vec2 offset;
};

#endif /* COLLIDER_H */
