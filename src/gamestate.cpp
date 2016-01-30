#include "gamestate.hpp"
#include "gameworld.inl"
#include "textureholder.hpp"
#include <fstream>


GameState::GameState(StateStack& mystack, StateContext context, GameWorld::Mode mode) :
	State(mystack, context),
	mGameWorld(mode),
	mFAManager(mGameWorld, mode == GameWorld::EditMode),
	mGameDrawer(mGameWorld)
{
	std::ifstream file("niveau1.txt");
	mGameWorld.load(file);
	mFAManager.rebuildAnchors();
	file.close();
}

GameState::GameState(StateStack& mystack, StateContext context) :
	GameState(mystack, context, GameWorld::GameMode)
{
	// We just have to set Sprites
	mGameDrawer.setBackGround(context.textures->get(Texture::Background));

	mGameDrawer.setLadybug(Ladybug::RedLadybug, context.textures->get(Texture::NormalLadybug), sf::Vector2f(50.f, 70.f), sf::Vector2f(.9f, .9f));
	mGameDrawer.setLadybug(Ladybug::RedBlackLadybug, context.textures->get(Texture::DefensiveLadybug), sf::Vector2f(50.f, 70.f), sf::Vector2f(.9f, .9f));
	mGameDrawer.setLadybug(Ladybug::BlackLadybug, context.textures->get(Texture::OffensiveLadybug), sf::Vector2f(50.f, 70.f), sf::Vector2f(.9f, .9f));
	mGameDrawer.setAphid(context.textures->get(Texture::Aphid), sf::Vector2f(50.f, 75.f), sf::Vector2f(.6f, .6f));

	mGameDrawer.setFlower(Flower::RegularFlower, context.textures->get(Texture::RegularFlower), sf::Vector2f(100.f, 100.f), sf::Vector2f(.3f, .3f));
	mGameDrawer.setFlower(Flower::AphidFlower, context.textures->get(Texture::AphidFlower), sf::Vector2f(100.f, 100.f), sf::Vector2f(.3f, .3f));
	mGameDrawer.setFlower(Flower::LadybugFlower, context.textures->get(Texture::LadybugFlower), sf::Vector2f(100.f, 100.f), sf::Vector2f(.3f, .3f));
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
    //mGameWorld.render(*mContext.window);
	mGameDrawer.draw(*mContext.window);
}

void GameState::load(std::string name)
{
	std::ifstream file(name);
	mGameWorld.load(file);
	file.close();
	mFAManager.rebuildAnchors();
}

