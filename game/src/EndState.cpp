#include "GameData.h"
#include "EndState.h"
#include "TitleState.h"
#include "Camera.h"
#include "Game.h"
#include "Sprite.h"
#include "InputManager.h"
#include "config.h"

EndState::EndState() : State() {
    Camera::pos = Vec2(0, 0); // Reset camera position

    auto bgObj = std::make_shared<GameObject>();
    objectArray.push_back(bgObj);
    //std::cout<<"Created:"<<&(*obj)<<std::endl;

    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);
    Sprite *spr = new Sprite(*bgObj, (GameData::playerVictory) ? ASSETS_PATH("/img/win.jpg") : ASSETS_PATH("/img/lose.jpg"));
    bgObj->AddComponent(spr);
}

EndState::~EndState() {

}

void EndState::LoadAssets() {

}
void EndState::Update(float dt) {
    InputManager &inp = InputManager::GetInstance();
    if (inp.KeyPress(ESCAPE_KEY) || inp.QuitRequested()) {
        quitRequested = true;
    }
    if (inp.KeyPress(SPACE_KEY)) {
        quitRequested = true;
        Game::GetInstance().Push(new TitleState());
        // std::cout<<"GOOD ";
    }
}
void EndState::Render() {
    for (const auto &go : objectArray) {
        go->Render();
    }
}

void EndState::Start() {
    LoadAssets();
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
        // std::cout<<"STARTED!:"<<i<<std::endl;
    }
    started = true;
}
void EndState::Pause() {

}
void EndState::Resume() {

}
