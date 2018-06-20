#include "../include/Forest.h"
#include "../include/Game.h"
#include "../include/Tree.h"
#include "../include/Collider.h"

#include <fstream>
#include <sstream>

Forest::Forest(GameObject &associated, std::string path, Vec2 tileSizeScaled)
  : Component(associated),  tileSizeScaled(tileSizeScaled) {
    Load(path);
}

void Forest::Update(float dt) {
}

void Forest::Render() {
    for (auto tree : treeVector) {
        tree->Render();
    }
}

bool Forest::Is(std::string type) {
    return ("Forest" == type);
}

std::string Forest::Type() {
    return "Forest";
}

void Forest::Start() {
    std::cout << "Started Forest"<<std::endl;
    auto &state = Game::GetInstance().GetCurrentState();
    for (const std::pair<int, int> &pos : treesPos) {
        auto treeObj = std::make_shared<GameObject>();
        std::cout <<"POS: ("<<pos.first * tileSizeScaled.GetX() << ',' <<pos.second * tileSizeScaled.GetY() <<')'<< std::endl;
        treeObj->layer = 2;
        Tree *tree = new Tree(*treeObj);
        treeObj->AddComponent(tree);
        treeVector.push_back(treeObj);
        state.AddObject(treeObj);
        treeObj->box.SetSize(treeObj->box.GetW(), treeObj->box.GetH());
        treeObj->box.SetOrigin(pos.first * tileSizeScaled.GetX(), pos.second * tileSizeScaled.GetY());
        Collider *colTree = new Collider(*treeObj, {0.15, 0.65}, {-3, 115});
        treeObj->AddComponent(colTree);
    }
}

void Forest::Load(std::string file_path) {
    std::ifstream file(file_path);
    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        int column = 0;
        while(std::getline(lineStream, cell, ',')){
            int val = std::stoi(cell);
            // std::cout << val <<",";
            if (val != -1) {
                treesPos.push_back({row, column});
            }
            column++;
        }
        row++;
        // std::cout <<"\n";
    }
}
