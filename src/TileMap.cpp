#include <iostream>

#include "../include/TileMap.h"
#include "../include/Camera.h"

TileMap::TileMap (GameObject& associated, std::string file, TileSet *tileSet) :
    Component(associated), tileSet(tileSet) {
    Start();
    Load(file);
}

TileMap::~TileMap() {
}

bool TileMap::Is(std::string type) {
    return type == "TileMap";
}

std::string TileMap::Type() {
    return "TileMap";
}

void TileMap::Update(float dt) {

}

void TileMap::Load(std::string file) {
    FILE *fin = fopen("assets/map/tileMap.txt", "r");
    int quant=0,i;
    fscanf(fin, "%i,", &mapWidth);
    fscanf(fin, "%i,", &mapHeight);
    fscanf(fin, "%i,", &mapDepth);
    // printf("MapWidth:%d MapHeight:%d MapDepth:%d\n", mapHeight, mapWidth, mapDepth);
    while (fscanf(fin, "%d,", &i) > 0 && quant < mapHeight * mapWidth * mapDepth){
        // printf("%d ", i);
        tileMatrix.push_back(i);
        quant++;
        // if (quant%mapWidth == 0)
            // printf("\n");
    }
    // printf("Quant: %d\n", quant);
    fclose(fin);

}

void TileMap::SetTileSet(TileSet *tileSet) {
    this->tileSet = tileSet;
}

int TileMap::At(int x, int y, int z) {
    if (x < mapWidth && y < mapHeight && z < mapDepth) {
        return tileMatrix[x + y*mapHeight + z * mapHeight * mapWidth];
    } else {
        return 0;
    }
}

void TileMap::Render() {
    Vec2 pos = Camera::pos;
    for (int i = 0; i < mapDepth; i++) {
        RenderLayer(i, pos.GetX(), pos.GetY());
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    int tileWidth = tileSet->GetTileWidth();
    int tileHeight = tileSet->GetTileHeight();
    float layerFactor = std::pow(1.1, layer);
    for (int row = 0; row < mapWidth; row++) {
        for (int col = 0; col < mapWidth; col++) {
            // std::cout << '('<<r <<','<<col << ')' <<std::endl;
            unsigned idx = col + row * mapWidth + layer * mapHeight * mapWidth;
            // std::cout << "Idx(" << idx <<") = "<<tileMatrix[idx]<< " | (" << r <<','<< col <<','<< layer<<")"<<std::endl;
            float posX = (col*tileWidth) + (cameraX*layerFactor);
            float posY = (row*tileHeight) + (cameraY*layerFactor);

            tileSet->RenderTile(tileMatrix[idx], posX, posY);
            // SDL_Delay(1500);
	        // SDL_RenderPresent(Game::GetInstance().GetRenderer());
        }
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}
