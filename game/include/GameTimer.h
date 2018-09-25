#ifndef GAME_TIMER_H
#define GAME_TIMER_H

#include "Component.h"
#include "Timer.h"
#include "Text.h"

class GameTimer : public Component {
    public:
        GameTimer(GameObject& associated, int startingMin, int startingSec);

        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        std::string Type();
        void NotifyCollision(GameObject &other);

        bool gameOver();
    private:
        int min;
        int sec;
        Timer timer;
        Text* timeText;
};

#endif