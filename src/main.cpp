#include <SFML/Graphics.hpp>
#include <iostream>

#include "misc.hpp"
#include "world.hpp"

int main()
{
    const unsigned w = sf::VideoMode::getDesktopMode().width * 2 / 3;
    const unsigned h = sf::VideoMode::getDesktopMode().height * 2 / 3;

    sf::RenderWindow window(sf::VideoMode(w, h), "Game of Life");

    World *world = World::getInstance(w, h);
    world->initGrid(20, 10);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    || (event.type == sf::Event::Closed))
            {
                window.close();
            }

            if (event.type == sf::Event::MouseMoved)
                world->handleHover(event);

            if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left)
            {
                world->setIsMouseDown(true);
                world->handleClick(event);
            }

            if (event.type == sf::Event::MouseButtonReleased &&
                    event.mouseButton.button == sf::Mouse::Left)
            {
                world->setIsMouseDown(false);
            }
        }

        window.clear();
        world->drawGrid(window);
        window.display();
    }

    std::cout << misc::meaning_of_life() << std::endl;
    misc::test_range();

    return 0;
}
