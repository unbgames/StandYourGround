#include "ItemFactory.h"
#include "Game.h"
#include "Sprite.h"
#include "Collider.h"
#include "Item.h"
#include "config.h"

#include <limits>
#include <fstream>
#include <sstream>

void ItemFactory::Load(std::vector<std::string> file_paths) {
    int i = 0;
    for (std::string path : file_paths) {
        std::ifstream file(path);
        std::string line;
        int row = 0;
        std::cout << "PEGANDO ITENS"<<std::endl;
        while (std::getline(file, line)) {
            std::stringstream lineStream(line);
            std::string cell;
            int column = 0;
            while(std::getline(lineStream, cell, ',')){
                int item = std::stoi(cell);
                // std::cout << val <<",";
                if (item != -1) {
                    std::cout << "ITEM TYPE:"<< item <<std::endl;
                    switch (i) {
                        case 0:
                            {
                                auto goItem = std::make_shared<GameObject>();
                                goItem->box.SetOrigin(4*10*column, 4*10*row);
                                Sprite* itemSprite = new Sprite(*goItem, ASSETS_PATH("/img/items/flor_rara.png"), 13, 0.1);
                                itemSprite->SetScale({4, 4});
                                goItem->AddComponent(itemSprite);
                                goItem->box.SetSize(itemSprite->GetWidth(), itemSprite->GetHeight());
                                goItem->AddComponent(new Collider(*goItem));
                                goItem->AddComponent(new Item(*goItem, ItemType::berry));
                                goItem->layer = 3;
                                Game::GetInstance().GetCurrentState().AddObject(goItem);

                                std::cout << "ADDED ITEM AT:"<<Vec2(4*10*column, 4*10*row) <<std::endl;
                            }
                        break;
                        case 1:
                            {
                                auto goItem = std::make_shared<GameObject>();
                                goItem->box.SetOrigin(4*10*column, 4*10*row);
                                Sprite* itemSprite = new Sprite(*goItem, ASSETS_PATH("/img/items/berries_mapa.png"));
                                itemSprite->SetScale({4, 4});
                                goItem->AddComponent(itemSprite);
                                goItem->box.SetSize(itemSprite->GetWidth(), itemSprite->GetHeight());
                                goItem->AddComponent(new Collider(*goItem));
                                goItem->AddComponent(new Item(*goItem, ItemType::berry));
                                goItem->layer = 3;
                                Game::GetInstance().GetCurrentState().AddObject(goItem);

                                std::cout << "ADDED ITEM AT:"<<Vec2(4*10*column, 4*10*row) <<std::endl;
                            }
                        break;

                        case 2:
                            {
                                auto goItem = std::make_shared<GameObject>();
                                goItem->box.SetOrigin(4*10*column, 4*10*row);
                                Sprite* itemSprite = new Sprite(*goItem, ASSETS_PATH("/img/items/galho_mapa.png"));
                                itemSprite->SetScale({4, 4});
                                goItem->AddComponent(itemSprite);
                                goItem->box.SetSize(itemSprite->GetWidth(), itemSprite->GetHeight());
                                goItem->AddComponent(new Collider(*goItem));
                                goItem->AddComponent(new Item(*goItem, ItemType::galho));
                                goItem->layer = 3;
                                Game::GetInstance().GetCurrentState().AddObject(goItem);

                                std::cout << "ADDED ITEM AT:"<<Vec2(4*10*column, 4*10*row) <<std::endl;
                            }
                        break;
                    }


                }
                column++;
            }
            row++;
            // std::cout <<"\n";
        }
        i++;
    }
}
