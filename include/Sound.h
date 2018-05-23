#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>
#include <memory>

#include "Component.h"
#include "GameObject.h"

class Sound : public Component {
public:
    Sound(GameObject &associated);
    Sound(GameObject &associated, std::string file);
    ~Sound();

    void Play(int times = 1);
    bool Playing();
    void Stop();
    void Open(std::string file);
    bool IsOpen();

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    std::string Type();

private:
    std::shared_ptr<Mix_Chunk> chunk;
    int channel;
};

#endif /* SOUND_H */
