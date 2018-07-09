#include "../include/HUD.h"
#include "../include/Bag.h"
#include "../include/Totem.h"
#include "../include/Game.h"


HUD::HUD(GameObject& associated, Elfa* player) : Component(associated), player(player){
    GameObject* goTimer = new GameObject();
    timer = new GameTimer(*goTimer, 3,1);
    goTimer->AddComponent(timer);
    goTimer->box.SetSize(timer->GetBox().GetW(), timer->GetBox().GetH());
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

    GameObject* totemHP = new GameObject();
    totemHP->box.SetOrigin(100, 100);
    totemHP->box.SetSize(300, 300);
    Sprite *hp = new Sprite(*totemHP, "./assets/img/hp.png");
    hp->SetScale({3, 3});
    totemHP->layer = associated.layer;
    totemHP->AddComponent(hp);
    hudComponents.push_back(totemHP);
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
    return timer->gameOver() || Totem::totem->GetNumTrees() <= 0;
}

bool HUD::Win() {
    std::cout << "NumTrees: " << Totem::totem->GetNumTrees() << std::endl;
    return Totem::totem->GetNumTrees() > 1;
}

void HUD::NotifyCollision(GameObject &other) {
}

bool HUD::UseTrap(std::string trap) {
    return sideItemBar->blinkItem(trap);
}
