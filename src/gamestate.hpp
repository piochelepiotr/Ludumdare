#pragma once
#include "state/state.hpp"
#include "gameworld.hpp"
#include "floweranchor.hpp"
#include "gamedrawer.hpp"


class GameState : public State
{
	public:
	GameState(StateStack& mystack, StateContext context);
	virtual ~GameState();
	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;
	bool handlePlayerInput(sf::Keyboard::Key , bool);

	void load(std::string name);

	protected:
	// This one does not set Sprites
	GameState(StateStack& mystack, StateContext context, GameWorld::Mode mode);

	GameWorld mGameWorld;
	FlowerAnchorManager mFAManager;
	GameDrawer mGameDrawer;
};
