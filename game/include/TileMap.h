#ifndef TILEMAP_H
#define TILEMAP_H

#include <iostream>

#include "Vec2.h"
#include "TileSet.h"

class TileMap {
public:
    TileMap (std::string file, Vec2 mapSize);
    ~TileMap();
    void Load(std::string file);
    int GetWidth();
    int GetHeight();
    int GetItem(unsigned int row, unsigned int column) const;

private:
    std::vector<int> tileMatrix;
    TileSet *tileSet;
    int mapWidth;
    int mapHeight;
};

#endif /* TILEMAP_H */
