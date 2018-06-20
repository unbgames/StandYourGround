#include "../include/MenuState.h"
#include "../include/Sprite.h"
#include "../include/InputManager.h"
#include "../include/Menu.h"
#include "../include/Game.h"
#include "../include/MainState.h"
#include "../include/GameTimer.h"
#include "../include/CreditState.h"

void StartGame() {
    Game::GetInstance().GetCurrentState().Quit();
    Game::GetInstance().Push(new MainState());
}

void QuitGame() {
    Game::GetInstance().GetCurrentState().Quit();
}

void Credits() {
    Game::GetInstance().Push(new CreditState());
}

MenuState::MenuState() {
    auto bgObj = std::make_shared<GameObject>();
    objectArray.push_back(bgObj);
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);
    Sprite *spr = new Sprite(*bgObj, "./assets/img/ocean.jpg");
    bgObj->AddComponent(spr);
    bgObj->layer = 0;
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);

    auto menuObj = std::make_shared<GameObject>();
    objectArray.push_back(menuObj);
    Menu* mainMenu = new Menu(*menuObj);
    menuObj->layer = 2;
    menuObj->AddComponent(mainMenu);
    mainMenu->AddOption("Start Game", StartGame);
    mainMenu->AddOption("Credits", Credits);
    mainMenu->AddOption("Exit", QuitGame);
}
MenuState::~MenuState() {
    objectArray.clear();
}

void MenuState::LoadAssets() {

}
bool MenuState::QuitRequested() {
    return quitRequested;
}
void MenuState::Update(float dt) {
    InputManager &inp = InputManager::GetInstance();

    if (inp.QuitRequested()) {
        quitRequested = true;
    }
    if (inp.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }

    UpdateArray(dt);
}
void MenuState::Render() {
    RenderArray();
}

void MenuState::Start() {
    LoadAssets();
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
        // std::cout<<"STARTED!:"<<i<<std::endl;
    }
    started = true;
}
void MenuState::Pause() {

}
void MenuState::Resume() {

}