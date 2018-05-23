#include "../include/Bullet.h"
#include "../include/Sprite.h"
#include "../include/Collider.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage,
    float maxDistance, bool targetsPlayer) : Component(associated), targetsPlayer(targetsPlayer),
    speed(speed, 0), damage(damage), distanceLeft(maxDistance) {

    this->speed.Rotate(angle);
    Sprite *spr =  new Sprite(associated, "./assets/img/minionbullet2.png", 3, 100);
    associated.box.SetSize(spr->GetWidth(), spr->GetHeight());
    associated.AddComponent(spr);

    Collider *col = new Collider(associated);
    associated.AddComponent(col);

    associated.angle = angle;
}

Bullet::~Bullet() {
}

void Bullet::Update(float dt) {
    Vec2 pos = speed*dt;
    float mag = pos.Mag();
    if (mag <= distanceLeft) {
        associated.box.Shift(pos);
        distanceLeft -= mag;
    } else {
        associated.RequestDelete();
    }
}

void Bullet::Render() {
}

bool Bullet::Is(std::string type) {
    return (type == "Bullet");
}

std::string Bullet::Type() {
    return "Bullet";
}

int Bullet::GetDamage() {
    return damage;
}

void Bullet::NotifyCollision(GameObject &other) {
    if (!other.HasComponent("Bullet")) {
        if (targetsPlayer) {
            if (other.HasComponent("PenguinBody")) {
                std::cout<<"BULLET HIT PLAYER"<<std::endl;
                associated.RequestDelete();
            }
        } else {
            if (other.HasComponent("Alien") || other.HasComponent("Minion")) {
                std::cout<<"BULLET HIT ENEMY"<<std::endl;
                associated.RequestDelete();
            }
        }
    }
}
