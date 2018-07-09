#include "../include/Totem.h"
#include "../include/Sprite.h"
#include "../include/Collider.h"
#include "../include/Elfa.h"

Totem* Totem::totem = nullptr;

Totem::Totem(GameObject& associated, int trees, int health) : Component(associated), trees(trees), health(health) {
    // std::cout << "CAN ATTACK:"<<trees<<"|"<<health<<std::endl;
    Sprite *totemSpr = new Sprite(associated, "./assets/img/totem.png", 20, 0.1, 0);
    totemSpr->SetScale({4, 4});
    associated.box.SetSize(totemSpr->GetWidth(), totemSpr->GetHeight()*0.75);

    std::cout << "CAN ATTACK:"<<trees<<"|"<<health<<std::endl;

    totemSpr = new SpriteVector(associated);
    totemSpr->AddSprite("alive", "./assets/img/totem/totem.png", 20, 0.1, 0, {4, 4});
    totemSpr->AddSprite("dead", "./assets/img/totem/totem_dead.png", 31, 0.1, 0, {4, 4});
    totemSpr->SetCurSprite("alive");
    associated.AddComponent(totemSpr);

    associated.box.SetSize(2*80, 4*110*0.75);
>>>>>>> ae6f43c... Totem morre.
    Collider *colTotem = new Collider(associated, {0.15, 0.65}, {0, 120});
    associated.AddComponent(colTotem);
}

Totem::~Totem() {
}

void Totem::Start() {
}

void Totem::Update(float dt) {
    const Rect &rect = associated.box;
    auto sprite = (SpriteVector *) associated.GetComponent("SpriteVector");
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
    // std::cout << "CAN ATTACK:"<<trees<<std::endl;
    return (trees == 0);
}

Vec2 Totem::Center() const {
    auto collider = (Collider *) associated.GetComponent("Collider");
    return collider->box.Center();
}

void Totem::Damage(int damage) {
    health -= damage;
    std::cout << "TOTEM LIFE:"<<health<<std::endl;
    if (health <= 0) {
        totemSpr->SetCurSprite("dead");
    }
}

bool Totem::IsDead() const {
    return (health <= 0);
}

void Totem::NotifyCollision(GameObject &other) {
}

int Totem::GetNumTrees() {
    return trees;
}
