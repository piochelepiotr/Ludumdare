#pragma once

#include <vector>
#include <utility>
#include <memory>
#include <cpp_std_11.hpp>

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
		~AnchorPool();
		
		template<typename T, typename... Args> Anchor::ID
		addAnchor (AnchorItem anchor, Args&... args);
		
		bool
		injectEvent (sf::Event event, sf::Vector2f mouse);
		
		bool
		injectMouse (sf::Vector2f mouse);
		
	private:
		std::vector<std::pair<AnchorItem, AnchorActionListener*> > mAnchors;
		std::vector<AnchorActionListener* > mAnchorPtrs;
		AnchorActionListener* mCurrentAnchor=nullptr;
};

template<typename T, typename... Args> Anchor::ID 
AnchorPool::addAnchor ( AnchorItem anchor, Args&... args )
{
    mAnchorPtrs.push_back(new T(args...));
    mAnchors.push_back(std::pair<AnchorItem, AnchorActionListener*>(anchor, mAnchorPtrs.back()));
    return mAnchors.size();
}
