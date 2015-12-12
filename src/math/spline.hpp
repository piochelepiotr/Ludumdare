#pragma once
#include <SFML/Graphics.hpp>

struct CubicCurve {
public:
  CubicCurve(float c0, float c1, float c2, float c3);
  float evaluate(float val);
private:
  float c0, c1, c2, c3; //c0 + c1 X + c2 X^2 + c3 X^3
};

class Spline {
public:
  Spline(sf::Vector2f start, sf::Vector2f end, sf::Vector2f startTangent, sf::Vector2f endTangent);
  CubicCurve x;
  CubicCurve y;
};

class SplineShape {
public:
  SplineShape(float thickness, int dots, sf::Vector2f start, sf::Vector2f end, sf::Vector2f startTangent, sf::Vector2f endTangent);
  void draw(sf::RenderWindow *window);
    
private:
  Spline spline;
  int dots;
  float thickness;
  std::vector<sf::Vector2f> approx;
  sf::VertexArray shape;
  float length;
};

//util. maybe i should put it in a class or something but idc
sf::Vector2f normalize(sf::Vector2f v);
