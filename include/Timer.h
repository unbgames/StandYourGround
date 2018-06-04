#ifndef TIMER_H
#define TIMER_H

class Timer {
public:
    Timer(bool startPaused = false);

    void Update(float dt);
    void Restart();
    float Get();
    void Pause();
    void Stop();
    void Start();

private:
    float time;
    bool paused;
};

#endif /* TIMER_H */
