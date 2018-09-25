#include "TitleState.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Text.h"
#include "Game.h"
#include "Sprite.h"
#include "config.h"

TitleState::TitleState() : State() {
    Camera::pos = Vec2(0, 0); // Reset camera position

    auto bgObj = std::make_shared<GameObject>();
    objectArray.push_back(bgObj);
    //std::cout<<"Created:"<<&(*obj)<<std::endl;

    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);
    Sprite *spr = new Sprite(*bgObj, ASSETS_PATH("/img/title.jpg"));
    bgObj->AddComponent(spr);

    auto txtObj = std::make_shared<GameObject>();
    txtObj->box.SetOrigin(100, 450);
    objectArray.push_back(txtObj);
    Text *text = new Text(*txtObj, ASSETS_PATH("/font/Call me maybe.ttf"), 50, TextStyle::SOLID,
      "Click SPACE to continue or ESC to exit.", {0, 0, 0, 0});
    txtObj->AddComponent(text);
}

TitleState::~TitleState() {
}

void TitleState::LoadAssets() {
}

void TitleState::Update(float dt) {
    InputManager &inp = InputManager::GetInstance();
    if (inp.KeyPress(ESCAPE_KEY) || inp.QuitRequested()) {
        quitRequested = true;
        std::cout<<"Esc from TitleState";
    }
    if (inp.KeyPress(SPACE_KEY)) {
        quitRequested = true;
        // Game::GetInstance().Push(new StageState());
        // std::cout<<"GOOD ";
    }
}

void TitleState::Render() {
    for (const auto &go : objectArray) {
        go->Render();
    }
}

void TitleState::Start() {
    LoadAssets();
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
        // std::cout<<"STARTED!:"<<i<<std::endl;
    }
    started = true;
}

void TitleState::Pause() {
}

void TitleState::Resume() {
}
