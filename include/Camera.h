#ifndef CAMERA_H
#define CAMERA_H

#include "./Vec2.h"
#include "./GameObject.h"
#include <memory>

class Camera {
public:
    static void Follow(std::weak_ptr<GameObject> newFocus);
    static void Unfollow();
    static void Update(float dt);

    static Vec2 pos;
    static Vec2 speed;

private:
    static std::weak_ptr<GameObject> focus;
};

#endif /* CAMERA_H */
