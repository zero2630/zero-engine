#include "debugger.hpp"


Debugger::Debugger()
{
    std::stringstream str_converter;

    sf::Font font;
    if (!font.loadFromFile("./fonts/arialmt.ttf"))
    {
        std::cout << "bebra\n";
    }

    rotation_label.setFont(font);
    rotation_label.setFillColor(sf::Color::White);
    rotation_label.setCharacterSize(16);
    rotation_label.setPosition(sf::Vector2f(0, 0));
}


void Debugger::set_rotation_label(float value)
{
    str_converter << std::fixed  << "rotation: " << std::setprecision(2) << value;
    rotation_label.setString(str_converter.str());
    str_converter.str("");
}


sf::Text Debugger::get_rotation_label()
{
    return rotation_label;
}