#include "CreditState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Text.h"
#include "Game.h"
#include "config.h"

const char* membros[6] = {"Felipe da Costa Malaquias", "Lucas Mota Ribeiro", "Emille Catarine Rodrigues Cancado", "Vitor Teodoro Bastos", "Leonardo Bustamente", "Brenda Holanda"};

CreditState::CreditState() {
    auto bgObj = std::make_shared<GameObject>();
    objectArray.push_back(bgObj);
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);
    Sprite *spr = new Sprite(*bgObj, ASSETS_PATH("/img/bg.jpg"));
    bgObj->AddComponent(spr);
    bgObj->layer = 0;
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);

    for(int i = 0; i < 6; i++) {
        auto creditTextObj = std::make_shared<GameObject>();
        objectArray.push_back(creditTextObj);
        Text* membro = new Text(*creditTextObj, ASSETS_PATH("/font/pixel.ttf"),
                                80, TextStyle::SOLID, membros[i], {0, 0, 0, 255});
        creditTextObj->box.SetOrigin(SCREEN_WIDTH/2 - membro->GetBox().GetW()/2, 100 + i*60);
        creditTextObj->layer = 2;
        creditTextObj->AddComponent(membro);
    }

    auto backTextObj = std::make_shared<GameObject>();
    objectArray.push_back(backTextObj);
    backTextObj->box.SetOrigin(20, SCREEN_HEIGHT - 100);
    Text* backText = new Text(*backTextObj, ASSETS_PATH("/font/pixel.ttf"),
                              80, TextStyle::SOLID, "Voltar", {255, 0, 0, 255});
    backTextObj->AddComponent(backText);
    backTextObj->layer = 2;
}
CreditState::~CreditState() {
    objectArray.clear();
}

void CreditState::LoadAssets() {

}
bool CreditState::QuitRequested() {
    return quitRequested;
}
void CreditState::Update(float dt) {
    InputManager &inp = InputManager::GetInstance();

    if (inp.KeyPress(SDLK_RETURN)) {
        quitRequested = true;
    }
    if (inp.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }
}
void CreditState::Render() {
    RenderArray();
}

void CreditState::Start() {
    LoadAssets();
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
        // std::cout<<"STARTED!:"<<i<<std::endl;
    }
    started = true;
}
void CreditState::Pause() {

}
void CreditState::Resume() {

}
