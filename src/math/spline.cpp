#include "spline.hpp"

CubicCurve::CubicCurve(float cc0, float cc1, float cc2, float cc3) : c0 (cc0)
								   , c1 (cc1)
								   , c2 (cc2)
								   , c3 (cc3) {
  
}

float CubicCurve::evaluate(float val) {
  return c0 + c1*val + c2*val*val + c3*val*val*val;
}

Spline::Spline(sf::Vector2f start, sf::Vector2f end, sf::Vector2f startTangent, sf::Vector2f endTangent) :  x (CubicCurve(start.x, startTangent.x, -2.0f*startTangent.x - 3.0f*start.x + 3*end.x - endTangent.x, endTangent.x - 2.0f * end.x + startTangent.x + 2.0f*start.x)),
													    y (CubicCurve(start.y, startTangent.y, -2.0f*startTangent.y - 3.0f*start.y + 3*end.y - endTangent.y, endTangent.y - 2.0f * end.y + startTangent.y + 2.0f*start.y)) {
  
}

sf::Vector2f normalize(sf::Vector2f v) {
  float norm = sqrt(v.x*v.x + v.y*v.y);
  return sf::Vector2f(v.x/norm, v.y/norm);
}

float norm(sf::Vector2f v) {
  return sqrt(v.x*v.x + v.y*v.y);
}

float SplineShape::getLength() {
  return length;
}

SplineShape::SplineShape(float thickness, int dots, sf::Vector2f start, sf::Vector2f end, sf::Vector2f startTangent, sf::Vector2f endTangent) :
  SplineShape(thickness, dots, Spline(start, end, startTangent, endTangent))
  {

}

SplineShape::SplineShape(float thickness, int dots, Spline spline) :
	spline(spline)
	, dots(dots)
	, thickness(thickness)
	, approx(dots, sf::Vector2f(0.f, 0.f))
	, shape(sf::TrianglesStrip, 2*dots)
	, length(0.f)
{
	float step = 1.0f / static_cast<float>(dots - 1);
	for (int i = 0; i < dots; i++) {
		approx[i] = sf::Vector2f(spline.x.evaluate(i * step), spline.y.evaluate(i * step));
		if (i > 0)
			length += norm(approx[i] - approx[i - 1]);
	}
	
	sf::Vector2f ns = normalize(sf::Vector2f(approx[1].y - approx[0].y, approx[0].x - approx[1].x));
	sf::Vector2f ne = normalize(sf::Vector2f(approx[dots - 1].y - approx[dots - 2].y, approx[dots - 2].y - approx[dots - 1].y));
	shape[0] = approx[0] + ns * thickness;
	shape[1] = approx[0] - ns * thickness;
	shape[2 * dots - 2] = approx[dots - 1] + ne * thickness;
	shape[2 * dots - 1] = approx[dots - 1] - ne * thickness;
	for (int i = 1; i < dots - 1; i++) {
		sf::Vector2f d1 = normalize(sf::Vector2f(approx[i].y - approx[i - 1].y, approx[i - 1].x - approx[i].x));
		sf::Vector2f d2 = normalize(sf::Vector2f(approx[i + 1].y - approx[i].y, approx[i].y - approx[i + 1].y));
		sf::Vector2f d = normalize(d1 + d2);
		shape[2*i] = approx[i] + d * thickness;
		shape[2*i + 1] = approx[i] - d * thickness;
	}
}


void SplineShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape, states);
}
