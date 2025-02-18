#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include <iomanip>
#include <sstream>

#include "player.hpp"
#include "worldmap.hpp"
#include "globals.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "level");
    window.setFramerateLimit(60);

    Player2D player(600, 400, 0);
    player.set_speed(100.f);
    sf::Clock clock;

    std::stringstream str_converter;

    sf::Font font;
    font.loadFromFile("./fonts/arialmt.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Hello world");
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);


    WorldMap2D map(MAP_SIZE, MAP_SIZE);
    map.load_from_file("map.txt");
    map.set_tile_size(TILE_SIZE);

    while (window.isOpen())
    {
        sf::Event event;
        float timedelta = clock.restart().asSeconds();

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        player.move(timedelta);
        player.rotate(timedelta);
        player.render2D(map);

        str_converter << std::fixed  << "rotation: " << std::setprecision(2) << player.get_rotation();
        text.setString(str_converter.str());
        str_converter.str("");


        window.clear();

        for (int i=0; i<MAP_SIZE; i++) {
            for(int j=0; j<MAP_SIZE; j++) {
                if(map.get_tile(j, i).get_type() == 1) {
                    window.draw(map.get_tile(j, i).get_shape());
                }
            }
        }

        std::vector<sf::VertexArray> temp_rays = player.get_rays();
        window.draw(player.get_shape());
        for(int i=0; i<temp_rays.size(); i++) {
            window.draw(temp_rays[i]);
        }

        window.draw(text);
        window.display();        
    }
    

    return 0;
}