#include "InputManager.h"
#include <SDL2/SDL.h>

InputManager& InputManager::GetInstance() {
    static InputManager manager;
    return manager;
}

InputManager::InputManager () {
}

InputManager::~InputManager() {
}

void InputManager::Update(float) {
    SDL_Event event;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);
    updateCounter++;
	while (SDL_PollEvent(&event)) {
		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
            std::cout<<"SAIUUU ";
			quitRequested = true;
		}
		if(event.type == SDL_MOUSEBUTTONUP) {
            // if (event.button.button == RIGHT_MOUSE_BUTTON) std::cout<<"MOVE UP"<<std::endl;
            mouseUpdate[event.button.button] = updateCounter;
            mouseState[event.button.button] = false;
        }
		if(event.type == SDL_MOUSEBUTTONDOWN) {
            // if (event.button.button == RIGHT_MOUSE_BUTTON) std::cout<<"MOVE DOWN"<<std::endl;
            if (!mouseState[event.button.button]){
                mouseUpdate[event.button.button] = updateCounter;
                mouseState[event.button.button] = true;
            }
        }
        if (event.type == SDL_KEYUP) {
            keyUpdate[event.key.keysym.sym] = updateCounter;
            keyState[event.key.keysym.sym] = false;
        }
		if (event.type == SDL_KEYDOWN) {
            if (keyState.find(event.key.keysym.sym) == keyState.end()){
                keyUpdate[event.key.keysym.sym] = updateCounter;
                keyState[event.key.keysym.sym] = true;
            } else if (!keyState[event.key.keysym.sym]){
                keyUpdate[event.key.keysym.sym] = updateCounter;
                keyState[event.key.keysym.sym] = true;
            }
        }
    }
}

bool InputManager::KeyPress(int key) {
    return (keyState.find(key) != keyState.end() && keyUpdate.at(key) == updateCounter && keyState.at(key));
}

bool InputManager::KeyRelease(int key) {
    return (keyState.find(key) != keyState.end() && !keyState.at(key));
}

bool InputManager::IsKeyDown(int key) {
    if (keyState.find(key) != keyState.end()) {
        return keyState.at(key);
    }
    return false;
}

bool InputManager::MousePress(int button) {
    // if (button == RIGHT_MOUSE_BUTTON) std::cout<<"CHECK"<<std::endl;
    return (mouseState[button] && mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button) {
    return !mouseState[button];
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}
