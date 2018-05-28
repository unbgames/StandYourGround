#include "../include/Game.h"
#include "../include/MainState.h"

int main (int argc, char** arg) {
    Game::GetInstance();
    auto state = new MainState();
    Game::GetInstance().Push(state);
    Game::GetInstance().Run();
}
