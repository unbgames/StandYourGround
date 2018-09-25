#ifndef CREDIT_STATE_H
#define CREDIT_STATE_H

#include "State.h"

class CreditState : public State {
    public:
        CreditState();
        ~CreditState();

        void LoadAssets();
        bool QuitRequested();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();
};

#endif