#include "State.h"

#ifndef END_GAME_STATE_H
#define END_GAME_STATE_H


class EndGameState : public State {
    public:
        EndGameState(bool win);
        ~EndGameState();

        void LoadAssets();
        bool QuitRequested();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();
};

#endif