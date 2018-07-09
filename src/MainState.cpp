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
#include "../include/Forest.h"
#include "../include/HUD.h"
#include "../include/Debug.h"
#include "../include/Hole.h"
#include "../include/Bomb.h"


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
    Sprite *spr = new Sprite(*bgObj, "./assets/img/bg.jpg");
    bgObj->AddComponent(spr);
    CameraFollower *followerBg = new CameraFollower(*bgObj);
    bgObj->layer = 0;
    bgObj->AddComponent(followerBg);
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);

    auto tileObj = std::make_shared<GameObject>();
    objectArray.push_back(tileObj);
    tileLayers = new LayeredTile(*tileObj, "./assets/map/", "levels.txt", {4, 4}, 0);

    #ifdef DEBUG
        DEBUG_TILE_BORDER_LAYER = 1;
    #endif // DEBUG

    tileObj->layer = 1;
    tileObj->AddComponent(tileLayers);

    goElfa->box.SetOrigin(900, 900);
    SpriteVector *vectorElfa = new SpriteVector(*goElfa);
    goElfa->AddComponent(vectorElfa);
    Elfa* player = new Elfa(*goElfa);
    Elfa::elfa = player;
    goElfa->AddComponent(player);
    Collider* colElfa = new Collider(*goElfa, {0.15, 0.6}, {0, 40});
    goElfa->AddComponent(colElfa);
    Camera::Follow(goElfa);
    goElfa->layer = 3;
    objectArray.push_back(goElfa);

    goOrc->box.SetOrigin(1050, 400);
    SpriteVector *vectorOrc = new SpriteVector(*goOrc);
    goOrc->AddComponent(vectorOrc);
    Orc* enemy = new Orc(*goOrc);
    goOrc->AddComponent(enemy);
    Collider *colOrc = new Collider(*goOrc, {0.15, 0.6}, {0, 40});
    goOrc->AddComponent(colOrc);
    goOrc->layer = 3;
    objectArray.push_back(goOrc);

    auto goForest = std::make_shared<GameObject>();
    goForest->box.SetOrigin(0, 0);
    goForest->box.SetSize(0, 0);
    Forest* forest = new Forest(*goForest, std::vector<std::string>{"./assets/map/trees1.csv", "./assets/map/trees2.csv"}, {40, 40});
    Forest::forest = forest;
    goForest->AddComponent(forest);
    goForest->layer = 3;
    objectArray.push_back(goForest);

    for(int i = 1; i < 15; i++) {
        auto goItem = std::make_shared<GameObject>();
        goItem->box.SetOrigin(600, 100*i);
        Sprite* itemSprite = new Sprite(*goItem, "./assets/img/items/Berries x800.png");
        itemSprite->SetScale(0.2, 0.2);
        goItem->AddComponent(itemSprite);
        goItem->box.SetSize(itemSprite->GetWidth(), itemSprite->GetHeight());
        goItem->AddComponent(new Collider(*goItem));
        goItem->AddComponent(new Item(*goItem, ItemType::berry));
        goItem->layer = 3;
        objectArray.push_back(goItem);
    }

    for(int i = 1; i < 15; i++) {
        auto goItem = std::make_shared<GameObject>();
        goItem->box.SetOrigin(800, 100*i);
        Sprite* itemSprite = new Sprite(*goItem, "./assets/img/items/cipo.png");
        itemSprite->SetScale(0.3, 0.3);
        goItem->AddComponent(itemSprite);
        goItem->box.SetSize(itemSprite->GetWidth(), itemSprite->GetHeight());
        goItem->AddComponent(new Collider(*goItem));
        goItem->AddComponent(new Item(*goItem, ItemType::cipo));
        goItem->layer = 3;
        objectArray.push_back(goItem);
    }

    for(int i = 1; i < 15; i++) {
        auto goItem = std::make_shared<GameObject>();
        goItem->box.SetOrigin(1000, 100*i);
        Sprite* itemSprite = new Sprite(*goItem, "./assets/img/items/galho.png");
        itemSprite->SetScale(0.4, 0.4);
        goItem->AddComponent(itemSprite);
        goItem->box.SetSize(itemSprite->GetWidth(), itemSprite->GetHeight());
        goItem->AddComponent(new Collider(*goItem));
        goItem->AddComponent(new Item(*goItem, ItemType::galho));
        goItem->layer = 3;
        objectArray.push_back(goItem);
    }


    // Concentra todos os elementos do HUD dentro da classe HUD
    auto goHUD = std::make_shared<GameObject>();
    HUD* hud = new HUD(*goHUD, Elfa::elfa);
    goHUD->AddComponent(hud);
    goHUD->layer = 5;
    objectArray.push_back(goHUD);
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

        vector->AddSprite("pick_dir", "./assets/img/elfa/pegando_item/elfa_pick_dir.png", 8, 0.11, 0.0, {4, 4});
        vector->AddSprite("pick_esq", "./assets/img/elfa/pegando_item/elfa_pick_esq.png", 8, 0.11, 0.0, {4, 4});

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
    if(!go1->IsDead() && !go2->IsDead() && Collision::IsColliding(col1->box, col2->box, go1->angle, go2->angle)) {
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

    // Elfa *elfa = (Elfa *) goElfa->GetComponent("Elfa");
    // SpriteVector *sprVec = (SpriteVector *) goElfa->GetComponent("SpriteVector");
    // if(elfa != nullptr && sprVec != nullptr) {
    //     sprVec->SetCurSprite(Character::StateToString(elfa->GetState()));
    // }
    //
    // Orc *orc = (Orc *) goOrc->GetComponent("Orc");
    // SpriteVector *sprVecOrc = (SpriteVector *) goOrc->GetComponent("SpriteVector");
    // if(orc != nullptr && sprVecOrc != nullptr) {
    //     sprVecOrc->SetCurSprite(Character::StateToString(orc->GetState()));
    // }

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
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        // std::cout<<"Obj:"<<i<<std::endl;
        if (objectArray[i]->IsDead()) {
            std::cout<<"Morreu de fato"<<std::endl;
            auto soundComp = objectArray[i].get()->GetComponent("Sound");
            if (!soundComp || !static_cast<Sound *>(soundComp)->Playing()) {
                std::cerr << "Morreu"<<std::endl;
                objectArray.erase(objectArray.begin() + i);
                i--; //adjust iterator ???
            }
        }
    }
}

void MainState::Render() {
    RenderArray();
}

void MainState::Start() {
    auto goTrap = std::make_shared<GameObject>();
    goTrap->box.SetOrigin(1050, 800);
    Sprite *trapSpr = new Sprite(*goTrap, "./assets/img/trap/buraco.png");
    // trapSpr->Hide();
    trapSpr->SetScale({4, 4});
    goTrap->box.SetSize(trapSpr->GetWidth(), trapSpr->GetHeight());
    Hole *hole = new Hole(*goTrap);
    goTrap->AddComponent(hole);
    goTrap->AddComponent(trapSpr);
    goTrap->layer = 1;
    objectArray.push_back(goTrap);

    auto goTrap1 = std::make_shared<GameObject>();
    goTrap1->box.SetSize(4*40, 4*20);
    goTrap1->box.SetOrigin(1050, 600);
    // trapSpr->Hide();
    Bomb *bomb = new Bomb(*goTrap1);
    goTrap1->AddComponent(bomb);
    goTrap1->layer = 1;
    objectArray.push_back(goTrap1);


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
