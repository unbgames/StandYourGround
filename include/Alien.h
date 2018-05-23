#ifndef ALIEN_H
#define ALIEN_H

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"

#include <queue>
#include <memory>

#define ALIEN_SPEED 5.0
#define ALIEN_WAIT 3.0

class Alien : public Component {
public:
    Alien(GameObject &associated, int nMinions);
    ~Alien();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    std::string Type();
    void NotifyCollision(GameObject &other);

    static int alienCount;

private:
    enum AlienState { MOVING, RESTING };
    AlienState state = AlienState::RESTING;
    Timer timer;
    Vec2 destination;
    int nMinions;
    Vec2 speed;
    int hp;
    std::vector<std::weak_ptr<GameObject>> minionArray;
};

#endif /* ALIEN_H */
