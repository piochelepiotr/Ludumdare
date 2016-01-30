#include "spline.hpp"
#include "utils/utils.hpp"

CubicCurve::CubicCurve(float cc0, float cc1, float cc2, float cc3) :
	c0 (cc0), c1 (cc1), c2 (cc2), c3 (cc3)
{ }

float CubicCurve::evaluate(float val) const {
	return c0 + val*(c1 + val*(c2 + val*(c3)));
}

float CubicCurve::deriv(float val) const {
	return c1 + val*(2.0f*c2 + val *(3.0f * c3));
}

Spline::Spline(sf::Vector2f start, sf::Vector2f end, sf::Vector2f startTangent, sf::Vector2f endTangent, int dots) :
	x(
			start.x,
			startTangent.x,
			-2.0f*startTangent.x - 3.0f*start.x + 3*end.x - endTangent.x,
			endTangent.x - 2.0f * end.x + startTangent.x + 2.0f*start.x
	 ),
	y(
			start.y,
			startTangent.y,
			-2.0f*startTangent.y - 3.0f*start.y + 3*end.y - endTangent.y,
			endTangent.y - 2.0f * end.y + startTangent.y + 2.0f*start.y
	 ),
	dots(dots)
{
	if (dots <= 1)
		return;
	float step = 1.0f / (dots - 1);
	float len;
	sf::Vector2f lastPos = evaluatePos(0);
	for (int i = 1 ; i < dots ; i++) {
		sf::Vector2f newPos = evaluatePos(i * step);
		len += norm(newPos - lastPos);
		lastPos = newPos;
	}
	length = len;
}

sf::Vector2f Spline::evaluatePos(float val) const {
	return sf::Vector2f(x.evaluate(val), y.evaluate(val));
}

sf::Vector2f Spline::evaluateSpeed(float val) const {
	return sf::Vector2f(x.deriv(val), y.deriv(val));
}
