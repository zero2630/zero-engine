#include "worldmap.hpp"

WorldMap2D::WorldMap2D(size_t _size_x, size_t _size_y)
{
    size_x = _size_x;
    size_y = _size_y;
    worldmap = std::vector<std::vector<Tile2D>>(size_y, std::vector<Tile2D>(size_x, Tile2D(0, 0, 0, 0)));
}

void WorldMap2D::load_from_file(std::string filepath)
{
    std::ifstream input(filepath);
    int type;
    
    for(int i=0; i<size_y; i++) {
        for(int j=0; j<size_x; j++) {
            worldmap[i][j].set_pos(j, i);
            if(!input.eof()) input >> type;
            else type = 0;
            worldmap[i][j].set_type(type);
        }
    }

}

Tile2D WorldMap2D::get_tile(size_t x_pos, size_t y_pos)
{
    return worldmap[y_pos][x_pos];
}


sf::Vector2f WorldMap2D::get_size()
{
    return sf::Vector2f(size_x, size_y);
}


void WorldMap2D::set_tile_size(size_t _size)
{
    for(int i=0; i<size_x; i++) {
        for(int j=0; j<size_y; j++) worldmap[i][j].set_size(_size);
    }
}


void WorldMap2D::set_tile_type(size_t tile_x, size_t tile_y, int type)
{
    worldmap[tile_y][tile_x].set_type(type);
}


Tile2D::Tile2D(size_t _pos_x, size_t _pos_y, size_t _size, int _type)
{
    pos_x = _pos_x;
    pos_y = _pos_y;
    tile_size = _size;
    type = _type;

    shape.setSize(sf::Vector2f(tile_size, tile_size));
    shape.setPosition(sf::Vector2f(pos_x*tile_size, pos_y*tile_size));
    shape.setFillColor(sf::Color::Blue);
}


sf::Vector2f Tile2D::get_pos()
{
    return sf::Vector2f(pos_x, pos_y);
}


sf::RectangleShape Tile2D::get_shape()
{
    return shape;
}


int Tile2D::get_type()
{
    return type;
}


void Tile2D::set_type(int _type)
{
    type = _type;
    if(type == 1) shape.setFillColor(sf::Color::Blue);
    else shape.setFillColor(sf::Color::Transparent);
}


void Tile2D::set_size(size_t _size)
{
    tile_size = _size;
    shape.setSize(sf::Vector2f(tile_size, tile_size));
    shape.setPosition(sf::Vector2f(pos_x*tile_size, pos_y*tile_size));
}


void Tile2D::set_pos(size_t _pos_x, size_t _pos_y)
{
    pos_x = _pos_x;
    pos_y = _pos_y;
    shape.setPosition(sf::Vector2f(pos_x*tile_size, pos_y*tile_size));
}