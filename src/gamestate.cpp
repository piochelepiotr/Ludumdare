#include "gamestate.hpp"
#include "gameworld.inl"
#include <fstream>

GameState::GameState(StateStack& mystack, StateContext context) :
	State(mystack, context),
	mGameWorld(context, GameWorld::GameMode),
	mFAManager(mGameWorld, false)
{
	std::ifstream file("niveau1.txt");
	mGameWorld.load(file);
	mFAManager.rebuildAnchors();
	file.close();
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
		case sf::Event::MouseButtonReleased:
			mFAManager.injectEvent(event, getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window)));
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
	bool b = mFAManager.injectMouse(getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window)));
	mGameWorld.update(dt);
	return b;
}

void GameState::draw()
{
    mGameWorld.render(*mContext.window);
}
