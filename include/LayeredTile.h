#ifndef LAYEREDTILED_H
#define LAYEREDTILED_H

#include <iostream>

#include "Component.h"
#include "TilePair.h"

class LayeredTile : public Component {
public:
    LayeredTile (GameObject& associated, std::string path, std::string file, Vec2 scale = {1, 1});
    ~LayeredTile();

    void Load(std::string file);
    int At(unsigned int x, unsigned int y, unsigned int z = 0);
    bool Is(std::string type);
    std::string Type();
    void Update(float dt);
    void Render();
    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
    int GetWidth();
    int GetHeight();
    int GetDepth();

private:
    std::string path;
    std::vector<TilePair> tileLayers;
    unsigned int mapWidth;
    unsigned int mapHeight;
    unsigned int mapDepth;
    Vec2 scale;
};

#endif /* LAYEREDTILED_H */
