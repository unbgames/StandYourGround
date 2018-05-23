#include "../include/Camera.h"
#include "../include/Game.h"

Vec2 Camera::pos(0, 0);
Vec2 Camera::speed(0, 0);
std::weak_ptr<GameObject> Camera::focus = std::weak_ptr<GameObject>();
void Camera::Follow(std::weak_ptr<GameObject> newFocus) {
    Camera::focus = newFocus;
}

void Camera::Unfollow() {
    Camera::focus = std::weak_ptr<GameObject>();
}

void Camera::Update(float dt) {
    Vec2 size = Game::GetInstance().GetWindowSize();
    auto obj = Camera::focus.lock();
    if (obj != nullptr) {
        pos = size/2 - obj->box.Center();
    }
}
