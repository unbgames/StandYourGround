#include "../include/GameTimer.h"

GameTimer::GameTimer(GameObject& associated, int startingMin, int startingSec) : Component(associated), 
                                                                                 timeText(new Text(associated, "./assets/font/pixel.ttf", 80, TextStyle::SOLID, "5:00", {0, 0, 0, 0})) {
    min = startingMin;
    sec = startingSec;
}

std::string TimeInStr(int min, int sec) {
    return std::to_string(min) + ":" + (sec >= 10 ?  "" : "0") + std::to_string(sec);
}

void GameTimer::Start() {
    timer.Restart();
    timer.Start();
    timeText->SetText(TimeInStr(min, sec));    
}

void GameTimer::Update(float dt) {
    timer.Update(dt);
    if(timer.Get() >= 1) {
        sec--;
        if(sec < 0) {
            sec = 59;
            min--;
        }
        timer.Restart();
        // Problema, o tamanho da box muda pra determinados valores de tempo
        // e ai o texto se mexe as vezes. O problema ta no setSize do RemakeTexture
        timeText->SetText(TimeInStr(min, sec));

    } 
}

void GameTimer::Render() {
    timeText->Render(associated.box.GetX(), associated.box.GetW());
}

bool GameTimer::Is(std::string type) {
    return type == "GameTimer";
}

std::string GameTimer::Type() {
    return "GameTimer";    
}

void GameTimer::NotifyCollision(GameObject &other) {
    
}

bool GameTimer::gameOver() {
    return min == 0 && sec == 0;
}