#ifndef TOTEM_H
#define TOTEM_H

#include "Timer.h"
#include "Forest.h"
#include "Trap.h"
#include "Orc.h"

class Totem : public Component {
public:
    Totem(GameObject& associated);
    ~Totem();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    std::string Type();
    void NotifyCollision(GameObject &other);

    static Orc* orc;

private:
    Timer chopTimer;
    int damage;

    void AddSound(const std::string &key, const std::string &file);
    void PlaySound(const std::string &key, int volume = 128);
};

#endif /* TOTEM_H */
