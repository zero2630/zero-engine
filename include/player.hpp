#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include<cmath>

#include "globals.hpp"
#include "worldmap.hpp"


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
    size_t fov;
    sf::RectangleShape shape;
    std::vector<sf::VertexArray> rays;

public:
    Player2D();
    Player2D(float _pos_x, float _pos_y, float _rotation);

    void move(float timdelta);
    void rotate(float timedelta);
    void render2D(WorldMap2D worldmap);
    void set_speed(float new_speed);

    sf::Vector2f get_pos();
    float get_rotation();

    sf::RectangleShape get_shape();
    std::vector<sf::VertexArray> get_rays();

};