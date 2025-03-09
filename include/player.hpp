#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include<cmath>

#include "globals.hpp"
#include "worldmap.hpp"
#include "ray.hpp"


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
    float cos_90;
    float sin_90;
    size_t fov;
    sf::RectangleShape shape;
    std::vector<Ray2D> rays;
    std::vector<sf::RectangleShape> lines3D;

public:
    Player2D();
    Player2D(float _pos_x, float _pos_y, float _rotation);

    void move(float timdelta);
    void rotate(float timedelta);
    void render2D(WorldMap2D worldmap);
    void render3D();
    void set_speed(float new_speed);

    sf::Vector2f get_pos();
    float get_rotation();

    sf::RectangleShape get_shape();
    std::vector<Ray2D> get_rays();
    std::vector<sf::RectangleShape> get_lines3D();

};