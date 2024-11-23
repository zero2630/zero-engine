#include "player.h"

Player2D::Player2D()
{
    pos_x = 0;
    pos_y = 0;
    rotation = PI/2;
    speed = 0;
    
    shape.setRadius(20.f);
    shape.setPosition(sf::Vector2f(pos_x, pos_y));
    shape.setFillColor(sf::Color::White);
}


Player2D::Player2D(float _pos_x, float _pos_y, float _rotaion)
{
    pos_x = _pos_x;
    pos_y = _pos_y;
    rotation = _rotaion;
    speed = 0;
    
    shape.setRadius(20.f);
    shape.setPosition(sf::Vector2f(pos_x, pos_y));
    shape.setFillColor(sf::Color::White);
}


void Player2D::move(float new_x, float new_y)
{
    pos_x = new_x;
    pos_y = new_y;

    shape.setPosition(sf::Vector2f(pos_x, pos_y));
}


void Player2D::set_speed(float new_speed)
{
    speed = new_speed;
}


sf::Vector2f Player2D::get_pos()
{
    return sf::Vector2f(pos_x, pos_y);
}


sf::CircleShape Player2D::get_shape()
{
    return shape;
}