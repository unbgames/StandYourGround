#include "../include/Totem.h"
#include "../include/Sprite.h"
#include "../include/Collider.h"
#include "../include/Elfa.h"

Totem* Totem::totem = nullptr;

Totem::Totem(GameObject& associated, int trees, int health) : Component(associated), trees(trees), health(health) {
    std::cout << "CAN ATTACK:"<<trees<<"|"<<health<<std::endl;
    Sprite *totemSpr = new Sprite(associated, "./assets/img/totem.png", 20, 0.1, 0);
    totemSpr->SetScale({4, 4});
    associated.box.SetSize(totemSpr->GetWidth(), totemSpr->GetHeight()*0.75);
    Collider *colTotem = new Collider(associated, {0.15, 0.65}, {0, 120});
    associated.AddComponent(colTotem);
    associated.AddComponent(totemSpr);
}

Totem::~Totem() {
}

void Totem::Start() {
}

void Totem::Update(float dt) {
    const Rect &rect = associated.box;
    auto sprite = (Sprite *) associated.GetComponent("Sprite");
    if (rect.Contains(Elfa::elfa->BottomLeft()) || rect.Contains(Elfa::elfa->BottomRight())) {
        sprite->Opacity(50);
    } else {
        sprite->Opacity(100);
    }
}

void Totem::Render() {
}

bool Totem::Is(std::string type) {
    return (type == "Totem");
}

std::string Totem::Type() {
    return "Totem";
}

void Totem::alertTreeFall() {
    trees--;
}

bool Totem::canAttack() const {
    std::cout << "CAN ATTACK:"<<trees<<std::endl;
    return (trees == 0);
}

Vec2 Totem::Center() const {
    auto collider = (Collider *) associated.GetComponent("Collider");
    return collider->box.Center();
}

void Totem::Damage(int damage) {
    health -= damage;
    std::cout << "TOTEM LIFE:"<<health<<std::endl;
}

bool Totem::IsDead() const {
    return (health <= 0);
}

void Totem::NotifyCollision(GameObject &other) {
}
