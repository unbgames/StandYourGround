#include "../include/Sprite.h"
#include "../include/TileSet.h"
#include "../include/Debug.h"

TileSet::TileSet (GameObject& associated, std::string file, Vec2 size, Vec2 scale) : tileSet(associated, file),
    tileWidth(size.GetX()), tileHeight(size.GetY()), scale(scale) {

    std::cout<<"TileSet File: "<<file<<std::endl;
    if (tileSet.IsOpen()) {
        columns = tileSet.GetWidth() / tileWidth;
        rows = tileSet.GetHeight() / tileWidth;
        // std::cerr << "ROWS/COLS"<< columns<<' '<<rows<< std::endl;
    }
}

void TileSet::RenderTile(int index, float x, float y) {
    if (index < int(rows * columns) && index >= 0) {
        int tileColumn = (index)%columns;
        int tileRow = floor((index)/columns);
        tileSet.SetClip(tileColumn*tileWidth, tileRow*tileHeight, tileWidth, tileHeight);
        tileSet.SetScale(scale);
        tileSet.Render(x, y);
        // if (x*tileWidth < 500 &&  y*tileHeight < 500) {
            // std::cout << "TileOnImg(" << tileRow<<','<< tileColumn<<')';
            // std::cout << "| Index(" << index<<')';
            // std::cout << "| TileClipPos(" << tileRow*tileHeight<<','<< tileColumn*tileWidth<<')';
            // std::cout << "| RenderAt(" << x*tileWidth<<','<< y*tileHeight<<')'<< '(' << x<<','<< y<<')'<<std::endl;
            // std::cout<<std::endl;
        // }
        #ifdef DEBUG
        if (DEBUG_TILE) {
            int width = int(tileWidth*scale.GetX());
            int height = int(tileWidth*scale.GetY());
        	SDL_Point points[5];
            Rect box = tileSet.GetClip();
        	points[0] = {x, y};
        	points[4] = {x, y};
        	points[1] =  {x + width, y};
            points[2] =  {x + width, y + height};
        	points[3] =  {x, y + height};

        	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 70, 255, SDL_ALPHA_OPAQUE);
        	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
        }
        #endif // DEBUG
    } else {
        if (index >= 0) {
            std::cout<<"Bad Index:"<<index<<" AMOUNT:"<<rows * columns<<std::endl;
        }
    }
}

int TileSet::GetTileWidth() const {
    return tileWidth;
}

int TileSet::GetTileHeight() const {
    return tileHeight;
}
