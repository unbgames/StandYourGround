#include "../include/State.h"
#include <algorithm>

State::State() : popRequested(false), quitRequested(false), started(false){
}

State::~State() {
    std::cout<<"Deleting Stage"<<std::endl;
    objectArray.clear();
    std::cout<<"Deleted Stage"<<std::endl;
}

std::weak_ptr<GameObject> State::AddObject(std::weak_ptr<GameObject> go) {
    auto shared = go.lock();
    if (shared != nullptr) {
        objectArray.push_back(shared);
        if (started) {
            shared->Start();
        }
        // std::cout <<"Added Object"<<std::endl;
        return go;
    } else {
        std::cerr <<"Tried to add null GameObject"<<std::endl;
        return std::weak_ptr<GameObject>();
    }
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        if (go == objectArray[i].get()){
            return objectArray[i];
        }
    }
    return std::weak_ptr<GameObject>();
}


bool State::PopRequested() {
    return popRequested;
}

bool State::QuitRequested() {
    return quitRequested;
}


void State::StartArray() {
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i] != nullptr) {
            objectArray[i]->Start();
        }
    }
}

void State::UpdateArray(float dt) {
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
        if (objectArray[i] != nullptr) {
            if(objectArray[i]->IsDead()) {
                auto test = objectArray.begin() + i;
                int c = (*test).use_count();
                if (c > 1) {
                    std::cout<<"WARNING!!! REMOVING GO WITH USE COUNT:"<<c<<std::endl;
                }
                objectArray.erase(test);
            }
        }
    }
    // Reorder, first by layer, and than from position. Lower renders first..
    std::sort(objectArray.begin(), objectArray.end(), [] (const std::shared_ptr<GameObject> obj1,
      const std::shared_ptr<GameObject> obj2) {
        if ((*obj1).layer < (*obj2).layer) return true;
        if ((*obj1).layer > (*obj2).layer) return false;

        if ((*obj1).box.BottomLeft().GetY() < (*obj2).box.BottomLeft().GetY()) return true;
        else {
            return false;
        }
    });
}

void State::RenderArray() {
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i] != nullptr) {
            objectArray[i]->Render();
        }
    }
}

void State::Quit() {
    quitRequested = true;
}
