#pragma once

#include <map>
#include <utility>
#include <algorithm>
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
		
		template<typename T, typename... Args> T*
		addAnchor (AnchorItem anchor, Args&... args);
	
		template<typename T> void
		removeAnchor (T* ptr);
		
		bool
		injectEvent (sf::Event event, sf::Vector2f mouse);
		
		bool
		injectMouse (sf::Vector2f mouse);
		
	private:
		std::map<AnchorActionListener*, AnchorItem> mAnchors;
		//std::set<std::pair<AnchorItem, AnchorActionListener*> > mAnchors;
		//std::set<AnchorActionListener* > mAnchorPtrs;
		AnchorActionListener* mCurrentAnchor=nullptr;
};

template<typename T, typename... Args> T*
AnchorPool::addAnchor ( AnchorItem anchor, Args&... args )
{
	auto ptr = new T(args...);
    //mAnchorPtrs.insert(ptr);
    mAnchors.insert(std::pair<AnchorActionListener*, AnchorItem>(ptr, anchor));
    return static_cast<T*>(ptr);
}

template<typename T> void
AnchorPool::removeAnchor(T* ptr)
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
