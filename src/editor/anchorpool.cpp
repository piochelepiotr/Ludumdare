#include <editor/anchorpool.hpp>
#include <editor/anchoractionlistener.hpp>
#include <SFML/Window/Event.hpp>
#include <utility>

Anchor::ID AnchorPool::addAnchor ( AnchorItem anchor, AnchorActionListener& listener )
{
	mAnchors.push_back(std::pair<AnchorItem, AnchorActionListener*>(anchor, &listener));
	return mAnchors.size();
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
	
	auto first = mAnchors[0].second->getPosition();
	float min_distance = first.x*first.x + first.y*first.y;
	std::size_t min_index = 0;
	
	
	for (std::size_t i=1; i < mAnchors.size(); ++i)
	{
		auto pos = mAnchors[i].second->getPosition();
		float distance = pos.x*pos.x + pos.y*pos.y;
		if (distance < min_distance)
		{
				min_distance = distance;
				min_index = i;
		}
	}
	
	if (mAnchors[min_index].second != mCurrentAnchor)
		mCurrentAnchor->onMouseLeft();
	
	if (min_distance < mAnchors[min_index].first.getRadius()) {
		mCurrentAnchor = mAnchors[min_index].second;
		mCurrentAnchor->onMouseEnter();
		return true;
	}
	
	return false;
}



