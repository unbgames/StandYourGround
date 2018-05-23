#include "../include/Component.h"
#include <iostream>

Component::Component(GameObject &assoc) : associated(assoc) {
    //std::cout<<"Component GO addr:"<<&assoc<<std::endl;
}

void Component::Start() {
    // std::cout<<"Started Componend WITHOUT Start"<<std::endl;
}

void Component::NotifyCollision(GameObject &other) {
    // std::cout<<"Collision Undetected from:"<<&associated<<std::endl;
}
const Rect Component::GetBox() const {
    return associated.box;
}
