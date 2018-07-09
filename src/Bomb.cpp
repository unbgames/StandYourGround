#include "../include/Bomb.h"
#include "../include/Elfa.h"

Bomb::Bomb(GameObject &associated) : Trap(associated) {
    AddSprite(TrapState::iddle, "./assets/img/trap/flower.png", 1, 0, 0, {4, 4});
    AddSprite(TrapState::start, "./assets/img/trap/flower_boom.png", 12, 0.1, 12*0.1, {4, 4});
    AddSprite(TrapState::interm, "./assets/img/trap/orc_to_sleep.png", 13, 0.1, 13*0.1, {4, 4});
    AddSprite(TrapState::finish, "./assets/img/trap/orc_sleep.png", 12, 0.1, 6*12*0.1, {4, 4});
    AddSprite(TrapState::after, "./assets/img/trap/orc_waking.png", 36, 0.1, 40*0.1, {4, 4});
    SetState(TrapState::iddle);
    ShiftState(TrapState::interm, {-30, -60});
    ShiftState(TrapState::finish, {-35, -60});
    ShiftState(TrapState::after, {-35, -60});
    // ShiftState(TrapState::after, {-40, -90});

    AddSound("sleep", "./assets/audio/orc_sleeping.wav");
    AddSound("flower_swoosh", "./assets/audio/flower_fx.wav");
}

Bomb::~Bomb() {
}

Vec2 Bomb::GetShiftAfter() const {
    return {0, 0};
}

bool Bomb::ShouldHide() const {
    return (state == TrapState::interm || state == TrapState::finish || state == TrapState::after);
}
void Bomb::StopTrap() {
    fell = false;
    associated.RequestDelete();
    std::cout << "TRAP DELETE" << std::endl;
}

void Bomb::Update(float dt) {
    // std::cout << "TRAP UPDATE" << std::endl;
    if (fell) {
        timer.Update(dt);
        float time = timer.Get();
        Elfa* elfaPtr = Elfa::elfa;
        Vec2 elfPos = elfaPtr->Origin();
        unsigned int reducer = int(std::pow(Vec2::EuclidianDist(associated.box.Center(), elfPos), 2) / 4000);
        if (state == TrapState::iddle) {
            std::cout << "TRAP UPDATE: start" << std::endl;
            timer.Restart();
            state = TrapState::start;
            trapSprites->SetCurSprite("start");
            goSprite->box.SetOrigin(spritePos + shiftMap[TrapState::start]);
            unsigned int maxVolume = 128;
            PlaySound("flower_swoosh", maxVolume - std::min(reducer, maxVolume));
        } else if (state == TrapState::start && time > mapStateDuration[TrapState::start]) {
            timer.Restart();
            state = TrapState::interm;
            std::cout << "TRAP UPDATE: interm" << std::endl;
            trapSprites->SetCurSprite("interm");
            goSprite->box.SetOrigin(spritePos + shiftMap[TrapState::interm]);
        } else if (state == TrapState::interm && time > mapStateDuration[TrapState::interm]) {
            timer.Restart();
            state = TrapState::finish;
            std::cout << "TRAP UPDATE: finish" << std::endl;
            trapSprites->SetCurSprite("finish");
            unsigned int maxVolume = 128;
            PlaySound("sleep", maxVolume - std::min(reducer, maxVolume));
            goSprite->box.SetOrigin(spritePos + shiftMap[TrapState::finish]);
        } else if (state == TrapState::finish && time > mapStateDuration[TrapState::finish]) {
            timer.Restart();
            state = TrapState::after;
            std::cout << "TRAP UPDATE: after" << std::endl;
            trapSprites->SetCurSprite("after");
            goSprite->box.SetOrigin(spritePos + shiftMap[TrapState::after]);
        } else if (state == TrapState::after && time > mapStateDuration[TrapState::after]){
            std::cout << "TRAP UPDATE: FREE"<<int(state) << std::endl;
            fell = false;
            timer.Restart();
        }
        if (previous != state) {
            trapSprites->ResetFrameCount();
        }
        previous = state;
    }
}
