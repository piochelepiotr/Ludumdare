#include "splinerenderer.hpp"
#include "utils/utils.hpp"
#include "gameworld.inl"

SplineShape::SplineShape(Spline const& spline, float thickness, int dots) : mSpline(spline), mThickness(thickness), mShape(sf::TrianglesStrip, 2*dots), mDots(dots)
{
	float step = 1.0f / (dots - 1);
	std::vector<sf::Vector2f> approx(dots);
	for (int i = 0 ; i < dots ; i++) {
		approx[i] = mSpline.evaluatePos(i * step);
	}

	sf::Vector2f ns = normalize(sf::Vector2f(approx[1].y - approx[0].y, approx[0].x - approx[1].x));
	sf::Vector2f ne = normalize(sf::Vector2f(approx[dots - 1].y - approx[dots - 2].y, approx[dots - 2].x - approx[dots - 1].x));
	mShape[0] = approx[0] + ns * thickness;
	mShape[1] = approx[0] - ns * thickness;
	mShape[2 * dots - 2] = approx[dots - 1] + ne * thickness;
	mShape[2 * dots - 1] = approx[dots - 1] - ne * thickness;
	for (int i = 1; i < dots - 1; i++) {
		sf::Vector2f d1 = normalize(sf::Vector2f(approx[i].y - approx[i - 1].y, approx[i - 1].x - approx[i].x));
		sf::Vector2f d2 = normalize(sf::Vector2f(approx[i + 1].y - approx[i].y, approx[i].x - approx[i + 1].x));
		sf::Vector2f d = normalize(d1 + d2);
		mShape[2*i] = approx[i] + d * thickness;
		mShape[2*i + 1] = approx[i] - d * thickness;
	}
}


void SplineShape::draw(sf::RenderTarget& target) const {
	target.draw(mShape);
}

void SplineShape::partialDraw(sf::RenderTarget& target, float start, float end) const {
	int startDot = std::min(static_cast<int>(start * (mDots - 1) + .5f), mDots - 1);
	int endDot = std::min(static_cast<int>(end * (mDots - 1) + .5f), mDots - 1);

	if (endDot - startDot > 1) {
		sf::VertexArray partialArray(sf::TrianglesStrip, 2*(endDot - startDot + 1));
		for (int i = startDot; i < endDot + 1; i++) {
			partialArray[2*(i - startDot)] = mShape[2*i];
			partialArray[2*(i - startDot) + 1] = mShape[2*i + 1];
		}
		target.draw(partialArray);
	}
}


void SplineRenderer::draw(sf::RenderTarget& target)
{
	auto& branchs = mGameWorld.getBranchs();

	// Nous allons dessiner toutes les splines qui sont dans branchs.
	// Mais on n’est pas obligé de les recalculer,
	// on le fait que si la branche est nouvelle.
	// On se met à jour pour l’instant,
	// en se servant du fait que les id sont triés.
	auto itSaved = mSavedSplines.begin();
	for (auto it = branchs.begin() ; it != branchs.end() ; ++it, ++itSaved)
	{
		ID<Branch> curid = it->first;

		// Certaines branches ont été supprimées, donc on les supprime aussi
		auto nextIt = itSaved;
		for  ( ; nextIt != mSavedSplines.end() && nextIt->first < curid ; ++nextIt);
		if (nextIt != itSaved)
		{
			mSavedSplines.erase(itSaved, nextIt);
			itSaved = mSavedSplines.lower_bound(curid);
		}

		// Si une nouvelle branche, on la rajoute
		if (itSaved == mSavedSplines.end() || curid < itSaved->first)
			itSaved = mSavedSplines.emplace_hint(itSaved,
					std::piecewise_construct,
					std::forward_as_tuple(it->first),
					std::forward_as_tuple(it->second.getSpline(), 3.f));

	}

	// Puis on les dessine
	for (auto& id_spline : mSavedSplines)
		id_spline.second.draw(target);
}
