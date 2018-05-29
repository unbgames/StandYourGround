#include "../include/MainState.h"
#include "../include/GameObject.h"
#include "../include/Sprite.h"
#include "../include/CameraFollower.h"
#include "../include/InputManager.h"
#include "../include/SpriteVector.h"
#include "../include/Elfa.h"
#include "../include/Orc.h"
#include "../include/Collider.h"
#include "../include/Camera.h"
#include "../include/LayeredTile.h"

MainState::MainState() : goElfa(std::make_shared<GameObject>()), goOrc(std::make_shared<GameObject>()) {
    auto bgObj = std::make_shared<GameObject>();
    objectArray.push_back(bgObj);
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);
    Sprite *spr = new Sprite(*bgObj, "./assets/img/ocean.jpg");
    bgObj->AddComponent(spr);
    CameraFollower *followerBg = new CameraFollower(*bgObj);
    bgObj->layer = 0;
    bgObj->AddComponent(followerBg);
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);

    auto tileObj = std::make_shared<GameObject>();
    objectArray.push_back(tileObj);
    LayeredTile *tileLayers = new LayeredTile(*tileObj, "./assets/map/", "levels.txt", {4, 4});
    tileObj->layer = 1;
    tileObj->AddComponent(tileLayers);

    goElfa->box.SetOrigin(30, 30);
    SpriteVector *vectorElfa = new SpriteVector(*goElfa);
    goElfa->AddComponent(vectorElfa);
    Elfa* player = new Elfa(*goElfa);
    goElfa->AddComponent(player);
    Collider* colElfa = new Collider(*goElfa);
    goElfa->AddComponent(colElfa);
    Camera::Follow(goElfa);
    goElfa->layer = 2;
    objectArray.push_back(goElfa);

    goOrc->box.SetOrigin(60, 30);
    SpriteVector *vectorOrc = new SpriteVector(*goOrc);
    goOrc->AddComponent(vectorOrc);
    Orc* enemy = new Orc(*goOrc);
    goOrc->AddComponent(enemy);
    Collider *colOrc = new Collider(*goOrc);
    goOrc->AddComponent(colOrc);
    goOrc->layer = 2;
    objectArray.push_back(goOrc);

}

MainState::~MainState() {
    objectArray.clear();
}


void MainState::LoadAssets() {
    SpriteVector *vector = (SpriteVector*) goElfa->GetComponent("SpriteVector");
    if(vector != nullptr) {
        vector->AddSprite("idle_frente_esq", "./assets/img/elfa/idle/elfa_idle_esq.png", 10, 0.11, 0.0, {4, 4});
        vector->AddSprite("run_frente_dir", "./assets/img/elfa/correndo/elfa_run_dir.png", 4, 0.11, 0.0, {4, 4});
        vector->AddSprite("run_frente_esq", "./assets/img/elfa/correndo/elfa_run_esq.png", 4, 0.11, 0.0, {4, 4});
        vector->AddSprite("idle_frente_dir", "./assets/img/elfa/idle/elfa_idle_dir.png", 10, 0.11, 0.0, {4, 4});

        vector->AddSprite("run_costa_dir", "./assets/img/elfa/correndo/elfa_run_costa_dir.png", 4, 0.11, 0.0, {4, 4});
        vector->AddSprite("idle_costa_dir", "./assets/img/elfa/idle/elfa_idle_costa_dir.png", 5, 0.11, 0.0, {4, 4});
        vector->AddSprite("run_costa_esq", "./assets/img/elfa/correndo/elfa_run_costa_esq.png", 4, 0.11, 0.0, {4, 4});
        vector->AddSprite("idle_costa_esq", "./assets/img/elfa/idle/elfa_idle_costa_esq.png", 5, 0.11, 0.0, {4, 4});
    }

    SpriteVector *vectorOrc = (SpriteVector*) goOrc->GetComponent("SpriteVector");
    if(vectorOrc != nullptr) {
        vectorOrc->AddSprite("idle_frente_esq", "./assets/img/orc/idle/orc_idle_esq.png", 10, 0.11, 0.0, {4, 4});
        vectorOrc->AddSprite("run_frente_dir", "./assets/img/orc/correndo/orc_run_dir.png", 4, 0.11, 0.0, {4, 4});
        vectorOrc->AddSprite("run_frente_esq", "./assets/img/orc/correndo/orc_run_esq.png", 4, 0.11, 0.0, {4, 4});
        vectorOrc->AddSprite("idle_frente_dir", "./assets/img/orc/idle/orc_idle_dir.png", 10, 0.11, 0.0, {4, 4});

        vectorOrc->AddSprite("run_costa_dir", "./assets/img/orc/correndo/orc_run_costa_dir.png", 4, 0.11, 0.0, {4, 4});
        vectorOrc->AddSprite("idle_costa_dir", "./assets/img/orc/idle/orc_idle_costa_dir.png", 5, 0.11, 0.0, {4, 4});
        vectorOrc->AddSprite("run_costa_esq", "./assets/img/orc/correndo/orc_run_costa_esq.png", 4, 0.11, 0.0, {4, 4});
        vectorOrc->AddSprite("idle_costa_esq", "./assets/img/orc/idle/orc_idle_costa_esq.png", 5, 0.11, 0.0, {4, 4});
    }
}

bool MainState::QuitRequested() {
    return quitRequested;
}

void MainState::Update(float dt) {
    Camera::Update(dt);
    InputManager &inp = InputManager::GetInstance();
    if (inp.QuitRequested()) {
        quitRequested = true;
    }
    if (inp.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }
    Elfa *elfa = (Elfa *) goElfa->GetComponent("Elfa");
    SpriteVector *sprVec = (SpriteVector *) goElfa->GetComponent("SpriteVector");
    if(elfa != nullptr && sprVec != nullptr) {
        sprVec->SetCurSprite(elfa->GetState());
    }

    Orc *orc = (Orc *) goOrc->GetComponent("Orc");
    SpriteVector *sprVecOrc = (SpriteVector *) goOrc ->GetComponent("SpriteVector");
    if(orc != nullptr && sprVecOrc != nullptr) {
        sprVecOrc->SetCurSprite(orc->GetState());
    }
    UpdateArray(dt);
}

void MainState::Render() {
    RenderArray();
}

void MainState::Start() {
    LoadAssets();
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
        // std::cout<<"STARTED!:"<<i<<std::endl;
    }
    started = true;
}

void MainState::Pause() {

}

void MainState::Resume() {

}
