#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

#include "worldmap.hpp"
#include "globals.hpp"

class MapEditor2D
{
private:
    sf::RectangleShape border;
    WorldMap2D worldmap;
    std::vector<sf::Vector2i> placed_tiles;
public:
    MapEditor2D();

    std::vector<sf::Vector2i> get_placed_tiles();
    WorldMap2D get_worldmap();

    void check_cursor(sf::Vector2i mouse_pos);
    void place_tile(int selected_type);
    void save_map();

    sf::RectangleShape get_border();

};
