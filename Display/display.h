#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

/**
   @class Display
   @brief This class implements a renderer to allow for easier rendering.
 */

class Display
{
private:
  /**
   @brief The renderer is an array that can contains pointers to every class extending from
   sf::Shape.
  */
  std::vector<sf::Shape*> renderer;

public:
  /**
     @brief The current window.
   */
  sf::RenderWindow window;
  Display();
  /**
   @brief Add a shape to the renderer.
   @param shape The shape to add to the renderer.
  */
  void AddToRenderer(sf::Shape* shape);
  /**
   @brief Render to the window everything that is contained in the renderer.
  */
  void Render();
  /**
     @brief Delete the renderer and every object contained inside.
   */
  void DeleteRenderer();
  /**
     @brief Render something to the screen without adding it to the renderer.
   */
  void LazyRender(sf::Shape* shape);
};
#endif
