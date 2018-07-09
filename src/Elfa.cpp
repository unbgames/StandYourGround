#include "../include/Elfa.h"
#include "../include/InputManager.h"
#include "../include/SpriteVector.h"
#include "../include/Game.h"
#include "../include/Bomb.h"
#include "../include/Hole.h"

Elfa* Elfa::elfa = nullptr;

Elfa::Elfa(GameObject& associated) : Character(associated,
  {Direction::esq, Facing::up, Movement::idle, Action::no_action}), timer(true), picking(false), casting(false) {
    hp = 100;
    speed = 200;
    cast = false;
    AddSound("footstep", "./assets/audio/footstep_grass2.mp3");
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
    CharState newState = {state.dir, state.face, Movement::idle, Action::no_action};
    if(inp.IsKeyDown(A_KEY)) {
        newState = {
            Direction::esq,
            Facing::down,
            Movement::run,
            Action::no_action
        };
        velX = -speed * dt;
    } else if(inp.IsKeyDown(D_KEY)) {
        newState = {
            Direction::dir,
            Facing::down,
            Movement::run,
            Action::no_action
        };
        velX = speed * dt;
    } else if(inp.IsKeyDown(W_KEY)) {
        newState = {
            state.dir,
            Facing::up,
            Movement::run,
            Action::no_action
        };
        velY = -speed * dt;
    } else if(inp.IsKeyDown(S_KEY)) {
        newState = {
            state.dir,
            Facing::down,
            Movement::run,
            Action::no_action
        };
        velY = speed * dt;
    } else if(inp.IsKeyDown(SDLK_e)) {
        if(picking.Get() < 0.9) {
            std::cout << "PEGANDO" << std::endl;
            newState = {
                state.dir,
                state.face,
                state.move,
                Action::pick
            };
        }
        picking.Update(dt);
    } else if(inp.IsKeyDown(SDLK_k) && (Bag::CanUseTrap("Bomb") || state.act == Action::pick)) {
        if(!cast) {
            auto goTrap = std::make_shared<GameObject>();
            goTrap->box.SetSize(4*40, 4*20);
            goTrap->box.SetOrigin(this->associated.box.GetX(), this->associated.box.GetY()+30);
            // trapSpr->Hide();
            Bomb *bomb = new Bomb(*goTrap);
            goTrap->AddComponent(bomb);
            goTrap->layer = 2;
            Game::GetInstance().GetCurrentState().AddObject(goTrap);
            cast = true;
            Bag::UseItem(ItemType::berry, 4);
            Bag::UseItem(ItemType::cipo, 2);
        }

        if(casting.Get() < 0.9) {
            newState = {
                state.dir,
                state.face,
                state.move,
                Action::pick
            };
        } else {
            newState = {
                state.dir,
                state.face,
                state.move,
                Action::no_action
            };
        }
        casting.Update(dt);
    } else if(inp.IsKeyDown(SDLK_j) && (Bag::CanUseTrap("Hole") || state.act == Action::pick)) {
        if(!cast) {
            auto goTrap = std::make_shared<GameObject>();
            Sprite *trapSpr = new Sprite(*goTrap, "./assets/img/trap/buraco.png");
            goTrap->box.SetOrigin(this->associated.box.GetX(), this->associated.box.GetY()+30);
            trapSpr->SetScale({4, 4});
            goTrap->box.SetSize(trapSpr->GetWidth(), trapSpr->GetHeight());
            Hole *hole = new Hole(*goTrap);
            goTrap->AddComponent(hole);
            goTrap->AddComponent(trapSpr);
            goTrap->layer = 2;
            Game::GetInstance().GetCurrentState().AddObject(goTrap);
            cast = true;
            Bag::UseItem(ItemType::cipo, 2);
            Bag::UseItem(ItemType::galho, 3);
        }
        if(casting.Get() < 0.9) {
            newState = {
                state.dir,
                state.face,
                state.move,
                Action::pick
            };
        } else {
            newState = {
                state.dir,
                state.face,
                state.move,
                Action::no_action
            };
        }
        casting.Update(dt);
    }else {
        // Se o run for setado somente no A e D ele nao deixa idle aqui
        state.move = Movement::idle;
    }
    if(inp.KeyRelease(SDLK_e)) {
        picking.Restart();
    }
    if(inp.KeyRelease(SDLK_j) || inp.KeyRelease(SDLK_k)) {
        casting.Restart();
        cast = false;
    }
    Vec2 shift(velX, velY);
    if (shift.Mag() > 0) { // Is moving
        // std::cout<<"MOVING"<<std::endl;
        timer.Start();
        float elapsed = timer.Get();
        if (elapsed > 0.22 || elapsed == 0) {
            // std::cout<<"PLAY SOUND"<<std::endl;
            PlaySound("footstep", 10);
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
    oldBox = associated.box;
    associated.box.Shift(shift);
    Character::Update(dt);
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
    if(other.GetComponent("Item") != nullptr) {
        Item* item = (Item*) other.GetComponent("Item");

    } else if(other.GetComponent("Trap") != nullptr) {

    }
    else {
        associated.box = oldBox;
    }
}
