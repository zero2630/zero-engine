#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include <iomanip>
#include <sstream>

#include "player.hpp"
#include "worldmap.hpp"
#include "globals.hpp"


void change_render_mode(bool* render_mode, bool* isclick)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        if(!(*isclick)) {
            *render_mode = !(*render_mode);
            *isclick = true;
        }
    }
    else *isclick = false;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "level");
    window.setFramerateLimit(60);

    Player2D player(700.f, 600.f, 0);
    player.set_speed(100.f);
    sf::Clock clock;
    bool render_mode = true;
    bool R_click = false;

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

    sf::RectangleShape ceiling;
    ceiling.setSize(sf::Vector2f(WIDTH, HEIGHT/2));
    ceiling.setFillColor(sf::Color(173, 216, 230));
    ceiling.setPosition(sf::Vector2f(0, 0));

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
        player.render3D();

        str_converter << std::fixed  << "rotation: " << std::setprecision(2) << player.get_rotation();
        text.setString(str_converter.str());
        str_converter.str("");

        change_render_mode(&render_mode, &R_click);
        window.clear();

        if(render_mode) {
            std::vector<sf::RectangleShape> temp_lines = player.get_lines3D();
            
            window.draw(ceiling);
            for(int i=0; i<temp_lines.size(); i++) {
                window.draw(temp_lines[i]);
            }
        }
        else {
            for (int i=0; i<MAP_SIZE; i++) {
                for(int j=0; j<MAP_SIZE; j++) {
                    if(map.get_tile(j, i).get_type() == 1) {
                        window.draw(map.get_tile(j, i).get_shape());
                    }
                }
            }
    
            window.draw(player.get_shape());
            for(int i=0; i<player.get_rays().size(); i++) {
                window.draw(player.get_rays()[i].get_ray());
            }
        }

        window.draw(text);
        window.display();        
    }
    

    return 0;
}