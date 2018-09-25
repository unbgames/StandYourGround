#include "Game.h"
#include "MenuState.h"

int main (int argc, char** arg) {
    Game::GetInstance();
    auto state = new MenuState();
    Game::GetInstance().Push(state);
    Game::GetInstance().Run();
}
