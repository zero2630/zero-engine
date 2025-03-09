#include "ray.hpp"


Ray2D::Ray2D():
    ray(sf::Lines, 2)
{
    length = 0;
    is_collided = false;
}


Ray2D::Ray2D(sf::VertexArray _ray, bool _is_collided)
{
    ray = _ray;
    is_collided = _is_collided;
    length = sqrt(pow(ray[0].position.x - ray[1].position.x, 2) + pow(ray[0].position.y - ray[1].position.y, 2));
}


void Ray2D::set_collided(bool _is_collided)
{
    is_collided = _is_collided;
}


void Ray2D::set_ray(sf::VertexArray _ray)
{
    ray = _ray;
    length = sqrt(pow(ray[0].position.x - ray[1].position.x, 2) + pow(ray[0].position.y - ray[1].position.y, 2));
}


void Ray2D::set_side(int _side)
{
    side = _side;
}


void Ray2D::set_perp_length(float _perp_length)
{
    perp_length = _perp_length;
}


float Ray2D::get_length()
{
    return length;
}


int Ray2D::get_side()
{
    return side;
}


bool Ray2D::get_collided()
{
    return is_collided;
}


sf::VertexArray Ray2D::get_ray()
{
    return ray;
}


float Ray2D::get_perp_length()
{
    return perp_length;
}