#include "../include/Orc.h"
#include "../include/Elfa.h"
#include "../include/InputManager.h"
#include "../include/SpriteVector.h"

Orc* Orc::orc = nullptr;

Orc::Orc(GameObject& associated) : Character(associated,
  {Direction::esq, Facing::up, Movement::idle}) {
    hp = 100;
    speed = 100;
    AddSound("footstep", "./assets/audio/footstep.wav");
}

Orc::~Orc() {
}

void Orc::Start() {
}

void Orc::Update(float dt) {
    timer.Update(dt);
    InputManager &inp = InputManager::GetInstance();
    velX = 0;
    velY = 0;
    // Seta o state do personagem que indica qual sprite sera renderizada
    // State sera movement + facing + direction
    CharState newState = {state.dir, state.face, Movement::idle};
    if(inp.IsKeyDown(LEFT_ARROW_KEY)) {
        newState = {
            Direction::esq,
            Facing::down,
            Movement::run,
        };
        velX = -speed * dt;
    } else if(inp.IsKeyDown(RIGHT_ARROW_KEY)) {
        newState = {
            Direction::dir,
            Facing::down,
            Movement::run,
        };
        velX = speed * dt;
    } else if(inp.IsKeyDown(UP_ARROW_KEY)) {
        newState = {
            state.dir,
            Facing::up,
            Movement::run,
        };
        velY = -speed * dt;
    } else if(inp.IsKeyDown(DOWN_ARROW_KEY)) {
        newState = {
            state.dir,
            Facing::down,
            Movement::run,
        };
        velY = speed * dt;
    } else {
        // Se o run for setado somente no A e D ele nao deixa idle aqui
        state.move = Movement::idle;
    }
    Vec2 shift(velX, velY);
    if (shift.Mag() > 0) { // Is moving
        // std::cout<<"MOVING"<<std::endl;
        timer.Start();
        float elapsed = timer.Get();
        if (elapsed > 0.22 || elapsed == 0) {
            Vec2 orcPos = associated.box.Origin();
            Elfa* elfaPtr = Elfa::elfa;
            Vec2 elfPos = elfaPtr->Origin();
            int reducer = int(std::pow(Vec2::EuclidianDist(orcPos, elfPos), 2) / 4000);
            // int reducer = int(Vec2::EuclidianDist(orcPos, elfPos) / 5);
            // std::cout<<"PLAY SOUND at "<< reducer <<std::endl;
            PlaySound("footstep", 128 - std::min(reducer, 128));
            timer.Restart();
        }
    } else { // Stopped
        // std::cout<<"STOPPED"<<std::endl;
        timer.Stop();
    }
    if (newState != state) {
        state = newState;
        // std::cout<<"CHANGED STATE:"<<StateToString(state)<<std::endl;
    }
    associated.box.Shift(shift);
}

void Orc::Render() {

}

bool Orc::Is(std::string type) {
    return type == "Orc";
}

std::string Orc::Type() {
    return "Orc";
}

void Orc::NotifyCollision(GameObject &other) {

}
