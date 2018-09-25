#include "Orc.h"
#include "Elfa.h"
#include "InputManager.h"
#include "SpriteVector.h"
#include "Collider.h"
#include "Tree.h"
#include "Totem.h"
#include "config.h"

Orc* Orc::orc = nullptr;

Orc::Orc(GameObject& associated) : Character(associated,
  {Direction::esq, Facing::up, Movement::idle, Action::no_action}), forest(Forest::forest) {
    hp = 100;
    speed = 100;
    AddSound("footstep", ASSETS_PATH("/audio/footstep_grass.wav"));
    hitTree = false;
    firstHit = true;
    damage = 10;
    onTrap = false;
    prevOnTrap = false;
}

Orc::~Orc() {
}

void Orc::Start() {
}

void Orc::Update(float dt) {
    footstepTimer.Update(dt);
    InputManager &inp = InputManager::GetInstance();
    velX = 0;
    velY = 0;
    // Seta o state do personagem que indica qual sprite sera renderizada
    // State sera movement + facing + direction
    CharState newState = {state.dir, state.face, Movement::idle, Action::no_action};
    Collider *orcColl = (Collider *) associated.GetComponent("Collider");

    if (onTrap) { // Check if fell on trap
        if (trap != nullptr) {
            associated.box.SetCenter(trap->GetCenter() + (associated.box.Center() - orcColl->box.Center()));
            Character::HideSprite(trap->ShouldHide());
            if (!prevOnTrap) {
                trap->StartTrap();
            }
            if (!trap->IsTrapped()) {
                onTrap =  false;
                velX = trap->GetShiftAfter().GetX();
                velY = trap->GetShiftAfter().GetY();
                Character::HideSprite(false);
                trap->StopTrap();
                trap = nullptr;
            }
        } else {
            std::cout << "TRAP DELETED BEFORE IT COULD BE CHECKED"<<std::endl;
            onTrap =  false;
        }
    } else {
        Totem *totem = Totem::totem;
        if (!totem->canAttack()) {
            std::shared_ptr<GameObject> tree = tree_w.lock();
            if (tree == nullptr) { // Get new tree
                if (forest != nullptr) {
                    std::cout << "GOT TREE"<<std::endl;
                    tree_w = forest->GetClosestTree(orcColl->box.Center());
                    hitTree = false;
                } else {
                    std::cout << "NULL FOREST"<<std::endl;
                    forest = Forest::forest;
                }
            } else {
                //speed * dt
                Collider *coll = (Collider *) tree->GetComponent("Collider");
                Rect colBox = coll->box;
                Vec2 diff = colBox.Center() - orcColl->box.Center();
                if (!hitTree) { // Is far to the tree diagonal.
                    firstHit = true;
                    chopTimer.Restart(); // Chopp stop.
                    // std::cout << "Diff: "<<diff<<std::endl;
                    if (std::abs(diff.GetY()) > speed * dt) { // Still has to walk on Y
                        if ((diff.GetY() > 0)) { // Going down
                            newState = {
                                Direction::dir,
                                Facing::down,
                                Movement::run,
                            };
                            velY = speed * dt;
                        } else {// Going up
                            newState = {
                                state.dir,
                                Facing::up,
                                Movement::run,
                            };
                            velY = -speed * dt;
                        }
                    } else { // Still has to walk on X
                        if ((diff.GetX() > 0)) { // Going right
                            newState = {
                                Direction::dir,
                                Facing::down,
                                Movement::run,
                            };
                            velX = speed * dt;
                        } else {// Going left
                            newState = {
                                Direction::esq,
                                Facing::down,
                                Movement::run,
                            };
                            velX = -speed * dt;
                        }
                    }
                } else { // Is close to the tree.
                    float time = 0;
                    if (firstHit) {
                        time = 0.1*2.5;
                    } else {
                        time = 0.1*5;
                    }
                    chopTimer.Update(dt);
                    newState.act = Action::atq;
                    Tree *tComp = (Tree*) tree->GetComponent("Tree");
                    if (chopTimer.Get() > time && tComp != nullptr) {
                        std::cout<<"HIT TREE"<<std::endl;
                        tComp->Damage(damage);
                        chopTimer.Restart();
                        firstHit = false;
                    }
                }
            }
        } else { // TOTEMMMMMM
            Vec2 diff = totem->Center() - orcColl->box.Center();
            if (!hitTotem) { // Is far to the totem diagonal.
                firstHit = true;
                chopTimer.Restart(); // Chopp stop.
                // std::cout << "Diff: "<<diff<<std::endl;
                if (std::abs(diff.GetY()) > speed * dt) { // Still has to walk on Y
                    if ((diff.GetY() > 0)) { // Going down
                        newState = {
                            Direction::dir,
                            Facing::down,
                            Movement::run,
                        };
                        velY = speed * dt;
                    } else {// Going up
                        newState = {
                            state.dir,
                            Facing::up,
                            Movement::run,
                        };
                        velY = -speed * dt;
                    }
                } else { // Still has to walk on X
                    if ((diff.GetX() > 0)) { // Going right
                        newState = {
                            Direction::dir,
                            Facing::down,
                            Movement::run,
                        };
                        velX = speed * dt;
                    } else {// Going left
                        newState = {
                            Direction::esq,
                            Facing::down,
                            Movement::run,
                        };
                        velX = -speed * dt;
                    }
                }
            } else if (!totem->IsDead()) { // Is close to the totem.
                float time = 0;
                if (firstHit) {
                    time = 0.1*2.5;
                } else {
                    time = 0.1*5;
                }
                chopTimer.Update(dt);
                newState.act = Action::atq;
                if (chopTimer.Get() > time && totem != nullptr) {
                    std::cout<<"HIT TREE"<<std::endl;
                    totem->Damage(damage);
                    chopTimer.Restart();
                    firstHit = false;
                }
            }
        }
    }
    /*if(inp.IsKeyDown(LEFT_ARROW_KEY)) {
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
    } else if(inp.IsKeyDown(SPACE_KEY)) {
        newState.act = Action::atq;
    } else {
        // Se o run for setado somente no A e D ele nao deixa idle aqui
        state.move = Movement::idle;
    }*/

    Vec2 shift(velX, velY);
    if (shift.Mag() > 0) { // Is moving
        // std::cout<<"MOVING"<<std::endl;
        footstepTimer.Start();
        float elapsed = footstepTimer.Get();
        if (elapsed > 0.22 || elapsed == 0) {
            Vec2 orcPos = associated.box.Origin();
            Elfa* elfaPtr = Elfa::elfa;
            Vec2 elfPos = elfaPtr->Origin();
            unsigned int maxVolume = 128;
            unsigned int reducer = int(std::pow(Vec2::EuclidianDist(orcPos, elfPos), 2) / 4000);
            // int reducer = int(Vec2::EuclidianDist(orcPos, elfPos) / 5);
            // std::cout<<"PLAY SOUND at "<< reducer <<std::endl;
            PlaySound("footstep", maxVolume - std::min(reducer, maxVolume));
            footstepTimer.Restart();
        }
    } else { // Stopped
        // std::cout<<"STOPPED"<<std::endl;
        footstepTimer.Stop();
    }
    if (newState != state) {
        state = newState;
        // std::cout<<"CHANGED STATE:"<<StateToString(state)<<std::endl;
    }
    oldBox = associated.box;
    associated.box.Shift(shift);
    prevOnTrap = onTrap;
    Character::Update(dt);
}

void Orc::Render() {

}

bool Orc::Is(std::string type) {
    return type == "Orc";
}

std::string Orc::Type() {
    return "Orc";
}

void Orc::NotifyCollision(GameObject &object) {
    Tree *colTree = (Tree *) object.GetComponent("Tree");
    if(colTree != nullptr) {
        std::shared_ptr<GameObject> tree = tree_w.lock();
        if (tree != nullptr && tree.get() == &object) {
            // std::cout<<"PODE BATER"<<std::endl;
            hitTree = true;
        } else {
            std::cout<<"NÃO É A MESMA ARVORE"<<std::endl;
        }
    }
    auto trapAux = (Trap *) object.GetComponent("Trap");
    if(trapAux != nullptr) {
        trap = trapAux;
        // std::cout << "TRAAAAP" << std::endl;
        onTrap = true;
    }
    auto totem = (Totem *) object.GetComponent("Totem");
    if(totem != nullptr) {
        std::cout << "TOTEM" << std::endl;
        hitTotem = true;
    }
    if(object.GetComponent("Item") == nullptr) {
        associated.box = oldBox;
    }
}
