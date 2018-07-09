#ifndef SPRITE_VECTOR_H
#define SPRITE_VECTOR_H

#include <iostream>
#include <unordered_map>
#include <string>
#include "Component.h"
#include "Sprite.h"

/*
    Um unico componente com varias sprites,
    elas ficam em um dicionario em que a chave
    eh o nome da sprite.
*/
class SpriteVector : public Component {
    public:
        SpriteVector(GameObject& associated);
        ~SpriteVector();

        // Adicionar uma sprite seta o currentSprite
        // para ela
        void AddSprite(std::string key, std::string file, int frameCount = 1, float frameTime = 1,
                       float secondsToSelfDestruct = 0, Vec2 scale = {1, 1});

        void SetCurSprite(std::string currentSprite);
        void ResetFrameCount();
        Sprite *GetCurSprite();

        bool Is(std::string type);
        std::string Type();
        void Render();
        void Render(float x, float y);
        void Update(float dt);
        void Hide();
        void Show();
        void Opacity(float percent);

    private:
        std::unordered_map<std::string, Sprite *> sprites;
        std::string currentSprite;
        int opacity;
        bool hide;
};

#endif /* SPRITEVECTOR_H */
