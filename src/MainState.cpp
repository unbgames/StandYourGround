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
#include "../include/Item.h"
#include "../include/Collision.h"
#include "../include/Tree.h"
#include "../include/Text.h"
#include "../include/GameTimer.h"
#include "../include/Debug.h"

#ifdef DEBUG
    bool DEBUG_GO = false;
    bool DEBUG_TILE = false;
    bool DEBUG_COL = false;
    unsigned int DEBUG_TILE_BORDER_LAYER = -1;
#endif // DEBUG

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
    tileLayers = new LayeredTile(*tileObj, "./assets/map/", "levels.txt", {4, 4}, 1);

    #ifdef DEBUG
        DEBUG_TILE_BORDER_LAYER = 1;
    #endif // DEBUG

    tileObj->layer = 1;
    tileObj->AddComponent(tileLayers);

    goElfa->box.SetOrigin(300, 300);
    SpriteVector *vectorElfa = new SpriteVector(*goElfa);
    goElfa->AddComponent(vectorElfa);
    Elfa* player = new Elfa(*goElfa);
    Elfa::elfa = player;
    goElfa->AddComponent(player);
    Collider* colElfa = new Collider(*goElfa, {0.15, 0.6}, {0, 40});
    goElfa->AddComponent(colElfa);
    Camera::Follow(goElfa);
    goElfa->layer = 2;
    objectArray.push_back(goElfa);

    goOrc->box.SetOrigin(100, 300);
    SpriteVector *vectorOrc = new SpriteVector(*goOrc);
    goOrc->AddComponent(vectorOrc);
    Orc* enemy = new Orc(*goOrc);
    goOrc->AddComponent(enemy);
    Collider *colOrc = new Collider(*goOrc, {0.15, 0.6}, {0, 40});
    goOrc->AddComponent(colOrc);
    goOrc->layer = 2;
    objectArray.push_back(goOrc);

    auto goBoulder = std::make_shared<GameObject>();
    goBoulder->box.SetOrigin(700, 500);
    Sprite* boulderSprite = new Sprite(*goBoulder, "./assets/img/items/boulder.png");
    goBoulder->AddComponent(boulderSprite);
    goBoulder->box.SetSize(boulderSprite->GetWidth() - 35, boulderSprite->GetHeight());
    goBoulder->AddComponent(new Collider(*goBoulder, {1, 1}, {0, 0}));
    goBoulder->layer = 2;
    objectArray.push_back(goBoulder);

    auto goItem = std::make_shared<GameObject>();
    goItem->box.SetOrigin(500, 100);
    Sprite* itemSprite = new Sprite(*goItem, "./assets/img/items/Berries x800.png");
    goItem->AddComponent(itemSprite);
    goItem->box.SetSize(itemSprite->GetWidth(), itemSprite->GetHeight());
    goItem->AddComponent(new Collider(*goItem));
    goItem->AddComponent(new Item(*goItem));
    goItem->layer = 1;
    objectArray.push_back(goItem);

    auto goTree = std::make_shared<GameObject>();
    goTree->box.SetOrigin(100, 100);
    Sprite *treeSprite = new Sprite(*goTree, "./assets/img/items/tree.png");
    goTree->AddComponent(treeSprite);
    goTree->box.SetSize(treeSprite->GetWidth(), treeSprite->GetHeight());
    goTree->AddComponent(new Collider(*goTree, {0.07, 0.2}, {30, 220}));
    goTree->AddComponent(new Tree(*goTree));
    goTree->layer = 2;
    objectArray.push_back(goTree);

    auto goTimer = std::make_shared<GameObject>();
    goTimer->box.SetOrigin(450, 0);
    GameTimer *countDownTimer = new GameTimer(*goTimer, 4, 15);
    goTimer->AddComponent(countDownTimer);
    goTimer->box.SetSize(countDownTimer->GetBox().GetW(), countDownTimer->GetBox().GetH());
    goTimer->layer = 2;
    objectArray.push_back(goTimer);
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

        vectorOrc->AddSprite("atq_dir", "./assets/img/orc/atq/orc_atq_dir.png", 9, 0.02, 0.0, {4, 4});
        vectorOrc->AddSprite("atq_esq", "./assets/img/orc/atq/orc_atq_esq.png", 9, 0.02, 0.0, {4, 4});
    }
}

bool MainState::QuitRequested() {
    return quitRequested;
}

void checkCollision(GameObject* go1, GameObject* go2) {
    Collider* col1 = (Collider *) go1->GetComponent("Collider");
    Collider* col2 = (Collider *) go2->GetComponent("Collider");
    if(Collision::IsColliding(col1->box, col2->box, go1->angle, go2->angle)) {
        go1->NotifyCollision(*go2);
        go2->NotifyCollision(*go1);
    }
}

void MainState::Update(float dt) {
    Camera::Update(dt);

    InputManager &inp = InputManager::GetInstance();

    #ifdef DEBUG
        if (inp.KeyPress(F1_KEY)) { // Game Object
            std::cout << "Debug GO: " << (!DEBUG_GO?"ON":"OFF")<<std::endl;
            DEBUG_GO = !DEBUG_GO;
        }
        if (inp.KeyPress(F2_KEY)) { // Tile
            std::cout << "Debug Tiles: " << (!DEBUG_GO?"ON":"OFF")<<std::endl;
            DEBUG_TILE = !DEBUG_TILE;
        }
        if (inp.KeyPress(F3_KEY)) { // Collision
            std::cout << "Debug COL: " << (!DEBUG_COL?"ON":"OFF")<<std::endl;
            DEBUG_COL = !DEBUG_COL;
        }
    #endif // DEBUG


    if (inp.QuitRequested()) {
        quitRequested = true;
    }
    if (inp.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }

    Elfa *elfa = (Elfa *) goElfa->GetComponent("Elfa");
    SpriteVector *sprVec = (SpriteVector *) goElfa->GetComponent("SpriteVector");
    if(elfa != nullptr && sprVec != nullptr) {
        sprVec->SetCurSprite(Character::StateToString(elfa->GetState()));
    }

    Orc *orc = (Orc *) goOrc->GetComponent("Orc");
    SpriteVector *sprVecOrc = (SpriteVector *) goOrc->GetComponent("SpriteVector");
    if(orc != nullptr && sprVecOrc != nullptr) {
        sprVecOrc->SetCurSprite(Character::StateToString(orc->GetState()));
    }

    UpdateArray(dt);

    for(int i = 0; i < objectArray.size(); i++) {
        GameObject* go1 = objectArray[i].get();
        if(go1->GetComponent("Collider") != nullptr) {
            for(int j = i + 1; j < objectArray.size(); j++) {
                GameObject* go2 = objectArray[j].get();
                if(go2->GetComponent("Collider") != nullptr)
                    checkCollision(go1, go2);
            }
        }
    }

    // Collision with border map.
    Collider *colliderElfa = (Collider *) goElfa->GetComponent("Collider");
    Collider *colliderOrc = (Collider *) goOrc->GetComponent("Collider");
    // colideBox.Shift(-Camera::pos);
    if (tileLayers->Collide(colliderElfa->box)){
        GameObject aux;
        goElfa->NotifyCollision(aux);
    }
    if (tileLayers->Collide(colliderOrc->box)){
        GameObject aux;
        goOrc->NotifyCollision(aux);
    }
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
