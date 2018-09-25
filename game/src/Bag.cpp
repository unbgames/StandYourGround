#include "Bag.h"


int Bag::cipo = 0;
int Bag::berry = 0;
int Bag::flor = 0;
int Bag::galho = 0;



void Bag::PickItem(ItemType type, int amount) {
    switch(type) {
        case ItemType::cipo:
            cipo+=amount;
            break;
        case ItemType::berry:
            berry+=amount;
            break;
        case ItemType::flor:
            flor+=amount;
            break;
        case ItemType::galho:
            galho+=amount;
            break;
    }
    std::cout << "Berry: " << berry << std::endl;
}

int Bag::GetAmountItem(ItemType type) {
    switch(type) {
        case ItemType::cipo:
            return cipo;
            break;
        case ItemType::berry:
            return berry;
            break;
        case ItemType::flor:
            return flor;
            break;
        case ItemType::galho:
            return galho;
            break;
    }
}

void Bag::UseItem(ItemType type, int amount) {
    switch(type) {
        case ItemType::cipo:
            cipo-=amount;
            cipo = cipo < 0 ? 0 : cipo;
            break;
        case ItemType::berry:
            berry-=amount;
            berry = berry < 0 ? 0 : berry;
            break;
        case ItemType::flor:
            flor-=amount;
            flor = flor < 0 ? 0 : flor;
            break;
        case ItemType::galho:
            galho-=amount;
            galho = galho < 0 ? 0 : galho;
            break;
    }
}

bool Bag::CanUseTrap(std::string trap) {
    if(trap == "Hole") { // 3 gravetos e 2 cipos
        return GetAmountItem(ItemType::galho) >= 3 && GetAmountItem(ItemType::cipo) >= 2;
    } else if(trap == "Bomb") {
        return GetAmountItem(ItemType::berry) >= 4 && GetAmountItem(ItemType::cipo) >= 2;
    } else if(trap == "Cipo") {
        return true;
    }
}