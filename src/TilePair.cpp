#include "../include/TilePair.h"
#include "../include/Game.h"

#include <SDL2/SDL.h>
// mapSize {height, width}
TilePair::TilePair(GameObject& associated, std::string mapFile, Vec2 mapSize,
  std::string setFile, Vec2 tileSize, Vec2 scale, int flags) :
  tileMap(mapFile, mapSize), tileSet(associated, setFile, tileSize, scale),
  mapSize(mapSize), scale(scale), tileSize(tileSize) {
}

TilePair::~TilePair() {
}

// void TilePair::Load(std::string mapFile, std::string setFile, Vec2 tileSize) {
//     tileSet = TileSet(associated, setFile, tileSize);
//     tileMap = TileMap(mapFile, mapSize);
// }

void TilePair::RenderAt(int offsetX, int offsetY) {
    int tileWidth = tileSet.GetTileWidth();
    int tileHeight = tileSet.GetTileHeight();
    // float layerFactor = std::pow(1.1, layer);
    // std::cout << "Map Size: ("<<mapSize.GetX() <<','<<mapSize.GetY()<<")"<<std::endl;
    for (unsigned int row = 0; row < mapSize.GetX(); row++) {
        for (unsigned int col = 0; col < mapSize.GetY(); col++) {
            // unsigned idx = col + row * mapSize.GetY();
            float posX = static_cast<float>((col * tileWidth * scale.GetX()) + offsetX);
            float posY = static_cast<float>((row * tileHeight * scale.GetY()) + offsetY);

            // std::cout << "Map POS(" << row <<','<< col  <<")"<<std::endl;
            int tileIdx = tileMap.GetItem(row, col);
            // std::cout << " at (" << posX <<','<< posY  <<")"<<std::endl;
            //
            // std::cout << "\n TileSize (" << tileWidth <<','<< tileHeight  <<")"<<std::endl;
            // std::cout << "\n Offset (" << offsetX <<','<< offsetY  <<")"<<std::endl;
            // std::cout <<"WTF:"<<static_cast<float>((col * tileWidth) + offsetX)<<std::endl;

            tileSet.RenderTile(tileIdx, posX, posY);
        }
        // SDL_Delay(5000);
        // SDL_RenderPresent(Game::GetInstance().GetRenderer());
    }
}

int TilePair::GetMapAt(int row, int column) const {
    return tileMap.GetItem(row, column);
}
Rect TilePair::BoxToTileBox(const Rect &box, const Vec2 &scale) const {
    // std::cout << tileSize<<std::endl;
    int left = std::ceil(box.GetX() / (tileSize.GetX() * scale.GetX()));
    int right = std::ceil((box.GetX() + box.GetW()) / (tileSize.GetX() * scale.GetX()));
    int top = std::ceil(box.GetY() / (tileSize.GetY() * scale.GetY()));
    int bottom = std::ceil((box.GetY() + box.GetH()) / (tileSize.GetY() * scale.GetY()));

    // std::cout << "Old (" << box.GetX() <<','<< box.GetY()<<','<< (box.GetX() + box.GetW()) <<','<< (box.GetY() + box.GetH())  <<")"<<std::endl;
    // std::cout << "New (" << left <<','<< top<<','<< right <<','<< bottom  <<")"<<std::endl;
    return Rect(left, top, right - left, bottom - top);
}

std::vector<int> TilePair::GetTilesAt(const Rect &box, const Vec2 &scale) const {
    std::vector<int> tiles;
    Rect tileRect = BoxToTileBox(box, scale);
    for (int i = tileRect.GetX(); i <= tileRect.GetX() + tileRect.GetW(); i++) {
        for (int j = tileRect.GetY(); j <= tileRect.GetY() + tileRect.GetH(); j++) {
            // TODO: finish using the layer
            int idx = tileMap.GetItem(j - 1, i - 1);
            // std::cout << idx;
            tiles.push_back(idx);
        }
    }
    return tiles;
}
