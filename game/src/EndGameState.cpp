#include "EndGameState.h"
#include "Sprite.h"
#include "Game.h"
#include "InputManager.h"
#include "config.h"

EndGameState::EndGameState(bool win) {
    auto bgObj = std::make_shared<GameObject>();
    objectArray.push_back(bgObj);
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);
    Sprite *spr = new Sprite(*bgObj, ASSETS_PATH("/img/bg.jpg"));
    bgObj->AddComponent(spr);
    bgObj->layer = 10;
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);

    auto messageObj = std::make_shared<GameObject>();
    objectArray.push_back(messageObj);
    messageObj->box.SetOrigin(SCREEN_WIDTH/2-128, SCREEN_HEIGHT/2-75);
    messageObj->box.SetSize(256, 150);
    std::string path = std::string(ASSETS_PATH("/img/")) + (win ? std::string("win.png") : std::string("lose.png"));
    Sprite *sprText = new Sprite(*messageObj, path);
    messageObj->AddComponent(sprText);
    messageObj->layer = 10;
    messageObj->box.SetOrigin(0, 0);
    messageObj->box.SetSize(1024, 600);
}

EndGameState::~EndGameState() {
    objectArray.clear();
}


void EndGameState::LoadAssets() {

}
bool EndGameState::QuitRequested() {
    return quitRequested;
}
void EndGameState::Update(float dt) {
    InputManager &inp = InputManager::GetInstance();

    if (inp.KeyPress(SDLK_RETURN)) {
        quitRequested = true;
    }
    if (inp.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }
}
void EndGameState::Render() {
    RenderArray();
}

void EndGameState::Start() {
    LoadAssets();
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
        // std::cout<<"STARTED!:"<<i<<std::endl;
    }
    started = true;
}
void EndGameState::Pause() {

}
void EndGameState::Resume() {

}

