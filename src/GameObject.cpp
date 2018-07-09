#include <string>
#include <vector>
#include <iostream>

#include "../include/Component.h"
#include "../include/GameObject.h"
#include "../include/Debug.h"

GameObject::GameObject() : angle(0), isDead(false), started(false) {
}

GameObject::~GameObject() {
    for (Component *cmp : components) {
        delete cmp;
    }
    // std::cout<<"Delete"<<std::endl;
    //std::cout<<"Delete isDead:"<<((isDead)?"True":"False")<<std::endl;
}

void GameObject::Update(float dt) {
    //std::cerr << "Size Components:"<<components.size()<<std::endl;
    //std::cout<<"Update isDead:"<<((isDead)?"True":"False")<<std::endl;
    // std::cout<<"Update GO"<<std::endl;
    for (int i = 0; i < components.size(); i++) {
        if (components[i] != nullptr) {
            // std::cout<<"Update Component:"<< components[i]->Type() <<std::endl;
            components[i]->Update(dt);
        }
    }

}

void GameObject::Render() {
    for (Component *cmp : components) {
        if (cmp != nullptr) {
            cmp->Render();
        }
    }

    #ifdef DEBUG
    if (DEBUG_GO) {
    	SDL_Point points[5];

    	Vec2 point = (box.Origin() - box.Center()).GetRotated(angle )
    					+ box.Center() + Camera::pos;
    	points[0] = {(int)point.GetX(), (int)point.GetY()};
    	points[4] = {(int)point.GetX(), (int)point.GetY()};

    	point = (Vec2(box.GetX() + box.GetW(), box.GetY()) - box.Center()).GetRotated(angle)
    					+ box.Center() + Camera::pos;
    	points[1] = {(int)point.GetX(), (int)point.GetY()};

    	point = (Vec2(box.GetX() + box.GetW(), box.GetY() + box.GetH()) - box.Center()).GetRotated(angle)
    					+ box.Center() + Camera::pos;

        points[2] = {(int)point.GetX(), (int)point.GetY()};

    	point = (Vec2(box.GetX(), box.GetY() + box.GetH()) - box.Center()).GetRotated(angle)
    					+ box.Center() + Camera::pos;
    	points[3] = {(int)point.GetX(), (int)point.GetY()};

    	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 70, 255, SDL_ALPHA_OPAQUE);
    	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
    }
    #endif // DEBUG
    //std::cout<<"Render isDead:"<<((isDead)?"True":"False")<<std::endl;
}

bool GameObject::IsDead() {
    if (isDead) {
        // std::cout<<"DEEEEAD"<<std::endl;
    }
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
    // std::cout<<"ReqDelete isDead:"<<((isDead)?"True":"False")<<std::endl;
}

void GameObject::AddComponent(Component *cpt) {
    // std::cout<<"AddCmp: "<< cpt->Type() <<std::endl;
    components.push_back(cpt);
    if (started) {
        cpt->Start();
    }
}

void GameObject::RemoveComponent(Component *cpt) {
    std::vector<Component*>::iterator i =  components.begin();
    while (i != components.end()) {
        if (*i == cpt){
            delete *i;
            components.erase(i);
            break;
        }
        i++;
    }
    //std::cout<<"RemComp isDead:"<<((isDead)?"True":"False")<<std::endl;
}

Component *GameObject::GetComponent(std::string type) {
    for (Component *cmp : components) {
        if (cmp->Is(type)) {
            return cmp;
        }
    }
    //std::cout<<"GetCmp isDead:"<<((isDead)?"True":"False")<<std::endl;
    return nullptr;
}

Component *GameObject::GetComponentByName(std::string name) {
    for (Component *cmp : components) {
        if (cmp->GetName() == name) {
            return cmp;
        }
    }
    //std::cout<<"GetCmp isDead:"<<((isDead)?"True":"False")<<std::endl;
    return nullptr;
}

bool GameObject::HasComponent(std::string type) {
    for (Component *cmp : components) {
        if (cmp->Is(type)) {
            return true;
        }
    }
    //std::cout<<"GetCmp isDead:"<<((isDead)?"True":"False")<<std::endl;
    return false;
}

void GameObject::Start() {
    for (auto cmp : components) {
        if (cmp != nullptr) {
            cmp->Start();
        } else {
            std::cout<<"BAD COMPONENT"<<std::endl;
        }
    }
}

void GameObject::NotifyCollision(GameObject &other) {
    for (auto cmp : components) {
        // std::cout<<"Notify collision of:"<<cmp->Type()<<std::endl;
        cmp->NotifyCollision(other);
    }
}
