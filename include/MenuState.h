#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.h"

class MenuState : public State {
    public:
        MenuState();
        ~MenuState();

        void LoadAssets();
        bool QuitRequested();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();
    private:
};

#endif