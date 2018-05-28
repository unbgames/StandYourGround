#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/TileMap.h"
#include "../include/Camera.h"

TileMap::TileMap (std::string file, Vec2 mapSize) : mapHeight(mapSize.GetX()), mapWidth(mapSize.GetY()) {
    Load(file);
}

TileMap::~TileMap() {
}

void TileMap::Load(std::string file_name) {
    std::ifstream file(file_name);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        while(std::getline(lineStream, cell, ',')){
            int val = std::stoi(cell);
            // std::cout << val <<",";
            tileMatrix.push_back(val);
        }
        // std::cout <<"\n";
    }
}

int TileMap::GetItem(unsigned int row, unsigned int column) const {
    // std::cout<<"Width:"<<mapWidth<<std::endl;
    unsigned idx = column + row * mapWidth;
    return tileMatrix.at(idx);
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}
