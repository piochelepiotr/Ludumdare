#pragma once

#include "utils/id.hpp"
#include <SFML/Graphics.hpp>

class Branch;
class Spline;
class GameWorld;

class SplineShape {
	public:
	SplineShape(Spline const& spline, float thickness, int dots = 30);

	void draw(sf::RenderTarget& target) const;
	void partialDraw(sf::RenderTarget& target, float start, float end) const;

	private:
	Spline const& mSpline;
	float mThickness;
	sf::VertexArray mShape;
	int mDots;
};



class SplineRenderer
{
	public:
	SplineRenderer(GameWorld const& gw) : mGameWorld(gw) {};
	void draw(sf::RenderTarget& target);

	private:
	GameWorld const& mGameWorld;
	std::map<ID<Branch>, SplineShape> mSavedSplines;
};
