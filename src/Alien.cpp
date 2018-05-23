#include "../include/Alien.h"
#include "../include/Minion.h"
#include "../include/Sprite.h"
#include "../include/Game.h"
#include "../include/Bullet.h"
#include "../include/Collider.h"
#include "../include/Camera.h"
#include "../include/Sound.h"
#include "../include/PenguinBody.h"
#include "../include/InputManager.h"

#include <iostream>

int Alien::alienCount = 0;

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), nMinions(nMinions), speed(0, 0), hp(100) {
    Sprite *spr =  new Sprite(associated, "./assets/img/alien.png");
    associated.box.SetSize(spr->GetWidth(), spr->GetHeight());
    associated.AddComponent(spr);

    Collider *col = new Collider(associated);
    associated.AddComponent(col);
    Alien::alienCount++;
}
Alien::~Alien() {
    minionArray.clear();
}

void Alien::Update(float dt) {
    // std::cout<<"Update GO:"<<pos<<std::endl;
    associated.angle -= dt;
    if (PenguinBody::player != nullptr) { // If Player is not DEAD
        switch (state) {
            case AlienState::MOVING:
                if (associated.box.Center() == destination) { // SHOOT
                    destination = PenguinBody::player->GetBox().Center();
                    std::shared_ptr<GameObject> closest = minionArray[0].lock();
                    float distance = std::numeric_limits<float>::max();
                    // Get closest minion
                    for (auto auxminion : minionArray) {
                        auto minion = auxminion.lock();
                        if (minion != nullptr) {
                            float auxDist = Vec2::ManhattamDist(destination, minion->box.Center());
                            if (auxDist < distance) {
                                closest = minion;
                                distance = auxDist;
                            }
                        }
                    }
                    Component *minion = closest->GetComponent("Minion");
                    if (minion != nullptr) {
                        Minion *casted = dynamic_cast<Minion*>(minion);
                        casted->Shoot(destination);
                    }
                    state = AlienState::RESTING;
                } else { // MOVE
                    float distance = Vec2::EuclidianDist(destination, associated.box.Center());
                    Vec2 dir = destination - associated.box.Center();
                    dir.SetMag(ALIEN_SPEED);
                    if (distance < 1.09 * ALIEN_SPEED) {
                        // std::cout<<"Parou"<<std::endl;
                        associated.box.SetCenter(destination);
                    } else {
                        // associated.box
                        // std::cout<<"POS CENTER:"<< associated.box.Center() <<std::endl;
                        associated.box.Shift(dir);
                    }
                }
            break;
            case AlienState::RESTING:
                if (timer.Get() >= ALIEN_WAIT) {
                    timer.Restart();
                    destination = PenguinBody::player->GetBox().Center();
                    state = AlienState::MOVING;
                } else {
                    timer.Update(dt);
                }
            break;
        }
    }

    if (hp <= 0) {
        for (auto auxminion : minionArray) {
            auto minion = auxminion.lock();
            if (minion != nullptr) {
                minion->RequestDelete();

                // EXPLOSION
                auto &state = Game::GetInstance().GetCurrentState();
                auto expObj = std::make_shared<GameObject>();
                Sprite *expSpr = new Sprite(*expObj, "./assets/img/aliendeath.png", 4, 100, 0.4);
                expObj->box.SetSize(expSpr->GetWidth(), expSpr->GetHeight());
                expObj->box.SetCenter(associated.box.Center());
                Sound *expSnd = new Sound(*expObj, "./assets/audio/boom.wav");
                expObj->AddComponent(expSpr);
                expObj->AddComponent(expSnd);
                state.AddObject(expObj);
                expSnd->Play();
            }
        }
        associated.RequestDelete();
    }
}

void Alien::Start() {
    if (nMinions > 0) {
        float radInterval = 2*PI/nMinions;
        auto &state = Game::GetInstance().GetCurrentState();
        for (int i = 0; i < nMinions; i++) {
            auto minionObj = std::make_shared<GameObject>();
            Minion *minion = new Minion(*minionObj, associated, i * radInterval);
            minionObj->AddComponent(minion);
            minionArray.push_back(minionObj);
            state.AddObject(minionObj);
        }
    }
    std::cout<<"Added minions"<<std::endl;
    //std::cout<<"Render GO addr:"<<&associated<<std::endl;
}

void Alien::Render() {

}

bool Alien::Is(std::string type) {
    return type == "Alien";
}

std::string Alien::Type() {
    return "Alien";
}

void Alien::NotifyCollision(GameObject &other) {
    auto cmp = other.GetComponent("Bullet");
    if (cmp != nullptr) {
        auto bullet = dynamic_cast<Bullet*>(cmp);
        if (!bullet->targetsPlayer) {
            hp -= bullet->GetDamage();
            std::cout<<"Damage Alien"<<std::endl;
        }
    }
}
