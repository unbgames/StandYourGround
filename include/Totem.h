#ifndef TOTEM_H
#define TOTEM_H

#include "Timer.h"
#include "Forest.h"
#include "Trap.h"

class Totem : public Component {
public:
    Totem(GameObject& associated, int trees, int health = 300);
    ~Totem();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    std::string Type();
    void NotifyCollision(GameObject &other);
    void alertTreeFall();
    bool canAttack() const;
    Vec2 Center() const;
    void Damage(int damage);
    bool IsDead() const;

    static Totem* totem;

private:
    Timer chopTimer;
    int health;
    int trees;

    void AddSound(const std::string &key, const std::string &file);
    void PlaySound(const std::string &key, int volume = 128);
};

#endif /* TOTEM_H */
