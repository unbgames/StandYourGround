#ifndef BOMB_H
#define BOMB_H

#include "Trap.h"

class Bomb : public Trap {
public:
    Bomb(GameObject &associated);
    ~Bomb();
    Vec2 GetShiftAfter() const;
    bool ShouldHide() const;
    void Update(float dt);
    void StopTrap();

    Rect box;
private:
    float duration;
};

#endif /* BOMB_H */
