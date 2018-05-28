#include "../include/Orc.h"
#include "../include/InputManager.h"
#include "../include/SpriteVector.h"

Orc* Orc::orc = nullptr;

Orc::Orc(GameObject& associated) : Component(associated), 
                                     hp(100), direction("esq"), 
                                     facing("frente"), movement("idle") {
}

Orc::~Orc() {

}

void Orc::Start() {

}


void Orc::Update(float dt) {
    InputManager &inp = InputManager::GetInstance();
    velX = 0;
    velY = 0;
    // Seta o state do personagem que indica qual sprite sera renderizada
    // State sera movement + facing + direction
    if(inp.IsKeyDown(LEFT_ARROW_KEY)) {
        movement = "run";
        direction = "esq";
        facing = "frente";
        velX = -ORC_VELOCITY*dt;
    } else if(inp.IsKeyDown(RIGHT_ARROW_KEY)) {
        movement = "run";
        direction = "dir";
        facing = "frente";
        velX = ORC_VELOCITY*dt;
    } else {
        movement = "idle";
    }

    if(inp.IsKeyDown(UP_ARROW_KEY)) {
        movement = "run";
        facing = "costa";
        velY = -ORC_VELOCITY*dt;
    } else if(inp.IsKeyDown(DOWN_ARROW_KEY)) {
        movement = "run";
        facing = "frente";
        velY = ORC_VELOCITY*dt;
    } else {
        if (movement != "run") // Se o run for setado somente no A e D ele nao deixa idle aqui
            movement = "idle";
    }
    associated.box.Shift({velX, velY});
    
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

std::string Orc::GetState() {
    return movement + "_" + facing + "_" + direction;
}
