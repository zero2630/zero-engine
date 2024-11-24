#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include<cmath>

#include"globals.h"


class Player2D
{
private:
    float pos_x;
    float pos_y;
    float rotation;
    float speed;
    float size;
    float cos;
    float sin;
    sf::RectangleShape shape;

public:
    Player2D();
    Player2D(float _pos_x, float _pos_y, float _rotation);

    void move(float timdelta);
    void rotate(float timedelta);
    void set_speed(float new_speed);

    sf::Vector2f get_pos();
    float get_rotation();

    sf::RectangleShape get_shape();

};