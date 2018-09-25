#ifndef MUSIC_H
#define MUSIC_H

#include <string>
#include <memory>
#include <SDL2/SDL_mixer.h>

class Music {
public:
    Music();
    Music(std::string file);
    ~Music();

    void Play(int times = -1);
    void Stop(int msToStop = 500);
    void Open(std::string file);
    bool IsOpen();

private:
    std::shared_ptr<Mix_Music> music;
};

#endif /* MUSIC_H */
