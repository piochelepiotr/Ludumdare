#include <editor/anchorpool.hpp>
#include <editor/anchoractionlistener.hpp>
#include <SFML/Window/Event.hpp>
#include <utility>
#include <iostream>
#include <limits>
#include "utils.hpp"

AnchorPool::~AnchorPool()
{
	/*
    for (auto ptr : mAnchorPtrs)
	delete ptr;
	*/
	for (auto& pair : mAnchors)
		delete pair.first;
}

bool AnchorPool::injectEvent ( sf::Event event, sf::Vector2f mouse )
{
	if(!mCurrentAnchor) return false;
	switch(event.type)
	{
		case sf::Event::MouseButtonPressed:
			mCurrentAnchor->onMouseButtonPressed(event.mouseButton.button, mouse); return true;

		case sf::Event::MouseButtonReleased:
			mCurrentAnchor->onMouseButtonReleased(event.mouseButton.button, mouse); return true;

		default: break;
	}
	return false;
}

bool AnchorPool::injectMouse ( sf::Vector2f mouse )
{
	// TODO améliorer en prenant en compte le rayon

	float min_distance = std::numeric_limits<float>::infinity();
	auto min_it = mAnchors.end();

	for (auto it = mAnchors.begin() ; it != mAnchors.end() ; it++)
	{
		float distance = squareNorm(mouse - it->first->getPosition());
		if (distance < min_distance)
		{
			min_distance = distance;
			min_it = it;
		}
	}

	if (min_it == mAnchors.end())
		return false;

	bool isOnAnchor = min_distance < min_it->second.getSquareRadius();
	if (mCurrentAnchor && (min_it->first != mCurrentAnchor || !isOnAnchor))
	{
		mCurrentAnchor->onMouseLeft();
		mCurrentAnchor = nullptr;
	}

	if (isOnAnchor)
	{
		mCurrentAnchor = min_it->first;
		mCurrentAnchor->onMouseEnter();
		return true;
	}
	else
		return false;
}



