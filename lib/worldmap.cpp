#include "worldmap.h"

WorldMap2D::WorldMap2D(size_t _size_x, size_t _size_y)
{
    size_x = _size_x;
    size_y = _size_y;
    worldmap = std::vector<std::vector<int>>(size_y, std::vector<int>(size_x, 0));
}

void WorldMap2D::load_from_file(std::string filepath)
{
    std::ifstream input(filepath);
    
    for(int i=0; i<size_y; i++) {
        for(int j=0; j<size_x; j++) {
            if(!input.eof()) input >> worldmap[i][j];
        }
    }

}

std::vector<std::vector<int>> WorldMap2D::get_worldmap()
{
    return worldmap;
}