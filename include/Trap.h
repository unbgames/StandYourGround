#ifndef TRAP_H
#define TRAP_H

#include "Component.h"
#include "Timer.h"
#include "SpriteVector.h"
#include "Collider.h"
#include "Sound.h"
#include <map>

enum class TrapState {
    iddle = 0, // At placement
    start, // When activated
    interm,  // Taking effect
    interm2,  // Taking effect2
    finish, // Effect finished
    after, // After
};

class Trap : public Component {
public:
    Trap(GameObject &associated);
    ~Trap();
    bool Is(std::string type);
    std::string Type();
    void Render();
    virtual void Update(float dt);
    float GetDuration() const;

    void NotifyCollision(GameObject &other);
    virtual Vec2 GetCenter() const;
    virtual bool ShouldHide() const;
    virtual Vec2 GetShiftAfter() const;

    virtual void StartTrap();
    virtual void StopTrap();
    virtual bool IsTrapped();

protected:
    std::shared_ptr<GameObject> goSprite;
    Vec2 spritePos;
    SpriteVector *trapSprites;
    TrapState state, previous;
    float totalTime;
    std::map<TrapState, float> mapStateDuration;
    std::map<TrapState, Vec2> shiftMap;

    Collider *collider;
    bool fell;
    Timer timer;
    std::map<std::string, Sound*> soundMap;

    void AddSound(const std::string &key, const std::string &file);
    void PlaySound(const std::string &key, int volume = 128);
    void AddSprite(TrapState state, std::string file, int frameCount, float frameTime,
      float duration, Vec2 scale);
    void SetState(TrapState newState);
    void ShiftState(TrapState state, Vec2 shift);
};

#endif /* TRAP_H */
