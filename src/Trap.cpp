#include "../include/Trap.h"
#include "../include/Game.h"

Trap::Trap(GameObject &associated) : Component(associated), totalTime(0), fell(false) {
    collider = new Collider(associated, {0.65, 0.70}, {0, 0});
    associated.AddComponent(collider);

    State &state = Game::GetInstance().GetCurrentState();

    goSprite = std::make_shared<GameObject>();
    goSprite->layer = 2;

    std::cout << "TRAP ORIGIN:"<<associated.box.GetH()<<"|"<< associated.box.GetW()<<std::endl;
    goSprite->box.SetOrigin(associated.box.Origin());
    spritePos = associated.box.Origin();
    trapSprites = new SpriteVector(*goSprite);
    goSprite->box.SetSize(28, 33);
    goSprite->AddComponent(trapSprites);
    state.AddObject(goSprite);
    shiftMap[TrapState::iddle] = {0, 0};
    shiftMap[TrapState::start] = {0, 0};
    shiftMap[TrapState::interm] = {0, 0};
    shiftMap[TrapState::finish] = {0, 0};
    shiftMap[TrapState::after] = {0, 0};
}

Trap::~Trap() {
    goSprite->RequestDelete();
}

float Trap::GetDuration() const {
    return totalTime;
}

Vec2 Trap::GetCenter() const {
    return associated.box.Center();
}

bool Trap::ShouldHide() const {
    return false;
}

void Trap::StartTrap() {
    std::cout << "STARTED TRAP"<<std::endl;
    fell = true;
}

void Trap::StopTrap() {
    // std::cout << "STARTED TRAP"<<std::endl;
    fell = false;
}

bool Trap::IsTrapped() {
    // std::cout << "STARTED TRAP"<<std::endl;
    return fell;
}

Vec2 Trap::GetShiftAfter() const {
    return {1, 1};
}

void Trap::NotifyCollision(GameObject &other) {
    // std::cout << "COLLISION"<<std::endl;
}

void Trap::AddSprite(TrapState state, std::string file, int frameCount, float frameTime,
  float duration, Vec2 scale) {
    mapStateDuration[state] = duration;
    switch (state) {
        case TrapState::iddle:
            trapSprites->AddSprite("iddle", file, frameCount, frameTime, 0, scale);
            break;
        case TrapState::start:
            trapSprites->AddSprite("start", file, frameCount, frameTime, 0, scale);
            totalTime += duration;
            break;
        case TrapState::interm:
            trapSprites->AddSprite("interm", file, frameCount, frameTime, 0, scale);
            totalTime += duration;
            break;
        case TrapState::interm2:
            trapSprites->AddSprite("interm2", file, frameCount, frameTime, 0, scale);
            totalTime += duration;
            break;
        case TrapState::finish:
            trapSprites->AddSprite("finish", file, frameCount, frameTime, 0, scale);
            totalTime += duration;
            break;
        case TrapState::after:
            trapSprites->AddSprite("after", file, frameCount, frameTime, 0, scale);
            break;
    }
}
bool Trap::Is(std::string type) {
    return (type == "Trap");
}

std::string Trap::Type() {
    return "Trap";
}

void Trap::Render() {
}

void Trap::Update(float dt) {

}

void Trap::SetState(TrapState newState) {
    state = newState;
    switch (state) {
        case TrapState::iddle:
            trapSprites->SetCurSprite("iddle");
            goSprite->box.SetOrigin(spritePos + shiftMap[TrapState::iddle]);
            break;
        case TrapState::start:
            trapSprites->SetCurSprite("start");
            goSprite->box.SetOrigin(spritePos + shiftMap[TrapState::start]);
            break;
        case TrapState::interm:
            trapSprites->SetCurSprite("interm");
            goSprite->box.SetOrigin(spritePos + shiftMap[TrapState::interm]);
            break;
        case TrapState::interm2:
            trapSprites->SetCurSprite("interm2");
            goSprite->box.SetOrigin(spritePos + shiftMap[TrapState::interm2]);
            break;
        case TrapState::finish:
            trapSprites->SetCurSprite("finish");
            goSprite->box.SetOrigin(spritePos + shiftMap[TrapState::finish]);
            break;
        case TrapState::after:
            trapSprites->SetCurSprite("after");
            goSprite->box.SetOrigin(spritePos + shiftMap[TrapState::after]);
            break;
    }
}

void Trap::ShiftState(TrapState state, Vec2 shift) {
    shiftMap[state] = shift;
}

void Trap::AddSound(const std::string &key, const std::string &file) {
    Sound *sound = new Sound(associated, file, true);
    if (sound == nullptr) {
        std::cerr << "Tried to add sound, but is problebly does not exists: " << file << std::endl;
        exit(-1);
    }
    associated.AddComponent(sound);
    soundMap[key] = sound;
}

void Trap::PlaySound(const std::string &key, int volume) {
    if (soundMap.find(key) != soundMap.end()) {
        soundMap[key]->SetVolume(volume);
        soundMap[key]->Play();
    } else {
        std::cerr << "Trying to play a sound not in the map: " << key << std::endl;
    }
}
