#include "mapeditor.hpp"


MapEditor2D::MapEditor2D(): 
    worldmap(MAP_SIZE, MAP_SIZE),
    placed_tiles()
{
    worldmap.load_from_file("map.txt");
    worldmap.set_tile_size(TILE_SIZE); 

    for (int i=0; i<MAP_SIZE; i++) {
        for(int j=0; j<MAP_SIZE; j++) {
            if(worldmap.get_tile(j, i).get_type() == 1) {
                placed_tiles.push_back(sf::Vector2i(j, i));
            }
        }
    }

    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::Red);
    border.setOutlineThickness(2.f);
    border.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
}


std::vector<sf::Vector2i> MapEditor2D::get_placed_tiles()
{
    return placed_tiles;
}


WorldMap2D MapEditor2D::get_worldmap()
{
    return worldmap;
}

void MapEditor2D::place_tile(int selected_type)
{
    int tile_x = (int)border.getPosition().x/(int)TILE_SIZE;
    int tile_y = (int)border.getPosition().y/(int)TILE_SIZE;

    for(int i=0; i<placed_tiles.size(); i++) {
        if(placed_tiles[i].x == tile_x && placed_tiles[i].y == tile_y){
            placed_tiles.erase(placed_tiles.begin()+i);
        }
    }

    if(selected_type) {
        placed_tiles.push_back(sf::Vector2i(tile_x, tile_y));
    }

    worldmap.set_tile_type(tile_x, tile_y, selected_type);
}


void MapEditor2D::check_cursor(sf::Vector2i mouse_pos)
{
    border.setPosition(mouse_pos.x-mouse_pos.x%(int)TILE_SIZE, mouse_pos.y-mouse_pos.y%(int)TILE_SIZE);
}


sf::RectangleShape MapEditor2D::get_border()
{
    return border;
}


void MapEditor2D::save_map()
{
    std::ofstream output("map.txt");

    for(int i=0; i<MAP_SIZE; i++) {
        for(int j=0; j<MAP_SIZE; j++) {
            output << worldmap.get_tile(j, i).get_type() << ' ';
        }
        output << "\n";
    }
}