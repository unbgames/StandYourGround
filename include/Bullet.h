#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

#include <queue>
#include <memory>

class Bullet : public Component {
public:
    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, bool targetsPlayer = false);
    ~Bullet();

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    std::string Type();
    int GetDamage();
    void NotifyCollision(GameObject &other);

    bool targetsPlayer;
private:
    Vec2 speed;
    int damage;
    float distanceLeft;
};

#endif /* BULLET_H */
