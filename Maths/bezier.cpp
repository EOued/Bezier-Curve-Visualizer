#include "bezier.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

double CBezier::Distance(sf::Vector2f p1, sf::Vector2f p2)
{
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

sf::Vector2f CBezier::Bezier(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3,
                             double t)
{
  return sf::Vector2f(pow(1 - t, 3) * p0.x + 3 * pow(1 - t, 2) * t * p1.x +
                          3 * (1 - t) * pow(t, 2) * p2.x + pow(t, 3) * p3.x,
                      pow(1 - t, 3) * p0.y + 3 * pow(1 - t, 2) * t * p1.y +
                          3 * (1 - t) * pow(t, 2) * p2.y + pow(t, 3) * p3.y

  );
}

std::vector<sf::Vector2f> CBezier::EvenBezier(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2,
                                              sf::Vector2f p3, double l)
{

  // Initialisation of the vector to return

  std::vector<sf::Vector2f> points;
  // arc length estimation
  sf::Vector2f oldPoint = p0;
  sf::Vector2f currentPoint;
  double length         = 0.0f;
  double splittedLength = 0.0f;
  for (double t = 0; t < 1; t += 0.001)
  {
    currentPoint = this->Bezier(p0, p1, p2, p3, t);

    // length computation
    length += this->Distance(oldPoint, currentPoint);
    oldPoint = currentPoint;
  }
  // Computation of evenly spaced points
  oldPoint = p0;
  for (double t = 0; t < 1; t += 0.001)
  {
    currentPoint = this->Bezier(p0, p1, p2, p3, t);
    if (currentPoint == p0 || currentPoint == p3 || splittedLength >= l)
    {
      points.push_back(currentPoint);
      splittedLength = 0;
    }

    // length computation
    splittedLength += this->Distance(oldPoint, currentPoint);
    oldPoint = currentPoint;
  }
  return points;
}
