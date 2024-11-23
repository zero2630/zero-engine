#pragma once

#include<SFML/Graphics.hpp>
#include<vector>

#include"globals.h"


class Player2D
{
private:
    float pos_x;
    float pos_y;
    float rotation;
    float speed;
    sf::CircleShape shape;
    sf::VertexArray shape_dir;

public:
    Player2D();
    Player2D(float _pos_x, float _pos_y, float _rotation);

    void move(float new_x, float new_y);
    void rotate(float new_rotation);
    void set_speed(float new_speed);

    sf::Vector2f get_pos();

    sf::CircleShape get_shape();

};