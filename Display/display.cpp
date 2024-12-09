#include "display.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowHandle.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>

Display::Display() : window(sf::VideoMode(200, 200),
                            "Bezier Curves") // Initialize the RenderWindow
{
}

void Display::AddToRenderer(sf::Shape* shape)
{
  this->renderer.push_back(shape);
  return;
}

void Display::DeleteRenderer()
{
  for (int i = 0; i < this->renderer.size(); i++) delete this->renderer[i];
  return;
}

void Display::Render()
{
  for (int i = 0; i < this->renderer.size(); i++) this->window.draw(*(this->renderer[i]));
  return;
}

void Display::LazyRender(sf::Shape* shape) { this->window.draw(*shape); }
