#include "../include/Forest.h"
#include "../include/Game.h"
#include "../include/Tree.h"
#include "../include/Collider.h"
#include "../include/Totem.h"

#include <limits>
#include <fstream>
#include <sstream>

Forest* Forest::forest = nullptr;

Forest::Forest(GameObject &associated, std::string path, Vec2 tileSizeScaled)
  : Component(associated),  tileSizeScaled(tileSizeScaled) {
    Load(path, 0);
    // std::cout << treeVector.size() << std::endl;
}

Forest::Forest(GameObject &associated, std::vector<std::string> paths, Vec2 tileSizeScaled)
  : Component(associated),  tileSizeScaled(tileSizeScaled) {
  int i = 0;
  for (const std::string &path : paths) {
      Load(path, i);
      i++;
  }
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
    for (const std::tuple<int, int, int, int> &pos : treesPos) {
        auto treeObj = std::make_shared<GameObject>();
        std::cout <<"POS: ("<<std::get<0>(pos) * tileSizeScaled.GetX() << ',' <<std::get<1>(pos) * tileSizeScaled.GetY() <<')'<< std::endl;
        treeObj->layer = associated.layer;
        Tree *tree = new Tree(*treeObj, std::get<2>(pos), std::get<3>(pos));
        treeObj->AddComponent(tree);
        treeVector.push_back(treeObj);
        state.AddObject(treeObj);
        // treeObj->box.SetSize(treeObj->box.GetW(), treeObj->box.GetH());
        treeObj->box.SetOrigin(std::get<0>(pos) * tileSizeScaled.GetX(), std::get<1>(pos) * tileSizeScaled.GetY());
        Collider *colTree = new Collider(*treeObj, {0.15, 0.65}, {-3, 115});
        treeObj->AddComponent(colTree);
    }
    std::cout <<"Finished adding trees"<<std::endl;
}

void Forest::Load(std::string file_path, int type) {
    std::ifstream file(file_path);
    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        int column = 0;
        while(std::getline(lineStream, cell, ',')){
            int status = std::stoi(cell);
            // std::cout << val <<",";
            if (status != -1) {
                treesPos.push_back(std::make_tuple(column, row - 6, type, status));
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
    for (const std::tuple<int, int, int, int> &pos : treesPos) {
        Vec2 auxTreePos(std::get<0>(pos) * tileSizeScaled.GetX(), std::get<1>(pos) * tileSizeScaled.GetY());
        if (auxTreePos == treePos) {
            Totem * totem = Totem::totem;
            totem->alertTreeFall();
            std::cout << "Deleted Tree at index: " << idx << std::endl;
            break;
        }
        idx++;
    }
}
