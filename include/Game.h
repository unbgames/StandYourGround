#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "Vec2.h"

#include <stack>
#include <string>
#include <memory>
#include <SDL2/SDL.h>

class Game {
public:
    ~Game();
    void Run();

    SDL_Renderer* GetRenderer();
    static Game &GetInstance();
    State &GetCurrentState();

    void Push(State *state);

    float GetDeltaTime();
    Vec2 GetWindowSize();

private:
    Game(std::string title, int width, int height);
    void CalculateDeltaTime();

    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *storedState;

    std::stack<std::unique_ptr<State>> stateStack;

    bool hasStarted;
    int frameStart;
    float dt;
    int width;
    int height;
};

#endif /* GAME_H */
