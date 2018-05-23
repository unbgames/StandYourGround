#include "../include/Collider.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated), scale(scale),
    offset(offset) {
}

void Collider::Update(float dt) {
    box = associated.box;

    // std::cout<<"BEFORE:"<<box.GetX()<<" "<<box.GetY()<<" "<<box.GetW()<<" "<<box.GetH()<<std::endl;
    box.SetScale(scale);
    box.SetCenter(associated.box.Center());
    offset.Rotate(associated.angle);
    box.Shift(offset);
    // std::cout<<"AFTER:"<<box.GetX()<<" "<<box.GetY()<<" "<<box.GetW()<<" "<<box.GetH()<<std::endl;
}

void Collider::Render() {

}

bool Collider::Is(std::string type) {
    return (type == "Collider");
}

std::string Collider::Type() {
    return "Collider";
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}
