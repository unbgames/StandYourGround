#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <memory>
#include <SDL2/SDL_ttf.h>

#include "Component.h"
#include "Camera.h"

#define PI 3.14159

enum TextStyle { SOLID, SHADED, BLENDED };

class Text : public Component{
public:
    Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style,
        std::string text, SDL_Color color);
    ~Text();

    bool Is(std::string type);
    std::string Type();
    void Render();
    void RenderNoCam();
    void Render(float x, float y);
    void Update(float dt);

    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(std::string file);
    void SetFontSize(int fontSize);
    void SetClip(int x, int y, int w, int h);

private:
    void RemakeTexture();
    TTF_Font* font;
    SDL_Texture* texture;
    std::string text;
    TextStyle style;
    std::string fontFile;
    int fontSize;
    SDL_Color color;
    SDL_Color fg;
};

#endif /* TEXT_H */
