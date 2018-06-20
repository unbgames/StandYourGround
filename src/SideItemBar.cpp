#include "../include/SideItemBar.h"
#include "../include/Game.h"
#include "../include/Sprite.h"
#include "../include/Bag.h"

SideItemBar::SideItemBar(GameObject& associated) : Component(associated) {
    GameObject* berryObj = new GameObject();
    berryAmount = new Text(*berryObj, "./assets/font/pixel.ttf", 80, TextStyle::SOLID, "0x", {0, 0, 0, 255});
    textItemList.push_back(berryAmount);
    berryObj->AddComponent(berryAmount);
    berryObj->layer = associated.layer;
    berryObj->box.SetOrigin(SCREEN_WIDTH-100, 100);
    Sprite* berrySprite = new Sprite(*berryObj, "./assets/img/items/Berries x800.png");
    spriteItemList.push_back(berrySprite);
    berrySprite->SetOffset({50, 10});
    berrySprite->SetScale(0.3, 0.3);
    berryObj->AddComponent(berrySprite);
    itemList.push_back(berryObj);

    GameObject* cipoObj = new GameObject();
    cipoAmount = new Text(*cipoObj, "./assets/font/pixel.ttf", 80, TextStyle::SOLID, "0x", {0, 0, 0, 255});
    textItemList.push_back(cipoAmount);
    cipoObj->AddComponent(cipoAmount);
    cipoObj->layer = associated.layer;
    cipoObj->box.SetOrigin(SCREEN_WIDTH-100, 150);
    Sprite* cipoSprite = new Sprite(*cipoObj, "./assets/img/items/cipo.png");
    spriteItemList.push_back(cipoSprite);
    cipoSprite->SetOffset({50, 15});
    cipoSprite->SetScale(0.5, 0.5);
    cipoObj->AddComponent(cipoSprite);
    itemList.push_back(cipoObj);

    GameObject* galhoObj = new GameObject();
    galhoAmount = new Text(*galhoObj, "./assets/font/pixel.ttf", 80, TextStyle::SOLID, "0x", {0, 0, 0, 255});
    textItemList.push_back(galhoAmount);
    galhoObj->AddComponent(galhoAmount);
    galhoObj->layer = associated.layer;
    galhoObj->box.SetOrigin(SCREEN_WIDTH-100, 200);
    Sprite* galhoSprite = new Sprite(*galhoObj, "./assets/img/items/galho.png");
    spriteItemList.push_back(galhoSprite);
    galhoSprite->SetOffset({50, 15});
    galhoSprite->SetScale(0.5, 0.5);
    galhoObj->AddComponent(galhoSprite);
    itemList.push_back(galhoObj);
}

void SideItemBar::Update(float dt) {
    if(berry != Bag::GetAmountItem(ItemType::berry)) {
        berry = Bag::GetAmountItem(ItemType::berry);
        berryAmount->SetText(std::to_string(berry) + "x");
    }

    if(cipo != Bag::GetAmountItem(ItemType::cipo)) {
        cipo = Bag::GetAmountItem(ItemType::cipo);
        cipoAmount->SetText(std::to_string(cipo) + "x");
    }

    if(galho != Bag::GetAmountItem(ItemType::galho)) {
        galho = Bag::GetAmountItem(ItemType::galho);
        galhoAmount->SetText(std::to_string(galho) + "x");
    }
}
void SideItemBar::Render() {
    for(int i = 0; i < itemList.size(); i++) {
        textItemList[i]->RenderNoCam();
        spriteItemList[i]->RenderNoCam();
    }
}
bool SideItemBar::Is(std::string type) {

}
std::string SideItemBar::Type() {

}
void SideItemBar::NotifyCollision(GameObject &other) {

}