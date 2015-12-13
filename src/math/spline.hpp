#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

struct CubicCurve {
public:
  CubicCurve(float c0, float c1, float c2, float c3);
  float evaluate(float val);
  float deriv(float val);
private:
  float c0, c1, c2, c3; //c0 + c1 X + c2 X^2 + c3 X^3
};

class Spline {
public:
  Spline(sf::Vector2f start, sf::Vector2f end, sf::Vector2f startTangent, sf::Vector2f endTangent);
  sf::Vector2f evaluatePos(float val);
  sf::Vector2f evaluateSpeed(float val);
  CubicCurve x;
  CubicCurve y;
};

class SplineShape : public sf::Drawable{
public:
  SplineShape(float thickness, int dots, sf::Vector2f start, sf::Vector2f end, sf::Vector2f startTangent, sf::Vector2f endTangent);
  SplineShape(float thickness, int dots, Spline spline);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  void partialDraw(sf::RenderTarget& target, sf::RenderStates states, float start, float end);
  float getLength();
  Spline getSpline();
    
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
float norm(sf::Vector2f v);
