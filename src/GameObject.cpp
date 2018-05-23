#include <string>
#include <vector>
#include <iostream>

#include "../include/Component.h"
#include "../include/GameObject.h"

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
    for (Component *cmp : components) {
        if (cmp != nullptr) cmp->Update(dt);
    }
}

void GameObject::Render() {
    for (Component *cmp : components) {
        if (cmp != nullptr) cmp->Render();
    }
    //std::cout<<"Render isDead:"<<((isDead)?"True":"False")<<std::endl;
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
    //std::cout<<"ReqDelete isDead:"<<((isDead)?"True":"False")<<std::endl;
}

void GameObject::AddComponent(Component *cpt) {
    // std::cout<<"AddCmp "<< cpt <<std::endl;
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
