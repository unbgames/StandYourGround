#include "../include/Collider.h"
#include "../include/Debug.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated), scale(scale),
    offset(offset) {
}
Collider::~Collider() {
    // std::cout <<"Removed Collider"<<std::endl;
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
    #ifdef DEBUG
    if (DEBUG_COL) {
        SDL_Point points[5];

        Vec2 point = (box.Origin() - box.Center()).GetRotated(associated.angle)
                                       + box.Center() + Camera::pos;
        points[0] = {(int)point.GetX(), (int)point.GetY()};
        points[4] = {(int)point.GetX(), (int)point.GetY()};

        point = (Vec2(box.GetX() + box.GetW(), box.GetY()) - box.Center()).GetRotated(associated.angle)
                                       + box.Center() + Camera::pos;
        points[1] = {(int)point.GetX(), (int)point.GetY()};

        point = (Vec2(box.GetX() + box.GetW(), box.GetY() + box.GetH()) - box.Center()).GetRotated(associated.angle)
                                       + box.Center() + Camera::pos;

        points[2] = {(int)point.GetX(), (int)point.GetY()};

        point = (Vec2(box.GetX(), box.GetY() + box.GetH()) - box.Center()).GetRotated(associated.angle)
                                       + box.Center() + Camera::pos;
        points[3] = {(int)point.GetX(), (int)point.GetY()};

        SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 150, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
     }
     #endif // DEBUG
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
