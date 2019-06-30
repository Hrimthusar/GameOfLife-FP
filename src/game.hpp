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
    bool m_animate = false;

    const static unsigned s_windowWidth;
    const static unsigned s_windowHeight;

    void Update(float dt);
    void Render();
    void ProcessEvents();
};

#endif /* GAME_H */

