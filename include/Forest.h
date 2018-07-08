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
    std::weak_ptr<GameObject> GetClosestTree(const Vec2 &pos) const;
    void alertDeleteTree(const Vec2 &pos);
    void alertDeleteTree(std::weak_ptr<GameObject> tree);


    static Forest* forest;

private:
    Vec2 tileSizeScaled;
    std::vector<std::pair<int, int>> treesPos;
    std::vector<std::weak_ptr<GameObject>> treeVector;

    void Load(std::string file_path);
};

#endif /* FOREST_H */
