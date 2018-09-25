#include <iostream>
#include <fstream>
#include <sstream>

#include "LayeredTile.h"
#include "Camera.h"

#ifdef DEBUG
    #include "Game.h"
    #include "Debug.h"
#endif //DEBUG

LayeredTile::LayeredTile (GameObject& associated, std::string path, std::string file, Vec2 scale,
  unsigned int collideLayer) : Component(associated), path(path), scale(scale), collideLayer(collideLayer) {
    Load(path + file);
}

LayeredTile::~LayeredTile() {
    std::cout << "DELETED LAYERS" << std::endl;
}

void LayeredTile::Load(std::string file) {
    std::ifstream fileStream(file);
    std::string line;
    if (std::getline(fileStream, line)) {
        std::stringstream firstLineStream(line);
        firstLineStream >> mapHeight >> mapWidth;

        // std::cout << mapWidth <<" "<< mapHeight<<std::endl;

        mapDepth = 0;
        while (std::getline(fileStream, line)) {
            std::stringstream lineStream(line);
            std::string mapFile, setFile;
            lineStream >> mapFile >> setFile >> setWidth >> setHeight;
            // Add pair
            tileLayers.push_back(TilePair(associated, path + mapFile, {float(mapHeight), float(mapWidth)},
                path + setFile, {float(setHeight), float(setWidth)}, scale));
            std::cout << mapFile << "|" << setFile << "|" << setWidth << "|" << setHeight << std::endl;
            mapDepth++;
        }
    }
}

bool LayeredTile::Collide(const Rect &box) {
    for (const int &idx : tileLayers[collideLayer].GetTilesAt(box, scale)) {
        // std::cout << idx <<" ";
        if (idx == -1) return true;
    }
    return false;
}

int LayeredTile::At(unsigned int x, unsigned int y, unsigned int z) {
    if (x < mapWidth && y < mapHeight && z < mapDepth) {
        return tileLayers[z].GetMapAt(x, y);
    } else {
        std::cout << "Out of bounds."<<std::endl;
        return -100;
    }
}

bool LayeredTile::Is(std::string type) {
    return (type == "LayeredTile");
}

std::string LayeredTile::Type() {
    return "LayeredTile";
}

void LayeredTile::Update(float dt) {
}

void LayeredTile::Render() {
    Vec2 pos = Camera::pos;
    int cameraX = pos.GetX();
    int cameraY = pos.GetY();
    for (auto &layer : tileLayers) {
        layer.RenderAt(cameraX, cameraY);
    }
    #ifdef DEBUG
    if (DEBUG_TILE) {
        int width = int(setWidth*scale.GetX());
        int height = int(setWidth*scale.GetY());
        SDL_Point points[5];
        for (int i = 0; i < mapWidth; i++) {
            for (int j = 0; j < mapHeight; j++) {
                int x = i*width + cameraX;
                int y = j*height + cameraY;
                points[0] = {x, y};
                points[4] = {x, y};
                points[1] =  {x + width, y};
                points[2] =  {x + width, y + height};
                points[3] =  {x, y + height};
                if (tileLayers[collideLayer].GetMapAt(j, i) == -1) {
                    SDL_Rect rect;
                    rect.x = int(x);
                    rect.y = int(y);
                    rect.w = width;
                    rect.h = height;
                    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, 70);
                    SDL_RenderFillRects(Game::GetInstance().GetRenderer(), &rect, 1);
                }
                SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 70, 255, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
            }
        }
    }
    #endif // DEBUG
}

void LayeredTile::RenderLayer(int layer, int cameraX, int cameraY) {
}

int LayeredTile::GetWidth() {
    return mapWidth;
}

int LayeredTile::GetHeight() {
    return mapHeight;
}

int LayeredTile::GetDepth() {
    return mapDepth;
}
