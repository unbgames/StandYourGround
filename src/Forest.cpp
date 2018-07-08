#include "../include/Forest.h"
#include "../include/Game.h"
#include "../include/Tree.h"
#include "../include/Collider.h"

#include <limits>
#include <fstream>
#include <sstream>

Forest* Forest::forest = nullptr;

Forest::Forest(GameObject &associated, std::string path, Vec2 tileSizeScaled)
  : Component(associated),  tileSizeScaled(tileSizeScaled) {
    Load(path);
    // std::cout << treeVector.size() << std::endl;
}

void Forest::Update(float dt) {
}

void Forest::Render() {
    for (auto tree : treeVector) {
        auto shared_tree = tree.lock();
        if (shared_tree != nullptr) {
            shared_tree->Render();
        }
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
    std::cout <<"Finished adding trees"<<std::endl;
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
                treesPos.push_back({column, row});
            }
            column++;
        }
        row++;
        // std::cout <<"\n";
    }
}

std::weak_ptr<GameObject> Forest::GetClosestTree(const Vec2 &pos) const {
    float max = std::numeric_limits<float>::max()/10;
    std::weak_ptr<GameObject> closestTree;
    // std::cout << treeVector.size() << std::endl;
    for (int i = 0; i < treeVector.size(); i++) {
        std::shared_ptr<GameObject> treeObj = treeVector[i].lock();
        if (treeObj != nullptr) {
            Collider *treeCollider = (Collider *) treeObj->GetComponent("Collider");
            Rect colliderBox = treeCollider->box;
            float distance = Vec2::ManhattamDist(pos, colliderBox.Center());
            if (distance < max) {
                max = distance;
                closestTree = treeVector[i];
            }
        }
    }
    return closestTree;
}

void Forest::alertDeleteTree(const Vec2 &treePos) {
    int idx = 0;
    for (const std::pair<int, int> &pos : treesPos) {
        Vec2 auxTreePos(pos.first * tileSizeScaled.GetX(), pos.second * tileSizeScaled.GetY());
        if (auxTreePos == treePos) {
            std::cout << "Deleted Tree at index: " << idx << std::endl;
            break;
        }
        idx++;
    }
}