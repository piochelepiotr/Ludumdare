#pragma once
#include <SFML/System/Vector2.hpp>

struct CubicCurve {
	public:
	CubicCurve(float c0, float c1, float c2, float c3);
	float evaluate(float val) const;
	float deriv(float val) const;
	private:
	float c0, c1, c2, c3; //c0 + c1 X + c2 X^2 + c3 X^3
};

class Spline {
	public:
	// La longueur ne sera calculée que si dots > 1
	Spline(sf::Vector2f start, sf::Vector2f end, sf::Vector2f startTangent, sf::Vector2f endTangent, int dots = 30);

	sf::Vector2f evaluatePos(float val) const;
	sf::Vector2f evaluateSpeed(float val) const;
	int getDots() const { return dots; }
	float getLength() const { return length; }

	private:
	CubicCurve x;
	CubicCurve y;
	int dots;
	float length;
};
