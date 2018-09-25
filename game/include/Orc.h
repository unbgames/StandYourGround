#ifndef ORC_H
#define ORC_H

#include "Character.h"
#include "Timer.h"
#include "Forest.h"
#include "Trap.h"

class Orc : public Character {
public:
    Orc(GameObject& associated);
    ~Orc();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    std::string Type();
    void NotifyCollision(GameObject &other);

    static Orc* orc;

private:
    Timer footstepTimer;
    Timer chopTimer;
    std::weak_ptr<GameObject> tree_w;
    Forest* forest;
    bool hitTree;
    bool hitTotem;
    bool firstHit;

    bool onTrap;
    bool prevOnTrap;
    Trap *trap;

    int damage;
};

#endif /* ORC_H */
