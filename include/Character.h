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

enum class Action {
    no_action,
    atq,
    pick,
    cast
};

typedef struct CharState {
    Direction dir;
    Facing face;
    Movement move;
    Action act;

    CharState& operator=(const CharState& a)
    {
       dir = a.dir;
       face = a.face;
       move = a.move;
       act = a.act;
       return *this;
   };

    bool operator==(const CharState& a) const
    {
        return (dir == a.dir && face == a.face &&  move == a.move && act == a.act);
    };
    bool operator!=(const CharState& a) const
    {
        return !(dir == a.dir && face == a.face &&  move == a.move && act == a.act);
    };
} CharState;

class Character : public Component {
public:
    Character(GameObject& associated, const CharState &state);
    CharState GetState() const;

    bool Is(std::string type);
    std::string Type();
    void Render();
    void Update(float dt);

    static std::string StateToString(const CharState &state);
    Vec2 Origin() const;
    Vec2 BottomLeft() const;
    Vec2 BottomRight() const;
    void HideSprite(bool hide);

protected:
    int hp;
    float speed;
    CharState state;
    std::map<std::string, Sound*> soundMap;

    void AddSound(const std::string &key, const std::string &file);
    void PlaySound(const std::string &key, int volume = 128);

    float velX, velY;
    Rect oldBox;
};

#endif /* CHARACTER_H */
