#ifndef BEZIER_H
#define BEZIER_H

#include <SFML/System/Vector2.hpp>
#include <vector>

/**
   @class CBezier
   @brief This class give some functions to generate Cubic Bezier Curves.
 */
class CBezier
{
public:
  /**
   @brief This function give the distance between two points.
   @param p1 A point.
   @param p2 A point.
   @retval double The distance between all points.
  */
  double Distance(sf::Vector2f p1, sf::Vector2f p2);
  /**
   @brief This function compute a Cubic Bezier Curve.
   @param p0 The origin.
   @param p1 The direction of the origin.
   @param p2 The direction of the goal.
   @param p3 The goal.
   @param t The time variable in the computation of a bezier curve, between 0 and 1.
   @retval sf::Vector2f The point on the bezier curve at time t.
  */
  sf::Vector2f Bezier(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, double t);

  /**
   @brief This function compute a Cubic Bezier Curve where the points are evenly spaced.
   @param p0 The origin.
   @param p1 The direction of the origin.
   @param p2 The direction of the goal.
   @param p3 The goal.
   @param l The space between two points.
   @retval std::vector<sf::Vector2f> A vector of points representing the curve.
  */
  std::vector<sf::Vector2f> EvenBezier(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2,
                                       sf::Vector2f p3, double l);
};

#endif
