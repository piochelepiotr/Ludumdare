#pragma once
#include "state/state.hpp"
#include "gameworld.hpp"
#include "floweranchor.hpp"


class GameState : public State
{
	public:
	GameState(StateStack& mystack, StateContext context);
	virtual ~GameState();
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
	bool handlePlayerInput(sf::Keyboard::Key , bool);

	void load(std::string name);

	protected:
	GameState(StateStack& mystack, StateContext context, GameWorld::Mode mode);

	GameWorld mGameWorld;
	FlowerAnchorManager mFAManager;
};
