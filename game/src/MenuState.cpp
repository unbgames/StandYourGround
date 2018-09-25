#include "MenuState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Menu.h"
#include "Game.h"
#include "MainState.h"
#include "GameTimer.h"
#include "CreditState.h"
#include "config.h"

void MenuState::StartGame() {
    quitRequested = true;
    Game::GetInstance().Push(new MainState());
}

void MenuState::QuitGame() {
    Game::GetInstance().GetCurrentState().Quit();
}

void MenuState::Credits() {
    Game::GetInstance().Push(new CreditState());
}

MenuState::MenuState() : music(ASSETS_PATH("/audio/soundtrack_menu.mp3")){
    music.Play();
    auto bgObj = std::make_shared<GameObject>();
    objectArray.push_back(bgObj);
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(265, 150);
    Sprite *spr = new Sprite(*bgObj, ASSETS_PATH("/img/bg_menu.jpg"));
    spr->SetScale({0.8, 0.8});
    bgObj->AddComponent(spr);
    bgObj->layer = 0;
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);

    auto menuObj = std::make_shared<GameObject>();
    objectArray.push_back(menuObj);
    Menu* mainMenu = new Menu(*menuObj);
    menuObj->layer = 2;
    menuObj->AddComponent(mainMenu);
    mainMenu->AddOption("Start Game", [=] () {
        this->StartGame();
    });
    // mainMenu->AddOption("Start Game", StartGame);
    mainMenu->AddOption("Credits", [=] () {
        this->Credits();
    });
    mainMenu->AddOption("Exit", [=] () {
        this->QuitGame();
    });
}

MenuState::~MenuState() {
    music.Stop();
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
