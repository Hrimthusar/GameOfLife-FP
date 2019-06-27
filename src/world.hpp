#ifndef WORLD_H // include guard
#define WORLD_H

class World
{
private:
  /* Here will be the instance stored. */
  static World *instance;

  /* Private constructor to prevent instancing. */
  World(unsigned w, unsigned h);

  unsigned screenWidth;
  unsigned screenHeight;

  unsigned innerWidth;
  unsigned innerHeight;

  unsigned xCount;
  unsigned yCount;

  unsigned cellSize;

  unsigned cellMargin = 5;

  //                        TODO: klasa za celiju
  std::vector<std::vector<std::pair<sf::RectangleShape, int>>> grid;

public:
  /* Static access method. */
  static World *getInstance(unsigned w, unsigned h);

  void initGrid(unsigned m, unsigned n);
  void drawGrid(sf::RenderWindow &window);
  void handleHover(sf::Event &event);
};
#endif /* WORLD_H */
