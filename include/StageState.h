#ifndef STATESTATE_H
#define STATESTATE_H

#include "Sprite.h"
#include "State.h"
#include "Music.h"
#include "GameObject.h"

#include <vector>
#include <memory>
#include <random>

#define PI 3.14159
#define CAMERA_SPEED 100

class StageState : public State {
public:
    StageState();
    ~StageState();

    void LoadAssets();
    bool QuitRequested();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();

private:
    Music music;
    std::random_device randDevice;
    std::mt19937 randGen;

    bool isPaused;
    bool started;
};

#endif /* STATESTATE_H */
