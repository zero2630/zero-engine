#include "player.hpp"

Player2D::Player2D()
{
    pos_x = 0;
    pos_y = 0;
    rotation = 0;
    speed = 0;
    size = 10.f;

    cos = 1.f;
    sin = 0.f;
    
    shape.setOrigin(sf::Vector2f(size, size)/2.f);
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(sf::Vector2f(pos_x, pos_y));
    shape.rotate(rotation);
    shape.setFillColor(sf::Color::White);
}


Player2D::Player2D(float _pos_x, float _pos_y, float _rotaion)
{
    pos_x = _pos_x;
    pos_y = _pos_y;
    rotation = _rotaion;
    speed = 0;
    size = 10.f;

    cos = 1.f;
    sin = 0.f;
    
    shape.setOrigin(sf::Vector2f(size, size)/2.f);
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(sf::Vector2f(pos_x, pos_y));
    shape.rotate(rotation);
    shape.setFillColor(sf::Color::White);
}


void Player2D::set_speed(float new_speed)
{
    speed = new_speed;
}


sf::Vector2f Player2D::get_pos()
{
    return sf::Vector2f(pos_x, pos_y);
}


float Player2D::get_rotation()
{
    return rotation;
}


sf::RectangleShape Player2D::get_shape()
{
    return shape;
}

void Player2D::move(float timedelta)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        pos_x = pos_x-speed*timedelta*cos;
        pos_y = pos_y-speed*timedelta*sin;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D )) {
        pos_x = pos_x+speed*timedelta*cos;
        pos_y = pos_y+speed*timedelta*sin;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        pos_x = pos_x-speed*timedelta*sin;
        pos_y = pos_y-speed*timedelta*cos;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        pos_x = pos_x+speed*timedelta*sin;
        pos_y = pos_y+speed*timedelta*cos;
    }

    shape.setPosition(sf::Vector2f(pos_x, pos_y));
}

void Player2D::rotate(float timedelta)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        rotation += speed*timedelta;
        cos = std::cos(to_radians(rotation));
        sin = std::sin(to_radians(rotation));
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        rotation -= speed*timedelta;
        cos = std::cos(to_radians(rotation));
        sin = std::sin(to_radians(rotation));
    }

    shape.setRotation(-rotation);
}