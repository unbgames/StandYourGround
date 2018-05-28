#include "../include/Text.h"
#include "../include/Game.h"

#include <iostream>

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style,
  std::string text, SDL_Color color) : Component(associated), font(nullptr), texture(nullptr), text(text),
  style(style), fontFile(fontFile), fontSize(fontSize), color(color), fg({0, 0, 0, 0}) {
    RemakeTexture();
}

Text::~Text() {
    if (font != nullptr) {
        TTF_CloseFont(font);
    }
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

bool Text::Is(std::string type) {
    return (type == "Text");
}

std::string Text::Type() {
    return "Text";
}
void Text::Render() {
    Vec2 camPos = Camera::pos;
    Render(associated.box.GetX() + camPos.GetX(), associated.box.GetY() + camPos.GetY());
}
void Text::Render(float x, float y) {
    SDL_Rect clipRect = associated.box.toSDL();
    SDL_Rect dstRect;

    clipRect.x = 0;
    clipRect.y = 0;

    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;
    if (texture == nullptr) {
        std::cerr << "Error Text: Trying to render null texture." <<std::endl;
    }

    // std::cout <<"CLIP RECT : ("<< clipRect.x <<','<< clipRect.y <<','<< clipRect.w <<','<< clipRect.h <<')'<<std::endl;
    // std::cout <<"DEST RECT : ("<< dstRect.x <<','<< dstRect.y <<','<< dstRect.w <<','<< dstRect.h <<')'<<std::endl;
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angle*180/PI,
        nullptr, SDL_FLIP_NONE);
    #ifdef DEBUG
    	SDL_Point points[5];

    	Vec2 point = (associated.box.Origin() - associated.box.Center()).GetRotated( associated.angle )
    					+ associated.box.Center() + Camera::pos;
    	points[0] = {(int)point.GetX(), (int)point.GetY()};
    	points[4] = {(int)point.GetX(), (int)point.GetY()};

    	point = (Vec2(associated.box.GetX() + associated.box.GetW(), associated.box.GetY()) - associated.box.Center()).GetRotated( associated.angle)
    					+ associated.box.Center() + Camera::pos;
    	points[1] = {(int)point.GetX(), (int)point.GetY()};

    	point = (Vec2(associated.box.GetX() + associated.box.GetW(), associated.box.GetY() + associated.box.GetH()) - associated.box.Center()).GetRotated( associated.angle)
    					+ associated.box.Center() + Camera::pos;
    	points[2] = {(int)point.GetX(), (int)point.GetY()};

    	point = (Vec2(associated.box.GetX(), associated.box.GetY() + associated.box.GetH()) - associated.box.Center()).GetRotated( associated.angle)
    					+ associated.box.Center() + Camera::pos;
    	points[3] = {(int)point.GetX(), (int)point.GetY()};

    	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 100, 255, 100, SDL_ALPHA_OPAQUE);
    	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
    #endif // DEBUG
}

void Text::Update(float dt) {
}

void Text::SetText(std::string t) {
    text = t;
}

void Text::SetColor(SDL_Color c) {
    color = c;
}

void Text::SetStyle(TextStyle s) {
    style = s;
}

void Text::SetFontFile(std::string f) {
    fontFile = f;
}

void Text::SetFontSize(int s) {
    fontSize = s;
}

void Text::RemakeTexture() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    if (font != nullptr) {
        TTF_CloseFont(font);
    }
    font = TTF_OpenFont(fontFile.c_str(), fontSize);

    SDL_Surface* surface;
    switch(style) {
        case SOLID:
            surface = TTF_RenderText_Solid(font, text.c_str(), color);
        break;
        case SHADED:
            surface = TTF_RenderText_Shaded(font, text.c_str(), color, fg);
        break;
        case BLENDED:
            surface = TTF_RenderText_Blended(font, text.c_str(), color);
        break;
    }
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    SDL_FreeSurface(surface);

    int w, h;
    if (SDL_QueryTexture(texture, nullptr, nullptr, &w, &h) != 0) { // error
        SDL_DestroyTexture(texture);
        std::cerr << "Error Sprite SDL: " << SDL_GetError() << std::endl;
        return;
    }
    associated.box.SetSize(w, h);
    // std::cout <<'('<< clipRect.w <<','<< clipRect.h <<')'<<std::endl;
}
