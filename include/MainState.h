#ifndef MAIN_STATE_H
#define MAIN_STATE_H

#include "State.h"

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
        
};

#endif