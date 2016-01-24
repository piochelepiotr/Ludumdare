#pragma once

#include "state.hpp"
#include "textureholder.hpp"
#include "rosetree/flower.hpp"
#include "gameworld.hpp"
#include "floweranchor.hpp"

// TODO: Dans l’éditeur, les fleurs None devrait être affichée
// TODO Il y a quelques redondances avec GameWorld…
class EditLevelState : public State
{
	public:
	EditLevelState(StateStack& mystack, StateContext context);
	virtual ~EditLevelState();
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
	void handlePlayerInput(sf::Keyboard::Key , bool);

	void save(std::string name);
	void load(std::string name);

	private:
	void drawFlower(sf::RenderTarget& target, Flower const& flower) const; // TODO Should not be here


	GameWorld mGameWorld;
	FlowerAnchorManager mFAManager;

	// TODO Should not be here
	std::map<Flower::Type, sf::Sprite> mFlowerSprites;
};
