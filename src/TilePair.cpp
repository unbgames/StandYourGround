#include "../include/TilePair.h"
#include "../include/Game.h"

#include <SDL2/SDL.h>
// mapSize {height, width}
TilePair::TilePair(GameObject& associated, std::string mapFile, Vec2 mapSize,
  std::string setFile, Vec2 tileSize, Vec2 scale, int flags) :
  tileMap(mapFile, mapSize), tileSet(associated, setFile, tileSize, scale),
  mapSize(mapSize), scale(scale) {
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
            unsigned idx = col + row * mapSize.GetY();
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
