#pragma once

#include <vector>
#include <utility>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include <editor/anchoritem.hpp>

namespace Anchor {
	using ID = std::size_t;
}

class AnchorActionListener;

class AnchorPool
{
	public:
		
		Anchor::ID
		addAnchor (AnchorItem anchor, AnchorActionListener& listener);
		
		bool
		injectEvent (sf::Event event, sf::Vector2f mouse);
		
		bool
		injectMouse (sf::Vector2f mouse);
		
	private:
		std::vector<std::pair<AnchorItem, AnchorActionListener*> > mAnchors;
		AnchorActionListener* mCurrentAnchor=nullptr;
};