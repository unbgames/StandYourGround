#include "SkillBar.h"
#include "Game.h"
#include "config.h"

SkillBar::SkillBar(GameObject& associated) : Component(associated) {
    GameObject* holeObj = new GameObject();
    holeKey = new Text(*holeObj, ASSETS_PATH("/font/pixel.ttf"), 80, TextStyle::SOLID, "J", {30, 45, 60, 255});
    textSkillList.push_back(holeKey);
    holeObj->AddComponent(holeKey);
    holeObj->layer = associated.layer;
    holeObj->box.SetOrigin(SCREEN_WIDTH/2 - 140, SCREEN_HEIGHT-100);
    Sprite* holeSprite = new Sprite(*holeObj, ASSETS_PATH("/img/trap/buraco_cam.png"));
    spriteSkillList.push_back(holeSprite);
    holeSprite->SetOffset({50, 30});
    holeSprite->SetScale(3, 3);
    holeObj->AddComponent(holeSprite);
    skillList.push_back(holeObj);


    GameObject* bombObj = new GameObject();
    bombKey = new Text(*bombObj, ASSETS_PATH("/font/pixel.ttf"), 80, TextStyle::SOLID, "K", {30, 45, 60, 255});
    textSkillList.push_back(bombKey);
    bombObj->AddComponent(bombKey);
    bombObj->layer = associated.layer;
    bombObj->box.SetOrigin(SCREEN_WIDTH/2, SCREEN_HEIGHT-100);
    Sprite* bombSprite = new Sprite(*bombObj, ASSETS_PATH("/img/trap/flower.png"));
    spriteSkillList.push_back(bombSprite);
    bombSprite->SetOffset({17, 10});
    bombSprite->SetScale(3, 3);
    bombObj->AddComponent(bombSprite);
    skillList.push_back(bombObj);

    GameObject* cipoObj = new GameObject();
    cipoKey = new Text(*cipoObj, ASSETS_PATH("/font/pixel.ttf"), 80, TextStyle::SOLID, "L", {30, 45, 60, 255});
    textSkillList.push_back(cipoKey);
    cipoObj->AddComponent(cipoKey);
    cipoObj->layer = associated.layer;
    cipoObj->box.SetOrigin(SCREEN_WIDTH/2 + 120, SCREEN_HEIGHT-100);
    Sprite* cipoSprite = new Sprite(*cipoObj, ASSETS_PATH("/img/trap/cipo_armadilha.png"));
    spriteSkillList.push_back(cipoSprite);
    cipoSprite->SetOffset({35, 24});
    cipoSprite->SetScale(0.3, 0.3);
    cipoObj->AddComponent(cipoSprite);
    skillList.push_back(cipoObj);
}

void SkillBar::Update(float dt) {

}

void SkillBar::Render() {
    for(int i = 0; i < skillList.size(); i++) {
        textSkillList[i]->RenderNoCam();
        spriteSkillList[i]->RenderNoCam();
    }
}

bool SkillBar::Is(std::string type) {
    return type == "SkillBar";
}

std::string SkillBar::Type() {
    return "SkillBar";
}

void SkillBar::NotifyCollision(GameObject &other) {

}
