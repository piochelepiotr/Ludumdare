#include <splinerenderer.hpp>
#include <cpp_std_11.hpp>

void SplineRenderer::addSpline(const Spline& spline)
{
	mSplines.push_back(SplineGraphics {make_unique<SplineShape>(5.f, 100, spline)});
}

void SplineRenderer::render(sf::RenderTarget& target) const
{
	for(auto& shape : mSplines)
	{
		target.draw(*shape.spline);
	}
}
