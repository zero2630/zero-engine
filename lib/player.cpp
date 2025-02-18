#include "player.hpp"

Player2D::Player2D():
    rays(RAYS_AMOUNT, sf::VertexArray(sf::Lines, 2))
{
    pos_x = 0;
    pos_y = 0;
    rotation = 0;
    speed = 0;
    size = 10.f;

    cos = 1.f;
    sin = 0.f;

    fov = 90.f;
    
    shape.setOrigin(sf::Vector2f(size, size)/2.f);
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(sf::Vector2f(pos_x, pos_y));
    shape.rotate(rotation);
    shape.setFillColor(sf::Color::White);
}


Player2D::Player2D(float _pos_x, float _pos_y, float _rotaion):
    rays(RAYS_AMOUNT, sf::VertexArray(sf::Lines, 2))
{
    pos_x = _pos_x;
    pos_y = _pos_y;
    rotation = _rotaion;
    speed = 0;
    size = 10.f;

    cos = 1.f;
    sin = 0.f;

    fov = 90.f;
    
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


std::vector<sf::VertexArray> Player2D::get_rays()
{
    return rays;
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

    if (rotation > 360.f) rotation = std::fmod(rotation, 360.f);
    if (rotation < 0.f) rotation = 360.f + std::fmod(rotation, 360.f);

    shape.setRotation(-rotation);
}


void Player2D::render2D(WorldMap2D worldmap)
{
    float ray_rotation;
    float ray_radians;
    float ray_length = 0.f;
    float side_x, side_y;
    float side_dist_x, side_dist_y;
    float delta_x, delta_y;
    float delta_dist_x, delta_dist_y;
    float end_x, end_y;
    int map_x, map_y;
    int step_x, step_y;
    int side;
    bool is_collided, is_ended;

    for(int i=0; i<rays.size(); i++){
        ray_rotation = rotation + i * ((float)fov / (float)rays.size()) - fov / 2;
        ray_radians = to_radians(ray_rotation);
        map_x = (int)pos_x/(int)TILE_SIZE;
        map_y = (int)pos_y/(int)TILE_SIZE;

        delta_x = TILE_SIZE * std::tan(ray_radians);
        delta_y = TILE_SIZE / std::tan(ray_radians);
        delta_dist_x = std::sqrt(TILE_SIZE * TILE_SIZE + delta_y * delta_y);
        delta_dist_y = std::sqrt(TILE_SIZE * TILE_SIZE + delta_x * delta_x);

        is_collided = false;
        is_ended = false;

        if (ray_rotation < 360.f && ray_rotation > 180.f) {
            side_x = TILE_SIZE - fmod(pos_x, TILE_SIZE);
            step_x = 1;
        }
        else {
            side_x = fmod(pos_x, TILE_SIZE);
            step_x = -1;
        }

        side_y = side_x / std::tan(ray_radians);
        side_dist_x = std::sqrt(side_x * side_x + side_y * side_y);

        if (ray_rotation > 90.f && ray_rotation < 270.f) {
            side_y = TILE_SIZE - fmod(pos_y, TILE_SIZE);
            step_y = 1;
        }
        else {
            side_y = std::fmod(pos_y, TILE_SIZE);
            step_y = -1;
        }

        side_x = side_y * std::tan(ray_radians);
        side_dist_y = std::sqrt(side_x * side_x + side_y * side_y);

        while (!is_ended && !is_collided)
        {
            if ((side_dist_x + delta_dist_x > RAY_MAX_LENGTH) && (side_dist_y + delta_dist_y > RAY_MAX_LENGTH)) {
                is_ended = true;
                if(side_dist_x < side_dist_y) side = 0;
                else side = 1;
            }
            else {
                if (side_dist_x < side_dist_y) {
                    side_dist_x += delta_dist_x;
                    map_x += step_x;
                    if(worldmap.get_tile(map_x, map_y).get_type() == 1) {
                        is_collided = true;
                        side = 0;
                    }
                }
                else {
                    side_dist_y += delta_dist_y;
                    map_y += step_y;
                    if(worldmap.get_tile(map_x, map_y).get_type() == 1) {
                        is_collided = true;
                        side = 1;
                    }
                }
            }
        }
        
        if(side == 0 && is_collided) side_dist_x -= delta_dist_x;
        else if(side == 1 && is_collided) side_dist_y -= delta_dist_y;

        ray_length = std::fmin(side_dist_x, side_dist_y);
        
        if(!is_collided) {
            ray_length = RAY_MAX_LENGTH;
        }

        // printf("%f %d | %f %d| %d\n", end_x, map_x, end_y, map_y, side);
        
        rays[i][0] = sf::Vector2f(pos_x, pos_y);
        rays[i][1] = sf::Vector2f(pos_x + ray_length * std::sin(ray_radians)*-1, pos_y - ray_length * std::cos(ray_radians));
    }
}