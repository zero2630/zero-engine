#include "player.hpp"

Player2D::Player2D():
    rays(RAYS_AMOUNT, Ray2D()),
    lines3D(RAYS_AMOUNT, sf::RectangleShape())
{
    pos_x = 0;
    pos_y = 0;
    rotation = 0;
    speed = 0;
    size = 10.f;

    cos = 1.f;
    sin = 0.f;
    cos_90 = 0.f;
    sin_90 = 1.f;

    fov = FOV;
    
    shape.setOrigin(sf::Vector2f(size, size)/2.f);
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(sf::Vector2f(pos_x, pos_y));
    shape.rotate(rotation);
    shape.setFillColor(sf::Color::White);
}


Player2D::Player2D(float _pos_x, float _pos_y, float _rotaion):
    rays(RAYS_AMOUNT, Ray2D()),
    lines3D(RAYS_AMOUNT, sf::RectangleShape())
{
    pos_x = _pos_x;
    pos_y = _pos_y;
    rotation = _rotaion;
    speed = 0;
    size = 10.f;

    cos = 1.f;
    sin = 0.f;
    cos_90 = 0.f;
    sin_90 = 1.f;

    fov = FOV;
    
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


std::vector<Ray2D> Player2D::get_rays()
{
    return rays;
}


void Player2D::move(float timedelta)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        pos_x = pos_x-speed*timedelta*sin_90;
        pos_y = pos_y-speed*timedelta*cos_90;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D )) {
        pos_x = pos_x-speed*timedelta*-sin_90;
        pos_y = pos_y-speed*timedelta*-cos_90;
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
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            rotation += speed*timedelta;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            rotation -= speed*timedelta;
        }
        cos = std::cos(to_radians(rotation));
        sin = std::sin(to_radians(rotation));
        cos_90 = std::cos(to_radians(rotation+90.f));
        sin_90 = std::sin(to_radians(rotation+90.f));
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
    float perp_ray_length;
    float side_x, side_y;
    float side_dist_x, side_dist_y;
    float delta_x, delta_y;
    float delta_dist_x, delta_dist_y;
    float end_x, end_y;
    int map_x, map_y;
    int step_x, step_y;
    int side;
    bool is_collided, is_ended;
    sf::VertexArray ray(sf::Lines, 2);

    for(int i=0; i<rays.size(); i++){
        ray_rotation = rotation + (RAYS_AMOUNT-i) * ((float)fov / (float)rays.size()) - fov / 2;
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
        perp_ray_length = ray_length * std::cos(to_radians(i * ((float)fov / (float)rays.size()) - fov / 2));
        if(!is_collided) ray_length = RAY_MAX_LENGTH;
        
        ray[0] = sf::Vector2f(pos_x, pos_y);
        ray[1] = sf::Vector2f(pos_x + ray_length * std::sin(ray_radians)*-1, pos_y - ray_length * std::cos(ray_radians));
        rays[i].set_ray(ray);
        rays[i].set_collided(is_collided);
        rays[i].set_side(side);
        rays[i].set_perp_length(perp_ray_length);
    }
}


void Player2D::render3D()
{
    float ray_width = (float)WIDTH/(float)RAYS_AMOUNT;
    float ray_height;
    for(int i=0; i<RAYS_AMOUNT; i++) {
        ray_height = (float)HEIGHT*(1 - rays[i].get_perp_length()/(float)RAY_MAX_LENGTH);
        lines3D[i].setSize(sf::Vector2f(ray_width, ray_height));
        lines3D[i].setPosition(sf::Vector2f(i*(ray_width), (float)HEIGHT/2.f - ray_height/2.f));

        if(rays[i].get_collided()) {
            if(rays[i].get_side()) lines3D[i].setFillColor(sf::Color::Green);
            else lines3D[i].setFillColor(sf::Color::Red);
        }

        else {
            lines3D[i].setFillColor(sf::Color::Transparent);
        }

        // lines3D[i].setOutlineColor(sf::Color::Red);
        // lines3D[i].setOutlineThickness(0.2);
    }
}


std::vector<sf::RectangleShape> Player2D::get_lines3D()
{
    return lines3D;
}
