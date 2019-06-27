#include <SFML/Graphics.hpp>
#include <iostream>

#include "misc.hpp"
#include "world.hpp"

int main()
{
    const unsigned w = 800;
    const unsigned h = 600;
    sf::RenderWindow window(sf::VideoMode(w, h), "Game of Life");

    World *world = World::getInstance(w, h);
    world->initGrid(20, 10);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
                world->handleHover(event);
        }

        window.clear();

        world->drawGrid(window);

        window.display();
    }

    std::cout << misc::meaning_of_life() << std::endl;
    misc::test_range();

    return 0;
}
