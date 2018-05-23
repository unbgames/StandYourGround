#include "../include/Sprite.h"
#include "../include/TileSet.h"

TileSet::TileSet (GameObject& associated, std::string file, int tileWidth,
    int tileHeight) : tileSet(associated, file), tileWidth(tileWidth),
    tileHeight(tileHeight) {

    if (tileSet.IsOpen()) {
        columns = tileSet.GetWidth() / tileWidth;
        rows = tileSet.GetHeight() / tileWidth;
        // std::cerr << "ROWS/COLS"<< columns<<' '<<rows<< std::endl;
    }
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if (index < rows*columns && index > 0) {
        int tileColumn = (index-1)%columns;
        int tileRow = floor((index-1)/columns);
        tileSet.SetClip(tileColumn*tileWidth, tileRow*tileHeight, tileWidth, tileHeight);
        tileSet.Render(x, y);
        // if (x*tileWidth < 500 &&  y*tileHeight < 500) {
        //     std::cout << "TileOnImg(" << tileRow<<','<< tileColumn<<')'<<std::endl;
        //     std::cout << "Index(" << index<<')'<<std::endl;
        //     std::cout << "TileClipPos(" << tileRow*tileHeight<<','<< tileColumn*tileWidth<<')'<<std::endl;
        //     std::cout << "RenderAt(" << x*tileWidth<<','<< y*tileHeight<<')'<< '(' << x<<','<< y<<')'<<std::endl;
        //     std::cout<<std::endl;
        // }
    } else {
        if (index > 0)
            std::cout<<"Bad Index:"<<index<<std::endl;
    }
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}
