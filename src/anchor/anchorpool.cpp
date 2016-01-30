#include <anchor/anchorpool.hpp>
#include <anchor/anchoractionlistener.hpp>
#include <SFML/Window/Event.hpp>
#include "utils/utils.hpp"
#include <limits>

AnchorPool::~AnchorPool()
{
	for (auto& pair : mAnchors)
		delete pair.first;
}


void
AnchorPool::removeAnchor(AnchorActionListener* ptr)
{
	auto it = mAnchors.find(ptr);
	if (it != mAnchors.end())
	{
		if (mCurrentAnchor == it->first)
			mCurrentAnchor = nullptr;
		delete it->first;
		mAnchors.erase(it);
	}
}

bool AnchorPool::injectEvent ( sf::Event event, sf::Vector2f mouse )
{
	switch(event.type)
	{
		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
			// On fait cela au cas où le clic à lieu avant qu’on ai eu le temps
			// d’update le mouvement (cas d’un écran tactile)
			if (injectMouse(mouse))
			{
				if (event.type == sf::Event::MouseButtonPressed)
					mCurrentAnchor->onMouseButtonPressed(event.mouseButton.button, mouse);
				else
					mCurrentAnchor->onMouseButtonReleased(event.mouseButton.button, mouse);
				return true;
			}
			break;

		default:
			break;
	}
	return false;
}


bool AnchorPool::injectMouse ( sf::Vector2f mouse )
{
	// On recherche l’ancre la plus proche qu’on touche
	float min_distance = std::numeric_limits<float>::infinity();
	auto min_it = mAnchors.end();
	for (auto it = mAnchors.begin() ; it != mAnchors.end() ; ++it)
	{
		AnchorActionListener& anchor = *it->first;
		AnchorItem& item = it->second;
		float distance = squareNorm(mouse - anchor.getPosition());
		float radius = item.getRadius();
		if (distance < radius*radius && distance < min_distance)
		{
			min_distance = distance;
			min_it = it;
		}
	}

	bool isOnAnchor = min_it != mAnchors.end();

	// Si on a quitté l’ancre précédente, on ne manque pas de le faire savoir
	if (mCurrentAnchor && (!isOnAnchor || min_it->first != mCurrentAnchor))
	{
		mCurrentAnchor->onMouseLeft();
		mCurrentAnchor = nullptr;
	}

	// Enfin, on fait ce qu’on a à faire avec cette ancre
	if (isOnAnchor)
	{
		mCurrentAnchor = min_it->first;
		mCurrentAnchor->onMouseEnter();
		return true;
	}
	else
		return false;
}
