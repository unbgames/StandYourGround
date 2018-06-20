#ifndef FOREST_H
#define FOREST_H

#include "Vec2.h"
#include "Rect.h"
#include "GameObject.h"
#include "Component.h"
#include <memory>

class Forest : public Component {
public:
    Forest(GameObject &associated, std::string path, Vec2 tileMapSize);

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    std::string Type();
    void Start();

private:
    Vec2 tileSizeScaled;
    std::vector<std::pair<int, int>> treesPos;
    std::vector<std::shared_ptr<GameObject>> treeVector;

    void Load(std::string file_path);
};

#endif /* FOREST_H */
