#pragma once
#include <map>
#include <anchor/anchoritem.hpp>
#include <SFML/System/Vector2.hpp>


// TODO rajouter un appel à AnchorActionListener::onMouseDragged()
// dans les cas propices

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

	void
	removeAnchor (AnchorActionListener* ptr);

	/// @return true il y a eu interaction avec une ancre
	bool
	injectEvent (sf::Event event, sf::Vector2f mouse);

	/// @return true si on est sur une ancre, false sinon
	bool
	injectMouse (sf::Vector2f mouse);

	private:
	std::map<AnchorActionListener*, AnchorItem> mAnchors;
	AnchorActionListener* mCurrentAnchor = nullptr;
};


template<typename T, typename... Args> T*
AnchorPool::addAnchor ( AnchorItem anchor, Args&&... args )
{
	auto ptr = new T(std::forward<Args>(args)...);
    mAnchors.insert(std::pair<AnchorActionListener*, AnchorItem>(ptr, anchor));
    return ptr;
}
