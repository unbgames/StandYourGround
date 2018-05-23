#include "../include/State.h"

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
        std::cout <<"Added Object"<<std::endl;
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
        if (objectArray[i] != nullptr) {
            objectArray[i]->Update(dt);
        }
    }
}

void State::RenderArray() {
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i] != nullptr) {
            objectArray[i]->Render();
        }
    }
}
