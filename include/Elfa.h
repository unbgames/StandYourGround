#ifndef ELFA_H
#define ELFA_H

#include "Timer.h"
#include "Character.h"

class Elfa : public Character {
public:
    Elfa(GameObject& associated);
    ~Elfa();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    std::string Type();
    void NotifyCollision(GameObject &other);

    static Elfa* elfa;

private:
    Timer timer;
};

#endif /* ELFA_H */
