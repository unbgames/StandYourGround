#ifndef BAG_H
#define BAG_H

#include "Item.h"

class Bag {
    public:        
        static void PickItem(ItemType type, int amount=1);
        static int GetAmountItem(ItemType type);
        static void UseItem(ItemType type, int amount);
    private:
        static int cipo;
        static int berry;
        static int galho;
        static int flor;
};

#endif