#include "../include/Totem.h"

Totem::Totem(GameObject& associated) : Component(associated) {
}
Totem::~Totem() {
}
void Totem::Start() {
}
void Totem::Update(float dt) {
}
void Totem::Render() {
}
bool Totem::Is(std::string type) {
}
std::string Totem::Type() {
}
void Totem::NotifyCollision(GameObject &other) {
}
