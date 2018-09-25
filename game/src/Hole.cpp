#include "Hole.h"
#include "Elfa.h"
#include "config.h"

Hole::Hole(GameObject &associated) : Trap(associated) {
    AddSprite(TrapState::iddle, ASSETS_PATH("/img/trap/buraco_cam.png"), 1, 0, 0, {4, 4});
    AddSprite(TrapState::start, ASSETS_PATH("/img/trap/buraco_falling.png"), 6, 0.1, 6*0.1, {4, 4});
    AddSprite(TrapState::interm, ASSETS_PATH("/img/trap/buraco.png"), 1, 0, 2, {4, 4});
    AddSprite(TrapState::finish, ASSETS_PATH("/img/trap/buraco_out.png"), 20, 0.1, 20*0.1, {4, 4});
    AddSprite(TrapState::after, ASSETS_PATH("/img/trap/buraco.png"), 1, 0, 0, {4, 4});

    AddSound("fall_in", ASSETS_PATH("/audio/orc_fall_in_hole.wav"));
    AddSound("get_out", ASSETS_PATH("/audio/orc_out_hole.wav"));

    SetState(TrapState::iddle);

    ShiftState(TrapState::start, {0, -90});
    ShiftState(TrapState::finish, {0, -90});
}

Hole::~Hole() {

}

Vec2 Hole::GetShiftAfter() const {
    return {40, 40};
}

bool Hole::ShouldHide() const {
    return true;
}
void Hole::Update(float dt) {
    // std::cout << "TRAP UPDATE" << std::endl;
    if (fell) {
        timer.Update(dt);
        float time = timer.Get();
        Elfa* elfaPtr = Elfa::elfa;
        Vec2 elfPos = elfaPtr->Origin();
        unsigned int reducer = int(std::pow(Vec2::EuclidianDist(associated.box.Center(), elfPos), 2) / 4000);
        if (state == TrapState::iddle) {
            timer.Restart();
            state = TrapState::start;
            std::cout << "TRAP UPDATE: start" << std::endl;
            trapSprites->SetCurSprite("start");
            goSprite->box.SetOrigin(spritePos + shiftMap[TrapState::start]);
            unsigned int maxVolume = 80;
            PlaySound("fall_in", maxVolume - std::min(reducer, maxVolume));
        } else if (state == TrapState::start && time > mapStateDuration[TrapState::start]) {
            timer.Restart();
            state = TrapState::interm;
            std::cout << "TRAP UPDATE: interm" << std::endl;
            trapSprites->SetCurSprite("interm");
            goSprite->box.SetOrigin(spritePos + shiftMap[TrapState::interm]);
        } else if (state == TrapState::interm && time > mapStateDuration[TrapState::interm]){
            timer.Restart();
            state = TrapState::finish;
            std::cout << "TRAP UPDATE: finish" << std::endl;
            trapSprites->SetCurSprite("finish");
            goSprite->box.SetOrigin(spritePos + shiftMap[TrapState::finish]);
            unsigned int maxVolume = 80;
            PlaySound("get_out", maxVolume - std::min(reducer, maxVolume));
        } else if (state == TrapState::finish && time > mapStateDuration[TrapState::finish]) {
            state = TrapState::after;
            std::cout << "TRAP UPDATE: after" << std::endl;
            trapSprites->SetCurSprite("after");
            goSprite->box.SetOrigin(spritePos + shiftMap[TrapState::after]);
            fell = false;
        }
        if (previous != state) {
            trapSprites->ResetFrameCount();
        }
        previous = state;
    }
}
