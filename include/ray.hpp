#pragma once

#include<SFML/Graphics.hpp>
#include<cmath>

#include "globals.hpp"


class Ray2D
{
private:
    float length;
    float perp_length;
    int side;
    bool is_collided;
    sf::VertexArray ray;

public:
    Ray2D();
    Ray2D(sf::VertexArray _ray, bool _is_collided);

    void set_collided(bool _is_collided);
    void set_ray(sf::VertexArray _ray);
    void set_side(int _side);
    void set_perp_length(float _perp_length);

    float get_length();
    float get_perp_length();
    int get_side();
    bool get_collided();
    sf::VertexArray get_ray();
};