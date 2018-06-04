#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/LayeredTile.h"
#include "../include/Camera.h"

LayeredTile::LayeredTile (GameObject& associated, std::string path, std::string file, Vec2 scale) : Component(associated),
    path(path), scale(scale) {
    Load(path + file);
}

LayeredTile::~LayeredTile() {
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
            int setWidth, setHeight;
            lineStream >> mapFile >> setFile >> setWidth >> setHeight;
            // Add pair
            tileLayers.push_back(TilePair(associated, path + mapFile, {float(mapHeight), float(mapWidth)},
                path + setFile, {float(setHeight), float(setWidth)}, scale));
            std::cout << mapFile << "|" << setFile << "|" << setWidth << "|" << setHeight << std::endl;
            mapDepth++;
        }
    }
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
