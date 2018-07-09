#include "../include/HUD.h"
#include "../include/Bag.h"


HUD::HUD(GameObject& associated, Elfa* player) : Component(associated), player(player){
    GameObject* goTimer = new GameObject();
    GameTimer *countDownTimer = new GameTimer(*goTimer, 1, 20);
    goTimer->AddComponent(countDownTimer);
    goTimer->box.SetSize(countDownTimer->GetBox().GetW(), countDownTimer->GetBox().GetH());
    goTimer->layer = associated.layer;
    hudComponents.push_back(goTimer);

    GameObject* goSideItemBar = new GameObject();
    sideItemBar = new SideItemBar(*goSideItemBar);
    goSideItemBar->layer = associated.layer;
    goSideItemBar->AddComponent(sideItemBar);
    hudComponents.push_back(goSideItemBar);

    GameObject* goSkillBar = new GameObject();
    skillBar = new SkillBar(*goSkillBar);
    goSkillBar->layer = associated.layer;
    goSkillBar->AddComponent(skillBar);
    hudComponents.push_back(goSkillBar);

}

void HUD::Update(float dt) {
    for(int i = 0; i < hudComponents.size(); i++) {
        hudComponents[i]->Update(dt);
    }
}
void HUD::Render() {
    for(int i = 0; i < hudComponents.size(); i++) {
        hudComponents[i]->Render();
    }
}
bool HUD::Is(std::string type) {
    return type == "HUD";
}
std::string HUD::Type() {
    return "HUD";
}

bool HUD::GameOver() {
    return timer->gameOver();
}
void HUD::NotifyCollision(GameObject &other) {

}

bool HUD::UseTrap(std::string trap) {
    return sideItemBar->blinkItem(trap);
}