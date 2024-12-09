#include "Display/display.h"
#include "Maths/bezier.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <vector>

int main()
{
  CBezier bezier;

  // Window initialisation
  Display display;
  display.window.setFramerateLimit(60);

  // Description of each points on the screen
  int pointRadius             = 4;
  double originDirectionAngle = 0;
  double goalDirectionAngle   = 0;
  int originDirectionDistance = 20;
  int goalDirectionDistance   = 20;

  // Bezier points position
  sf::Vector2f originPosition          = sf::Vector2f(100, 100);
  sf::Vector2f goalPosition            = sf::Vector2f(300, 300);
  sf::Vector2f originDirectionPosition = sf::Vector2f(110, 110);
  sf::Vector2f goalDirectionPosition   = sf::Vector2f(310, 310);

  // Initialisation of the 4 bezier points needed for the curve
  sf::CircleShape* origin = new sf::CircleShape;
  origin->setFillColor(sf::Color(149, 148, 227));
  origin->setRadius(pointRadius);
  origin->setOrigin(pointRadius, pointRadius);
  sf::CircleShape* originDirection = new sf::CircleShape;
  originDirection->setFillColor(sf::Color(73, 73, 224));
  originDirection->setRadius(pointRadius);
  originDirection->setOrigin(pointRadius, pointRadius);
  sf::CircleShape* goalDirection = new sf::CircleShape;
  goalDirection->setFillColor(sf::Color(73, 224, 73));
  goalDirection->setRadius(pointRadius);
  goalDirection->setOrigin(pointRadius, pointRadius);
  sf::CircleShape* goal = new sf::CircleShape;
  goal->setFillColor(sf::Color(149, 227, 148));
  goal->setRadius(pointRadius);
  goal->setOrigin(pointRadius, pointRadius);

  // Initialisation of the lines
  sf::VertexArray originLines(sf::Lines, 2);
  sf::VertexArray goalLines(sf::Lines, 2);

  // Adding points to renderer
  display.AddToRenderer(origin);
  display.AddToRenderer(originDirection);
  display.AddToRenderer(goalDirection);
  display.AddToRenderer(goal);

  // Index of the currently selected point
  int pointSelection = -1;
  // Is a point holded
  bool holding = false;
  // Tolerance when picking a point
  double tolerance = 2;

  // Window loop
  while (display.window.isOpen())
  {
    // Clocking for deltaTime
    static sf::Clock clock;
    float deltaTime = clock.restart().asSeconds();

    // Clocking for keypress cap
    static sf::Clock timeSinceKeypress;

    // Display functions
    display.window.display();
    display.window.clear();

    // Updating positions of bezier points
    origin->setPosition(originPosition);
    originDirection->setPosition(originDirectionPosition);
    goalDirection->setPosition(goalPosition);
    goal->setPosition(goalDirectionPosition);

    // Updating positions of tangents
    originLines[0] = originPosition;
    originLines[1] = originDirectionPosition;
    goalLines[0]   = goalPosition;
    goalLines[1]   = goalDirectionPosition;

    // Close event
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
         sf::Keyboard::isKeyPressed(sf::Keyboard::C)))
      display.window.close();

    // Mouse events for point grabbing
    sf::Vector2f mousePosition =
        display.window.mapPixelToCoords(sf::Mouse::getPosition(display.window));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      if (!holding)
      {
        if (bezier.Distance(originPosition, mousePosition) <= pointRadius + tolerance)
          pointSelection = 0;
        if (bezier.Distance(originDirectionPosition, mousePosition) <= pointRadius + tolerance)
          pointSelection = 1;
        if (bezier.Distance(goalDirectionPosition, mousePosition) <= pointRadius + tolerance)
          pointSelection = 2;
        if (bezier.Distance(goalPosition, mousePosition) <= pointRadius + tolerance)
          pointSelection = 3;
      }
      holding = true;
      switch (pointSelection)
      {
      case 0: originPosition = mousePosition; break;
      case 1: originDirectionPosition = mousePosition; break;
      case 2: goalDirectionPosition = mousePosition; break;
      case 3: goalPosition = mousePosition; break;
      default: break;
      }
    }

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && holding)
    {
      holding        = false;
      pointSelection = -1;
    }

    // Points for the bezier curve
    sf::CircleShape bezierPoints(1);
    bezierPoints.setFillColor(sf::Color(176, 31, 191));
    bezierPoints.setOrigin(bezierPoints.getRadius(), bezierPoints.getRadius());
    for (double t = 0; t <= 1; t += 0.001)
    {
      bezierPoints.setPosition(bezier.Bezier(originPosition, originDirectionPosition,
                                             goalDirectionPosition, goalPosition, t));
      display.LazyRender(&bezierPoints);
    }

    std::vector<sf::Vector2f> points = bezier.EvenBezier(originPosition, originDirectionPosition,
                                                         goalDirectionPosition, goalPosition, 10);
    bezierPoints.setRadius(2);
    bezierPoints.setFillColor(sf::Color(176, 191, 31));
    bezierPoints.setOrigin(bezierPoints.getRadius(), bezierPoints.getRadius());
    for (int _ = 0; _ < points.size(); _++)
    {
      bezierPoints.setPosition(points[_]);
      display.LazyRender(&bezierPoints);
    }

    // Manually rendering lines
    display.window.draw(originLines);
    display.window.draw(goalLines);
    display.Render();

    // Resising
    sf::Event event;
    display.window.pollEvent(event);
    if (event.type == sf::Event::Resized)
    {
      sf::View view(sf::FloatRect(0, 0, event.size.width, event.size.height));
      display.window.setView(view);
    }
  }
  display.DeleteRenderer();
  return 0;
}
