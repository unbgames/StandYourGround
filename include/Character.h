#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "Component.h"
#include "Sound.h"

#include <map>

enum class Direction {
    esq,
    dir,
};

enum class Facing {
    up,
    down,
};

enum class Movement {
    idle,
    run,
};

typedef struct CharState {
    Direction dir;
    Facing face;
    Movement move;

    CharState& operator=(const CharState& a)
    {
       dir = a.dir;
       face = a.face;
       move = a.move;
       return *this;
   };

    bool operator==(const CharState& a) const
    {
        return (dir == a.dir && face == a.face &&  move == a.move);
    };
    bool operator!=(const CharState& a) const
    {
        return !(dir == a.dir && face == a.face &&  move == a.move);
    };
} CharState;

class Character : public Component {
public:
    Character(GameObject& associated, const CharState &state);
    CharState GetState() const;
    static std::string StateToString(const CharState &state);
    Vec2 Origin() const;

protected:
    int hp;
    float speed;
    CharState state;
    std::map<std::string, Sound*> soundMap;

    void AddSound(const std::string &key, const std::string &file);
    void PlaySound(const std::string &key, int volume = 128);

    float velX, velY;
};

#endif /* CHARACTER_H */
