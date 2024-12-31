#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

class WorldMap2D
{
private:
    size_t size_x;
    size_t size_y;
    std::vector<std::vector<int>> worldmap;

public:
    WorldMap2D(size_t size_x, size_t size_y);
    void load_from_file(std::string filepath);
    std::vector<std::vector<int>> get_worldmap();
};