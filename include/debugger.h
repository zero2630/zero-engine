#include <iomanip>
#include <vector>
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>

class Debugger
{
private:
    std::stringstream str_converter;

    sf::Font font;
    sf::Text rotation_label;

public:
    Debugger();

    void set_rotation_label(float value);
    sf::Text get_rotation_label();
};