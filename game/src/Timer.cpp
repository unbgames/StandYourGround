#include "Timer.h"

Timer::Timer(bool startPaused) : time(0), paused(startPaused){
}

void Timer::Update(float dt) {
    if (!paused) {
        time += dt;
    }
}

void Timer::Restart() {
    time = 0;
}

float Timer::Get() {
    return time;
}

void Timer::Pause() {
    paused = true;
}

void Timer::Stop() {
    paused = true;
    time = 0;
}

void Timer::Start() {
    paused = false;
}
