#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include <iomanip>
#include <sstream>

#include "player.cpp"
#include "worldmap.cpp"
#include "globals.cpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "level");

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


    size_t map_size_x = 5;
    size_t map_size_y = 5;
    WorldMap2D map(map_size_x, map_size_y);
    map.load_from_file("map.txt");
    map.set_tile_size(40, 40);

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

        str_converter << std::fixed  << "rotation: " << std::setprecision(2) << player.get_rotation();
        text.setString(str_converter.str());
        str_converter.str("");


        window.clear();
        window.draw(player.get_shape());

        for (int i=0; i<map_size_y; i++) {
            for(int j=0; j<map_size_x; j++) {
                if(map.get_tile(j, i).get_type() == 1) {
                    window.draw(map.get_tile(j, i).get_shape());
                }
            }
        }

        window.draw(text);
        window.display();        
    }
    

    return 0;
}