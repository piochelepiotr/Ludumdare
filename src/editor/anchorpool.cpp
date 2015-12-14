#include <editor/anchorpool.hpp>
#include <editor/anchoractionlistener.hpp>
#include <SFML/Window/Event.hpp>
#include <utility>
#include <iostream>

AnchorPool::~AnchorPool()
{
    for (auto ptr : mAnchorPtrs)
	delete ptr;
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
	// FIXME améliorer en prenant en compte le rayon
	
	if (mAnchors.size() == 0) return false;
	std::cout << mAnchors.size() << std::endl;
	
	auto first = mAnchors[0].second->getPosition();
	auto offset = first - mouse;
	float min_distance = offset.x*offset.x + offset.y*offset.y;
	std::size_t min_index = 0;
	
	
	for (std::size_t i=1; i < mAnchors.size(); ++i)
	{
		auto pos = mAnchors[i].second->getPosition();
		auto offset = pos - mouse;
		float distance = offset.x*offset.x + offset.y*offset.y;
		if (distance < min_distance)
		{
				min_distance = distance;
				min_index = i;
		}
	}
	
	if (mCurrentAnchor && mAnchors[min_index].second != mCurrentAnchor)
		mCurrentAnchor->onMouseLeft();
	float radius = mAnchors[min_index].first.getRadius();
	if (min_distance < radius*radius) {
		mCurrentAnchor = mAnchors[min_index].second;
		mCurrentAnchor->onMouseEnter();
		return true;
	} else {
		mCurrentAnchor = nullptr;
	}
	
	return false;
}



