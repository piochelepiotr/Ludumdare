#include "gamestate.hpp"
#include "gamestateanchorlistener.hpp"
#include <fstream>

GameState::GameState(StateStack& mystack, StateContext context) :
	State(mystack, context),
	mGameWorld(mAnchors, context),
	mDraggedFlower(noID)
{
	std::ifstream file("niveau1.txt");
	mGameWorld.load(file);
	file.close();
	updateAnchors();
}

GameState::~GameState()
{
}

bool GameState::handleEvent(const sf::Event& event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				requestStackPush(States::Menu);
			else
				handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::MouseButtonPressed:
			mAnchors.injectEvent(event, getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window)));
			break;

		case sf::Event::MouseButtonReleased:
			mAnchors.injectEvent(event, getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window)));
			mIsDragged = false;
			break;

        default:
            break;
    }
    return true;
}

void GameState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{

}

bool GameState::update(sf::Time dt)
{
	bool b = mAnchors.injectMouse(getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window)));
	getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window));
	mGameWorld.update(dt);
	return b;
}

void GameState::draw()
{
    mGameWorld.render(*mContext.window);
}




void GameState::addFlower(sf::Vector2f position, Flower::Type type)
{
	ID<Flower> id = mGameWorld.addFlower(position, type);
	mAnchors.addAnchor<NodeAnchor>(AnchorItem(10.f), *this, id, position);
}

void GameState::addBranch(ID<Flower> f1, ID<Flower> f2)
{
	if (mGameWorld.getCapacity() - mGameWorld.getUsedCapacity())
	{
		mGameWorld.addBranch(f1, f2);
		mGameWorld.setUsedCapacity(mGameWorld.getUsedCapacity()+1);
	}
}



void GameState::onFlowerPressed(ID<Flower> flower)
{
	mDraggedFlower = flower;
	mIsDragged = true;
}

void GameState::onFlowerReleased(ID<Flower> flower)
{
	if (mIsDragged && mDraggedFlower != flower)
		addBranch(mDraggedFlower, flower);
}

void GameState::updateAnchors()
{
    auto flowers = mGameWorld.getFlowers();
    for(auto& id_flower : flowers)
    {
		mAnchors.addAnchor<NodeAnchor>(AnchorItem(10.f), *this,
				id_flower.first, id_flower.second.getPosition());
    }
}
