#ifndef TILEPAIR_H
#define TILEPAIR_H

#include <iostream>

#include "TileMap.h"
#include "TileSet.h"

enum TileProperties {
    COLLISION = 1 << 0,
};

class TilePair {
public:
    TilePair(GameObject& associated, std::string mapFile, Vec2 mapSize,
      std::string setFile, Vec2 tileSize, Vec2 scale = {1, 1}, int flags = 0);
    ~TilePair();

    void RenderAt(int offsetX, int offsetY);
    int GetMapAt(int row, int columns) const;
    std::vector<int> GetTilesAt(const Rect &box, const Vec2 &scale) const;

private:
    std::string mapFile;
    std::string setFile;
    TileMap tileMap;
    TileSet tileSet;
    Vec2 mapSize;
    Vec2 scale;
    Vec2 tileSize;

    Rect BoxToTileBox(const Rect &box, const Vec2 &scale) const;
};

#endif /* TILEPAIR_H */
