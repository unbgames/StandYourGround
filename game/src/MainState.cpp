#include "MainState.h"
#include "GameObject.h"
#include "Sprite.h"
#include "CameraFollower.h"
#include "InputManager.h"
#include "SpriteVector.h"
#include "Elfa.h"
#include "Orc.h"
#include "Collider.h"
#include "Camera.h"
#include "Item.h"
#include "Collision.h"
#include "Tree.h"
#include "Text.h"
#include "GameTimer.h"
#include "Forest.h"
#include "config.h"

#include "Debug.h"
#include "Hole.h"
#include "Bomb.h"
#include "Totem.h"
#include "ItemFactory.h"

#include "EndGameState.h"
#include "CreditState.h"


#ifdef DEBUG
    bool DEBUG_GO = false;
    bool DEBUG_TILE = false;
    bool DEBUG_COL = false;
    unsigned int DEBUG_TILE_BORDER_LAYER = -1;
#endif // DEBUG

MainState::MainState() : goElfa(std::make_shared<GameObject>()), goOrc(std::make_shared<GameObject>()) {
    CABO_ESSA_DESGRACA = false;
    auto bgObj = std::make_shared<GameObject>();
    objectArray.push_back(bgObj);
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);
    Sprite *bgSpr = new Sprite(*bgObj, ASSETS_PATH("/img/bg.jpg"));
    bgObj->AddComponent(bgSpr);
    CameraFollower *followerBg = new CameraFollower(*bgObj);
    bgObj->layer = 0;
    bgObj->AddComponent(followerBg);
    bgObj->box.SetOrigin(0, 0);
    bgObj->box.SetSize(1024, 600);

    auto tileObj = std::make_shared<GameObject>();
    objectArray.push_back(tileObj);
    tileLayers = new LayeredTile(*tileObj, ASSETS_PATH("/map/"), "levels.txt", {4, 4}, 0);

    #ifdef DEBUG
        DEBUG_TILE_BORDER_LAYER = 1;
    #endif // DEBUG

    tileObj->layer = 1;
    tileObj->AddComponent(tileLayers);

    goElfa->box.SetOrigin(950, 900);
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
    Forest* forest = new Forest(*goForest, std::vector<std::string>{ASSETS_PATH("/map/trees1.csv"), ASSETS_PATH("/map/trees2.csv")}, {40, 40});
    Forest::forest = forest;
    goForest->AddComponent(forest);
    goForest->layer = 3;
    objectArray.push_back(goForest);

    auto goTotem = std::make_shared<GameObject>();
    goTotem->box.SetOrigin(3000, 700);
    Totem *totem = new Totem(*goTotem, 15);
    goTotem->AddComponent(totem);
    Totem::totem = totem;
    goTotem->layer = 3;
    objectArray.push_back(goTotem);



    // Concentra todos os elementos do HUD dentro da classe HUD
    auto goHUD = std::make_shared<GameObject>();
    hud = new HUD(*goHUD, Elfa::elfa);
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
        vector->AddSprite("idle_frente_esq", ASSETS_PATH("/img/elfa/idle/elfa_idle_esq.png"), 10, 0.11, 0.0, {4, 4});
        vector->AddSprite("run_frente_dir", ASSETS_PATH("/img/elfa/correndo/elfa_run_dir.png"), 4, 0.11, 0.0, {4, 4});
        vector->AddSprite("run_frente_esq", ASSETS_PATH("/img/elfa/correndo/elfa_run_esq.png"), 4, 0.11, 0.0, {4, 4});
        vector->AddSprite("idle_frente_dir", ASSETS_PATH("/img/elfa/idle/elfa_idle_dir.png"), 10, 0.11, 0.0, {4, 4});

        vector->AddSprite("run_costa_dir", ASSETS_PATH("/img/elfa/correndo/elfa_run_costa_dir.png"), 4, 0.11, 0.0, {4, 4});
        vector->AddSprite("idle_costa_dir", ASSETS_PATH("/img/elfa/idle/elfa_idle_costa_dir.png"), 5, 0.11, 0.0, {4, 4});
        vector->AddSprite("run_costa_esq", ASSETS_PATH("/img/elfa/correndo/elfa_run_costa_esq.png"), 4, 0.11, 0.0, {4, 4});
        vector->AddSprite("idle_costa_esq", ASSETS_PATH("/img/elfa/idle/elfa_idle_costa_esq.png"), 5, 0.11, 0.0, {4, 4});

        vector->AddSprite("pick_dir", ASSETS_PATH("/img/elfa/pegando_item/elfa_pick_dir.png"), 8, 0.11, 0.0, {4, 4});
        vector->AddSprite("pick_esq", ASSETS_PATH("/img/elfa/pegando_item/elfa_pick_esq.png"), 8, 0.11, 0.0, {4, 4});

        vector->AddSprite("cast_dir", ASSETS_PATH("/img/elfa/casting/elfa_cast_dir.png"), 24, 0.07, 0.0, {4, 4});
        vector->AddSprite("cast_esq", ASSETS_PATH("/img/elfa/casting/elfa_cast_esq.png"), 24, 0.07, 0.0, {4, 4});

    }

    SpriteVector *vectorOrc = (SpriteVector*) goOrc->GetComponent("SpriteVector");
    if(vectorOrc != nullptr) {
        vectorOrc->AddSprite("idle_frente_esq", ASSETS_PATH("/img/orc/idle/orc_idle_esq.png"), 10, 0.11, 0.0, {4, 4});
        vectorOrc->AddSprite("run_frente_dir", ASSETS_PATH("/img/orc/correndo/orc_run_dir.png"), 4, 0.11, 0.0, {4, 4});
        vectorOrc->AddSprite("run_frente_esq", ASSETS_PATH("/img/orc/correndo/orc_run_esq.png"), 4, 0.11, 0.0, {4, 4});
        vectorOrc->AddSprite("idle_frente_dir", ASSETS_PATH("/img/orc/idle/orc_idle_dir.png"), 10, 0.11, 0.0, {4, 4});

        vectorOrc->AddSprite("run_costa_dir", ASSETS_PATH("/img/orc/correndo/orc_run_costa_dir.png"), 4, 0.11, 0.0, {4, 4});
        vectorOrc->AddSprite("idle_costa_dir", ASSETS_PATH("/img/orc/idle/orc_idle_costa_dir.png"), 5, 0.11, 0.0, {4, 4});
        vectorOrc->AddSprite("run_costa_esq", ASSETS_PATH("/img/orc/correndo/orc_run_costa_esq.png"), 4, 0.11, 0.0, {4, 4});
        vectorOrc->AddSprite("idle_costa_esq", ASSETS_PATH("/img/orc/idle/orc_idle_costa_esq.png"), 5, 0.11, 0.0, {4, 4});

        vectorOrc->AddSprite("atq_dir", ASSETS_PATH("/img/orc/atq/orc_atq_dir.png"), 9, 0.02, 0.0, {4, 4});
        vectorOrc->AddSprite("atq_esq", ASSETS_PATH("/img/orc/atq/orc_atq_esq.png"), 9, 0.02, 0.0, {4, 4});
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
    if(hud->GameOver() && !CABO_ESSA_DESGRACA) {
        bool win = hud->Win();
        std::cout << "Cabo porra" << std::endl;

        auto bgObj = std::make_shared<GameObject>();
        objectArray.push_back(bgObj);
        bgObj->box.SetOrigin(0, 0);
        bgObj->box.SetSize(1024, 600);
        Sprite *bgSpr = new Sprite(*bgObj, ASSETS_PATH("/img/bg.jpg"));
        bgObj->AddComponent(bgSpr);
        CameraFollower *followerBg = new CameraFollower(*bgObj);
        bgObj->layer = 990;
        bgObj->AddComponent(followerBg);
        bgObj->box.SetOrigin(0, 0);
        bgObj->box.SetSize(1024, 600);

        auto messageObj = std::make_shared<GameObject>();
        objectArray.push_back(messageObj);
        messageObj->box.SetOrigin(SCREEN_WIDTH/2-128, SCREEN_HEIGHT/2-75);
        messageObj->box.SetSize(256, 150);
        std::string endGame = win ? "win" : "lose";
        Sprite *sprText = new Sprite(*messageObj, ASSETS_PATH("/img/") + endGame + ".png");
        messageObj->AddComponent(sprText);
        messageObj->layer = 10000;
        messageObj->box.SetOrigin(270, 540);
        messageObj->box.SetSize(256, 120);

        CABO_ESSA_DESGRACA = true;
    }
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
    if(!CABO_ESSA_DESGRACA)
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
    ItemFactory::Load({ASSETS_PATH("/map/flowers.csv"), ASSETS_PATH("/map/berries.csv"), ASSETS_PATH("/map/galhos.csv")});
    // auto goTrap = std::make_shared<GameObject>();
    // goTrap->box.SetOrigin(850, 580);
    // Sprite *trapSpr = new Sprite(*goTrap, ASSETS_PATH("/img/trap/buraco.png"));
    // // trapSpr->Hide();
    // trapSpr->SetScale({4, 4});
    // goTrap->box.SetSize(trapSpr->GetWidth(), trapSpr->GetHeight());
    // Hole *hole = new Hole(*goTrap);
    // goTrap->AddComponent(hole);
    // goTrap->AddComponent(trapSpr);
    // goTrap->layer = 1;
    // objectArray.push_back(goTrap);
    //
    // auto goTrap1 = std::make_shared<GameObject>();
    // goTrap1->box.SetSize(4*40, 4*20);
    // goTrap1->box.SetOrigin(1050, 600);
    // // trapSpr->Hide();
    // Bomb *bomb = new Bomb(*goTrap1);
    // goTrap1->AddComponent(bomb);
    // goTrap1->layer = 1;
    // objectArray.push_back(goTrap1);


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
