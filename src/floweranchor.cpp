#include "floweranchor.hpp"
#include <SFML/Window/Event.hpp>
#include "gameworld.inl"

// FlowerAnchor

FlowerAnchor::FlowerAnchor(FlowerAnchorManager& man, ID<Flower> flower, sf::Vector2f position) :
	mManager(man), mFlower(flower), mPosition(position)
{ }

sf::Vector2f FlowerAnchor::getPosition()
{
	return mPosition;
}

void FlowerAnchor::onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f& position)
{
    mManager.onFlowerPressed(this, button);
}

void FlowerAnchor::onMouseButtonReleased(sf::Mouse::Button button, const sf::Vector2f& position)
{
    mManager.onFlowerReleased(this, button);
}

void FlowerAnchor::onMouseEnter()
{
}

void FlowerAnchor::onMouseLeft()
{
}


// FlowerAnchorManager

FlowerAnchorManager::FlowerAnchorManager(GameWorld& gameworld, bool canChangeFlowers) :
	mGameWorld(gameworld), mPool(), mDraggedFlower(noID),
	mCanChangeFlowers(canChangeFlowers)
{}

void FlowerAnchorManager::injectEvent(sf::Event event, sf::Vector2f mouse)
{
	bool toucheQqch = mPool.injectEvent(event, mouse);
	if (event.type == sf::Event::MouseButtonReleased)
	{
		mDraggedFlower = noID;
	}
	else if (event.type == sf::Event::MouseButtonPressed && !toucheQqch && mCanChangeFlowers)
	{
		ID<Flower> id = mGameWorld.addFlower(mouse, Flower::Type::RegularFlower);
		mPool.addAnchor<FlowerAnchor>(AnchorItem(10.f), *this, id, mouse);
	}
}

void FlowerAnchorManager::onFlowerPressed(FlowerAnchor* flower, sf::Mouse::Button button)
{
	mDraggedFlower = flower->getFlowerID();
}

void FlowerAnchorManager::onFlowerReleased(FlowerAnchor* flower, sf::Mouse::Button button)
{
	ID<Flower> flowerID = flower->getFlowerID();
	if(mDraggedFlower != noID)
	{
		if (mDraggedFlower != flowerID)
			mGameWorld.addBranch(mDraggedFlower, flowerID);
		else if (mCanChangeFlowers)
		{
			switch (button)
			{
				case sf::Mouse::Right:
					mPool.removeAnchor(flower);
					mGameWorld.removeFlower(flowerID);
					break;
				case sf::Mouse::Left:
					mGameWorld.nextType(flowerID);
					break;
				default:
					break;
			}
		}
	}
}

void FlowerAnchorManager::rebuildAnchors()
{
	auto flowers = mGameWorld.getFlowers();
	for(auto& id_flower : flowers)
	{
		mPool.addAnchor<FlowerAnchor>(AnchorItem(10.f), *this,
				id_flower.first, id_flower.second.getPosition());
	}
}
