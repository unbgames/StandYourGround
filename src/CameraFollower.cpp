#include "../include/CameraFollower.h"
#include "../include/Camera.h"
#include "../include/Vec2.h"

CameraFollower::CameraFollower(GameObject &go) : Component(go) {
}

void CameraFollower::Update(float) {
    Vec2 pos = Camera::pos;
    associated.box.SetOrigin(-pos);
}

void CameraFollower::Render() {
}

bool CameraFollower::Is(std::string type) {
    return type == "CameraFollower";
}

std::string CameraFollower::Type() {
    return "Sprite";
}
