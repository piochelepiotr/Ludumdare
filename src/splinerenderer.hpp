#pragma once

#include <math/spline.hpp>
#include <memory>

// TODO What is this file ?

struct SplineGraphics
{
	std::unique_ptr<SplineShape> spline;
};

class SplineRenderer
{
	public:
		~SplineRenderer()=default;
		
		void addSpline(const Spline& curve);
	
		void render(sf::RenderTarget& target) const;
	private:
		std::vector<SplineGraphics> mSplines;
};
