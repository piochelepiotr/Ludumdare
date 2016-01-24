#pragma once
#include "state.hpp"
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
	void handlePlayerInput(sf::Keyboard::Key , bool);

	private:
	GameWorld mGameWorld;
	FlowerAnchorManager mFAManager;
};
