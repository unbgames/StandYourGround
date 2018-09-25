#ifndef TILESET_H
#define TILESET_H

#include <iostream>

#include "Sprite.h"

class TileSet {
public:
    TileSet (GameObject& associated, std::string file, Vec2 size, Vec2 scale = {1, 1});
    ~TileSet() = default;
    void RenderTile(int index, float x, float y);
    int GetTileWidth() const;
    int GetTileHeight() const;

private:
    Sprite tileSet;
    unsigned rows;
    unsigned columns;
    int tileWidth;
    int tileHeight;
    Vec2 scale;
};

#endif /* TILESET_H */
