#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define A_KEY               SDLK_a
#define D_KEY               SDLK_d
#define W_KEY               SDLK_w
#define S_KEY               SDLK_s
#define SPACE_KEY           SDLK_SPACE
#define ESCAPE_KEY          SDLK_ESCAPE

#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON  SDL_BUTTON_RIGHT

#include <unordered_map>
#include <iostream>

class InputManager {
public:
    void Update(float dt);
    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);

    static InputManager& GetInstance();

    int GetMouseX();
    int GetMouseY();

    bool QuitRequested();

private:
    InputManager ();
    ~InputManager();
    bool mouseState[6];
    int mouseUpdate[6];

    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;

    bool quitRequested;
    int updateCounter;
    int mouseX;
    int mouseY;
};

#endif /* INPUTMANAGER_H */
