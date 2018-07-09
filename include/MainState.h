#ifndef MAIN_STATE_H
#define MAIN_STATE_H

#include "State.h"
#include "LayeredTile.h"
#include "../include/HUD.h"

class MainState : public State {
public:
    MainState();
    ~MainState();

    void LoadAssets();
    bool QuitRequested();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();

private:
    bool isPaused;
    bool started;
    std::shared_ptr<GameObject> goElfa;
    std::shared_ptr<GameObject> goOrc;
    LayeredTile *tileLayers;
    HUD *hud;
    bool CABO_ESSA_DESGRACA;
};

#endif
