#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>

#include "player.cpp"
#include "globals.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "level");

    Player2D player(100, 100, PI/2);
    player.set_speed(10.f);

    while (window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {
                window.close();
            }

            else if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::A) {
                    player.move(player.get_pos().x-5, player.get_pos().y);
                }

                else if(event.key.code == sf::Keyboard::D) {
                    player.move(player.get_pos().x+5, player.get_pos().y);
                }

                else if(event.key.code == sf::Keyboard::W) {
                    player.move(player.get_pos().x, player.get_pos().y-5);
                }

                else if(event.key.code == sf::Keyboard::S) {
                    player.move(player.get_pos().x, player.get_pos().y+5);
                }
            }
        }

        window.clear();
        window.draw(player.get_shape());
        window.display();        
    }
    

    return 0;
}