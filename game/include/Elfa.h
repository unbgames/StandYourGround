#ifndef ELFA_H
#define ELFA_H

#include "Timer.h"
#include "Character.h"
#include "Bag.h"

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
    Timer picking;
    Timer casting;
    bool cast;

};

#endif /* ELFA_H */
