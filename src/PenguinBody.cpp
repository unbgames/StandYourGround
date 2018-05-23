#include "../include/PenguinBody.h"
#include "../include/PenguinCannon.h"
#include "../include/InputManager.h"
#include "../include/Collider.h"
#include "../include/Camera.h"
#include "../include/Sprite.h"
#include "../include/Game.h"
#include "../include/Sound.h"
#include "../include/Bullet.h"

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated), speed(0, 0), linearSpeed(300), angle(0), hp(50) {
    Sprite *spr =  new Sprite(associated, "./assets/img/penguin.png");
    associated.box.SetSize(spr->GetWidth(), spr->GetHeight());
    associated.AddComponent(spr);

    Collider *col = new Collider(associated);
    associated.AddComponent(col);

    PenguinBody::player = this;
    std::cout<<"Created Penguin:"<<this<<std::endl;
}

PenguinBody::~PenguinBody() {
    // EXPLOSION
    if (hp <= 0) {
        auto &state = Game::GetInstance().GetCurrentState();
        auto expObj = std::make_shared<GameObject>();
        Sprite *expSpr = new Sprite(*expObj, "./assets/img/penguindeath.png", 5, 100, 0.5);
        expObj->box.SetSize(expSpr->GetWidth(), expSpr->GetHeight());
        expObj->box.SetCenter(associated.box.Center());
        Sound *expSnd = new Sound(*expObj, "./assets/audio/boom.wav");
        expObj->AddComponent(expSpr);
        expObj->AddComponent(expSnd);
        state.AddObject(expObj);
        expSnd->Play();
    }

    Camera::Unfollow();
    PenguinBody::player = nullptr;
}

void PenguinBody::Start() {
    auto &state = Game::GetInstance().GetCurrentState();
    auto cannonObj = std::make_shared<GameObject>();
    PenguinCannon *cannon = new PenguinCannon(*cannonObj, associated);
    cannonObj->AddComponent(cannon);
    state.AddObject(cannonObj);
    pcannon = cannonObj;
}

void PenguinBody::Update(float dt) {
    InputManager &inp = InputManager::GetInstance();
    float speedInc = dt * 8;
    float angleInc = dt * 2;
    float friction = 0.99;

    speed *= friction;

    if (inp.IsKeyDown(W_KEY)) { // UP
        speed += Vec2(speedInc, 0);
    }
    if (inp.IsKeyDown(S_KEY)) { // DOWN
        speed -= Vec2(speedInc, 0);
    }
    if (inp.IsKeyDown(A_KEY)) { // LEFT
        angle -= angleInc;
    }
    if (inp.IsKeyDown(D_KEY)) { // RIGHT
        angle += angleInc;
    }
    if (speed.Mag() > linearSpeed) speed.SetMag(linearSpeed);
    associated.box.Shift(speed.GetRotated(angle));
    associated.angle = angle;
    // std::cout<<"Body:"<<associated.box.Origin()<< &(associated.box)<<std::endl;
    // std::cout<<"Angle:"<<angle<<std::endl;

    if (hp <= 0) {
        auto cannon = pcannon.lock();
        if (cannon != nullptr) {
            cannon->RequestDelete();
        }
        associated.RequestDelete();
    }
}

void PenguinBody::Render() {
}

bool PenguinBody::Is(std::string type) {
    return (type == "PenguinBody");
}

std::string PenguinBody::Type() {
    return "PenguinBody";
}

void PenguinBody::NotifyCollision(GameObject &other) {
    // std::cout<<"COLLISION Penguin"<<std::endl;
    auto cmp = other.GetComponent("Bullet");
    if (cmp != nullptr) {
        auto bullet = dynamic_cast<Bullet*>(cmp);
        if (bullet->targetsPlayer) {
            hp -= bullet->GetDamage();
            // std::cout<<"Damage Penguin"<<std::endl;
        }
    }
}
