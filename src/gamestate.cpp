#include "gamestate.hpp"
#include "gameworld.inl"
#include <fstream>


GameState::GameState(StateStack& mystack, StateContext context, GameWorld::Mode mode) :
	State(mystack, context),
	mGameWorld(context, mode),
	mFAManager(mGameWorld, mode == GameWorld::EditMode)
{
	std::ifstream file("niveau1.txt");
	mGameWorld.load(file);
	mFAManager.rebuildAnchors();
	file.close();
}
GameState::GameState(StateStack& mystack, StateContext context) :
	GameState(mystack, context, GameWorld::GameMode)
{
}

GameState::~GameState()
{
}

bool GameState::handleEvent(const sf::Event& event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					requestStackPush(States::Menu);
					return true;
				default:
					return handlePlayerInput(event.key.code, true);
			}
			break;

		case sf::Event::KeyReleased:
			return handlePlayerInput(event.key.code, false);

		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
			mFAManager.injectEvent(event, getMousePos());
		case sf::Event::MouseMoved:
			return true;

		default:
			break;
	}
	return false;
}



bool GameState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	return true;
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

void GameState::load(std::string name)
{
	std::ifstream file(name);
	mGameWorld.load(file);
	file.close();
	mFAManager.rebuildAnchors();
}

