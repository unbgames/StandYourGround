#include "../include/Minion.h"
#include "../include/Sprite.h"
#include "../include/Bullet.h"
#include "../include/Game.h"
#include "../include/Sound.h"
#include "../include/Collider.h"

#define RADIUS 200

Minion::Minion(GameObject &associated, GameObject &alienCenter,
  float arcOffsetDeg) : Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg),
  randGen(randDevice()) {
    Sprite *spr =  new Sprite(associated, "./assets/img/minion.png");

    std::uniform_real_distribution<float> realDist(1, 1.5);
    float randVal = realDist(randGen);
    spr->SetScale(randVal, randVal);
    associated.box.SetSize(spr->GetWidth(), spr->GetHeight());
    associated.AddComponent(spr);

    Collider *col = new Collider(associated);
    associated.AddComponent(col);
}

Minion::~Minion() {
}

void Minion::Update(float dt) {
    // std::cout<<"Updated Minion:"<<dt<<std::endl;
    Vec2 distance(RADIUS, 0);
    arc +=dt;
    distance.Rotate(arc);
    associated.box.SetCenter(alienCenter.box.Center() + distance);
    associated.angle += dt;
}

void Minion::Render() {
}

bool Minion::Is(std::string type) {
    return (type == "Minion");
}

std::string Minion::Type() {
    return "Minion";
}

void Minion::Shoot(Vec2 pos) {
    auto &state = Game::GetInstance().GetCurrentState();
    auto bulletObj = std::make_shared<GameObject>();

    float angle = Vec2::Angle(associated.box.Center(), pos);
    float speed = 200;
    int damage = 30;
    float maxDistance = 2080;

    Bullet *bullet = new Bullet(*bulletObj, angle, speed, damage, maxDistance, true);
    bulletObj->box.SetCenter(associated.box.Center());
    bulletObj->AddComponent(bullet);
    state.AddObject(bulletObj);
}

void Minion::NotifyCollision(GameObject &other) {
    auto bulletComp = other.GetComponent("Bullet");
    auto bullet = dynamic_cast<Bullet*>(bulletComp);
    if (bulletComp != nullptr && !bullet->targetsPlayer) {
        alienCenter.NotifyCollision(other);
        associated.RequestDelete();

        // EXPLOSION
        auto &state = Game::GetInstance().GetCurrentState();
        auto expObj = std::make_shared<GameObject>();
        Sprite *expSpr = new Sprite(*expObj, "./assets/img/miniondeath.png", 4, 100, 0.4);
        expObj->box.SetSize(expSpr->GetWidth(), expSpr->GetHeight());
        // std::cout<<"CREATED RECT:"<<expObj->box.GetX()<<" "<<expObj->box.GetY()<<" "<<expObj->box.GetW()<<" "<<expObj->box.GetH()<<std::endl;
        expObj->box.SetOrigin(associated.box.Origin());
        Sound *expSnd = new Sound(*expObj, "./assets/audio/boom.wav");
        expObj->AddComponent(expSpr);
        expObj->AddComponent(expSnd);
        state.AddObject(expObj);
        expSnd->Play();
    }
}
