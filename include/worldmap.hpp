#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>


class Tile2D
{
private:
    size_t pos_x;
    size_t pos_y;
    size_t tile_size;
    int type;
    sf::RectangleShape shape;
public:
    Tile2D(size_t _pos_x, size_t _pos_y, size_t _size, int _type);

    sf::Vector2f get_pos();
    sf::RectangleShape get_shape();
    int get_type();

    void set_type(int _type);
    void set_size(size_t _size);
    void set_pos(size_t _pos_x, size_t _pos_y);
};

class WorldMap2D
{
private:
    size_t size_x;
    size_t size_y;
    std::vector<std::vector<Tile2D>> worldmap;

public:
    WorldMap2D(size_t size_x, size_t size_y);
    void load_from_file(std::string filepath);

    Tile2D get_tile(size_t x_pos, size_t y_pos);
    sf::Vector2f get_size();

    void set_tile_size(size_t _size);
    void set_tile_type(size_t tile_y, size_t tile_x, int type);

};