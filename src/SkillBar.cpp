#include "../include/SkillBar.h"
#include "../include/Game.h"

SkillBar::SkillBar(GameObject& associated) : Component(associated) {
    GameObject* holeObj = new GameObject();
    holeKey = new Text(*holeObj, "./assets/font/pixel.ttf", 80, TextStyle::SOLID, "J", {30, 45, 60, 255});
    textSkillList.push_back(holeKey);
    holeObj->AddComponent(holeKey);
    holeObj->layer = associated.layer;
    holeObj->box.SetOrigin(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT-100);
    Sprite* holeSprite = new Sprite(*holeObj, "./assets/img/trap/buraco.png");
    spriteSkillList.push_back(holeSprite);
    holeSprite->SetOffset({50, 30});
    holeSprite->SetScale(3, 3);
    holeObj->AddComponent(holeSprite);
    skillList.push_back(holeObj);


    GameObject* bombObj = new GameObject();
    bombKey = new Text(*bombObj, "./assets/font/pixel.ttf", 80, TextStyle::SOLID, "K", {30, 45, 60, 255});
    textSkillList.push_back(bombKey);
    bombObj->AddComponent(bombKey);
    bombObj->layer = associated.layer;
    bombObj->box.SetOrigin(SCREEN_WIDTH/2 + 40, SCREEN_HEIGHT-100);
    Sprite* bombSprite = new Sprite(*bombObj, "./assets/img/trap/flower.png");
    spriteSkillList.push_back(bombSprite);
    bombSprite->SetOffset({20, 10});
    bombSprite->SetScale(3, 3);
    bombObj->AddComponent(bombSprite);
    skillList.push_back(bombObj);
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
