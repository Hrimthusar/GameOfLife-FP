#include <SFML/Graphics.hpp>
#include <iostream>

#include "misc.hpp"

void test_range();

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    std::cout << misc::meaning_of_life() << std::endl;
    misc::test_range();

    return 0;
}





