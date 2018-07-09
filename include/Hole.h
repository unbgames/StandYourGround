#ifndef HOLE_H
#define HOLE_H

#include "Trap.h"

class Hole : public Trap {
public:
    Hole(GameObject &associated);
    ~Hole();
    Vec2 GetShiftAfter() const;
    bool ShouldHide() const;
    void Update(float dt);
    void StopTrap();

    Rect box;
private:
    float duration;
};

#endif /* HOLE_H */
