#ifndef SKILL_BAR_H
#define SKILL_BAR_H

#include "Text.h"
#include "Component.h"
#include "Sprite.h"

class SkillBar : public Component {
    public:
        SkillBar(GameObject& associated);

        void Update(float dt);
        void Render();
        bool Is(std::string type);
        std::string Type();
        void NotifyCollision(GameObject &other);
    private:
        Text* holeKey;

        Text* bombKey;


        std::vector<GameObject*> skillList;
        std::vector<Sprite*> spriteSkillList;
        std::vector<Text*> textSkillList;
};

#endif