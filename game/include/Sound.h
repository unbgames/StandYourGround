#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>
#include <memory>

#include "Component.h"
#include "GameObject.h"

class Sound : public Component {
public:
    Sound(GameObject &associated, bool shouldReplay = false);
    Sound(GameObject &associated, std::string file, bool shouldReplay = false);
    ~Sound();

    void Play(int times = 1);
    bool Playing();
    void SetVolume(unsigned int volume);
    void Stop();
    void Open(std::string file);
    bool IsOpen();

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    std::string Type();

    bool started;

private:
    std::vector<int> channels;
    std::shared_ptr<Mix_Chunk> chunk;
    unsigned int volume;
    bool shouldReplay;
};

#endif /* SOUND_H */
