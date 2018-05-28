#include "../include/Sprite.h"
#include "../include/TileSet.h"

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
    if (index < rows * columns && index >= 0) {
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
