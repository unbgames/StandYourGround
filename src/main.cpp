#include "../include/Game.h"
#include "../include/StageState.h"

int main (int argc, char** arg) {
    Game::GetInstance();
    auto state = new StageState();
    Game::GetInstance().Push(state);
    Game::GetInstance().Run();

}
