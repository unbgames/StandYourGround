#include "../include/Elfa.h"
#include "../include/InputManager.h"
#include "../include/SpriteVector.h"

Elfa* Elfa::elfa = nullptr;

Elfa::Elfa(GameObject& associated) : Character(associated,
  {Direction::esq, Facing::up, Movement::idle}), timer(true) {
    hp = 100;
    speed = 100;
    AddSound("footstep", "./assets/audio/footstep.wav");
}

Elfa::~Elfa() {
}

void Elfa::Start() {
}

void Elfa::Update(float dt) {
    timer.Update(dt);
    InputManager &inp = InputManager::GetInstance();
    velX = 0;
    velY = 0;
    // Seta o state do personagem que indica qual sprite sera renderizada
    // State sera movement + facing + direction
    CharState newState = {state.dir, state.face, Movement::idle};
    if(inp.IsKeyDown(A_KEY)) {
        newState = {
            Direction::esq,
            Facing::down,
            Movement::run,
        };
        velX = -speed * dt;
    } else if(inp.IsKeyDown(D_KEY)) {
        newState = {
            Direction::dir,
            Facing::down,
            Movement::run,
        };
        velX = speed * dt;
    } else if(inp.IsKeyDown(W_KEY)) {
        newState = {
            state.dir,
            Facing::up,
            Movement::run,
        };
        velY = -speed * dt;
    } else if(inp.IsKeyDown(S_KEY)) {
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
            // std::cout<<"PLAY SOUND"<<std::endl;
            PlaySound("footstep");
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

void Elfa::Render() {

}

bool Elfa::Is(std::string type) {
    return type == "Elfa";
}

std::string Elfa::Type() {
    return "Elfa";
}

void Elfa::NotifyCollision(GameObject &other) {

}
