#ifndef GAME_H // include guard
#define GAME_H

#include <SFML/Graphics.hpp>
#include "world.hpp"

class Game
{
public:
    Game();
    ~Game();

    void Run();
private:
    sf::RenderWindow m_window;
    World *m_world;
    static sf::Time s_tick;
    static sf::Time s_fastest_tick;
    static sf::Time s_slowest_tick;
    static sf::Time s_tick_change;

    static int s_xGridSize;
    static int s_yGridSize;
    static int s_xGridChange;
    static int s_yGridChange;


    bool m_animate = false;

    const static unsigned s_windowWidth;
    const static unsigned s_windowHeight;

    void Update(float dt);
    void Render();
    void ProcessEvents();
    void processKeyboardEvents(sf::Event& event);
};

#endif /* GAME_H */

