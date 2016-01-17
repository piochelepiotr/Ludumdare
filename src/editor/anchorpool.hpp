#pragma once
#include <map>
#include <editor/anchoritem.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf {
	class Event;
}

namespace Anchor {
	using ID = std::size_t;
}

class AnchorActionListener;

class AnchorPool
{
	public:
	~AnchorPool();

	template<typename T, typename... Args> T*
	addAnchor (AnchorItem anchor, Args&&... args);

	template<typename T> void
	removeAnchor (T* ptr);

	bool
	injectEvent (sf::Event event, sf::Vector2f mouse);

	bool
	injectMouse (sf::Vector2f mouse);

	private:
	std::map<AnchorActionListener*, AnchorItem> mAnchors;
	AnchorActionListener* mCurrentAnchor = nullptr;
};

template<typename T, typename... Args> T*
AnchorPool::addAnchor ( AnchorItem anchor, Args&&... args )
{
	auto ptr = new T(args...);
    mAnchors.insert(std::pair<AnchorActionListener*, AnchorItem>(ptr, anchor));
    return ptr;
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
