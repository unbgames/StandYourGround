#ifndef TILESET_H
#define TILESET_H

#include <iostream>

#include "Sprite.h"

class TileSet {
public:
    TileSet (GameObject& associated, std::string file, int tileWidth, int tileHeight);
    ~TileSet() = default;
    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();

private:
    Sprite tileSet;
    unsigned rows;
    unsigned columns;
    int tileWidth;
    int tileHeight;
};

#endif /* TILESET_H */
