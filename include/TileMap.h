#ifndef TILEMAP_H
#define TILEMAP_H

#include <iostream>

#include "Component.h"
#include "TileSet.h"

class TileMap : public Component {
public:
    TileMap (GameObject& associated, std::string file, TileSet *tileSet);
    ~TileMap();
    void Load(std::string file);
    void SetTileSet(TileSet *tileSet);
    int At(int x, int y, int z = 0);
    bool Is(std::string type);
    std::string Type();
    void Update(float dt);
    void Render();
    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
    int GetWidth();
    int GetHeight();
    int GetDepth();

private:
    std::vector<int> tileMatrix;
    TileSet *tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
};

#endif /* TILEMAP_H */
