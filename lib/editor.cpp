#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include <iomanip>
#include <sstream>

#include "mapeditor.hpp"
#include "player.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "level");
    window.setFramerateLimit(60);

    sf::Clock clock;

    std::stringstream str_converter;

    bool lclick = false;
    bool rclick = false;
    bool enter_click = false;

    sf::Font font;
    font.loadFromFile("./fonts/arialmt.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Hello world");
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);

    Player2D player(600, 400, 0);
    player.set_speed(100.f);


    MapEditor2D mapeditor;

    std::vector<sf::Vector2i> tmp_tiles= mapeditor.get_placed_tiles();
    WorldMap2D tmp_worldmap = mapeditor.get_worldmap();

    while (window.isOpen())
    {
        sf::Event event;
        float timedelta = clock.restart().asSeconds();

        mapeditor.check_cursor(sf::Mouse::getPosition(window));

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        player.move(timedelta);
        player.rotate(timedelta);

        str_converter << std::fixed  << "type: " << "void";
        text.setString(str_converter.str());
        str_converter.str("");

        if(event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Left && !lclick) {
                mapeditor.place_tile(1);

                tmp_worldmap = mapeditor.get_worldmap();
                tmp_tiles = mapeditor.get_placed_tiles();

                lclick = true;
            }
            if(event.mouseButton.button == sf::Mouse::Right && !rclick) {
                mapeditor.place_tile(0);

                tmp_worldmap = mapeditor.get_worldmap();
                tmp_tiles = mapeditor.get_placed_tiles();

                rclick = true;
            }
        }
        else if(event.type == sf::Event::MouseButtonReleased) {
            if(event.mouseButton.button == sf::Mouse::Left && lclick) {
                lclick = false;
            }
            if(event.mouseButton.button == sf::Mouse::Right && rclick) {
                rclick = false;
            }
        }
        

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !enter_click) {
            mapeditor.save_map();
        }
        enter_click = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);

        window.clear();

        for(int i=0; i<tmp_tiles.size(); i++) {
            window.draw(tmp_worldmap.get_tile(tmp_tiles[i].x, tmp_tiles[i].y).get_shape());
        }

        window.draw(mapeditor.get_border());

        window.draw(player.get_shape());

        window.draw(text);
        window.display();        
    }
    

    return 0;
}