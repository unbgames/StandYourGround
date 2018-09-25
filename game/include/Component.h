#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

#include "GameObject.h"
#include "Rect.h"

class Component {
public:
    Component(GameObject &associated);
    virtual ~Component() = default;

    virtual bool Is(std::string type) = 0;
    virtual std::string Type() = 0;
    virtual void Render() = 0;
    virtual void Update(float dt) = 0;
    virtual void Start();
    virtual void NotifyCollision(GameObject &other);

    void SetName(std::string name);
    std::string GetName();

    const Rect GetBox() const;

protected:
    GameObject &associated;
    std::string name;
    
};

#endif /* COMPONENT_H */
