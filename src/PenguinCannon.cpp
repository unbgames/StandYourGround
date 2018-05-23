#include "../include/PenguinCannon.h"
#include "../include/Sprite.h"
#include "../include/Camera.h"
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/Bullet.h"
#include "../include/Collider.h"

PenguinCannon::PenguinCannon(GameObject &associated, GameObject &penguinBody) : Component(associated),
    pbody(penguinBody), angle(0){
    Sprite *spr =  new Sprite(associated, "./assets/img/cubngun.png");
    associated.box.SetSize(spr->GetWidth(), spr->GetHeight());
    associated.AddComponent(spr);

    // Collider *col = new Collider(associated);
    // associated.AddComponent(c    ol);
}

PenguinCannon::~PenguinCannon() {
}

void PenguinCannon::Update(float dt) {
    timer.Update(dt);
    // std::cout<<"Cannon:"<<associated.box.Center()<<"| "<<pbody.box.Center()<<std::endl;
    associated.box.SetCenter(pbody.box.Center());
    InputManager &inp = InputManager::GetInstance();
    Vec2 clickPos(inp.GetMouseX(), inp.GetMouseY());
    Vec2 pos(clickPos - Camera::pos);
    associated.angle = Vec2::Angle(associated.box.Center(), pos);

    if (inp.IsMouseDown(LEFT_MOUSE_BUTTON)) { // RIGHT
        Shoot();
    }
}

void PenguinCannon::Render() {
}

bool PenguinCannon::Is(std::string type) {
    return (type == "PenguinCannon");
}

std::string PenguinCannon::Type() {
    return "PenguinCannon";
}

void PenguinCannon::Shoot() {
    if (timer.Get() >= COOLDOWN) {
        auto &state = Game::GetInstance().GetCurrentState();
        auto bulletObj = std::make_shared<GameObject>();

        float speed = 200;
        int damage = 30;
        float maxDistance = 2080;

        Bullet *bullet = new Bullet(*bulletObj, associated.angle, speed, damage, maxDistance, false);
        bulletObj->box.SetCenter(associated.box.Center() + Vec2(50, 0).GetRotated(associated.angle));
        bulletObj->AddComponent(bullet);
        state.AddObject(bulletObj);

        timer.Restart();
    }
}

void PenguinCannon::NotifyCollision(GameObject &other) {
    auto bullet = other.GetComponent("Bullet");
    if (bullet != nullptr) {
        pbody.NotifyCollision(other);
    }
}
