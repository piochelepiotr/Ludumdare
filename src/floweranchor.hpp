#pragma once
#include "anchor/anchoractionlistener.hpp"
#include "anchor/anchorpool.hpp"
#include "utils/id.hpp"

class Flower;
class GameWorld;

class FlowerAnchorManager;

class FlowerAnchor : public AnchorActionListener
{
	public:
	FlowerAnchor(FlowerAnchorManager& man, ID<Flower> flower, sf::Vector2f position);

	void onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f& position) override;
	void onMouseButtonReleased(sf::Mouse::Button button, const sf::Vector2f& position) override;
	void onMouseEnter() override;
	void onMouseLeft() override;
	sf::Vector2f getPosition() override;
	ID<Flower> getFlowerID() { return mFlower; }

	private:
	FlowerAnchorManager& mManager;
	ID<Flower> mFlower;
	sf::Vector2f mPosition;
};

class FlowerAnchorManager
{
	public:
	FlowerAnchorManager(GameWorld& gameworld, bool canChangeFlowers);

	/// @return true si l’événement a été traité, false sinon
	bool injectEvent(sf::Event event, sf::Vector2f mouse);
	inline bool injectMouse(sf::Vector2f mouse)
	{ return mPool.injectMouse(mouse); }

	void onFlowerPressed(FlowerAnchor* flower, sf::Mouse::Button button);
	void onFlowerReleased(FlowerAnchor* flower, sf::Mouse::Button button);

	void rebuildAnchors();

	private:
	GameWorld& mGameWorld;
	AnchorPool mPool;
	ID<Flower> mDraggedFlower;
	bool mCanChangeFlowers;
};
