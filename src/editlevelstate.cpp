#include "editlevelstate.hpp"
#include "gameworld.inl"
#include "textureholder.hpp"
#include <fstream>


EditLevelState::EditLevelState(StateStack& mystack, StateContext context) :
	GameState(mystack, context, GameWorld::EditMode)
{
	// We just have to set Sprites
	mGameDrawer.setFlower(Flower::RegularFlower, context.textures->get(Texture::RegularFlower), sf::Vector2f(100.f, 100.f), sf::Vector2f(.3f, .3f));
	mGameDrawer.setFlower(Flower::AphidFlower, context.textures->get(Texture::AphidFlower), sf::Vector2f(100.f, 100.f), sf::Vector2f(.3f, .3f));
	mGameDrawer.setFlower(Flower::LadybugFlower, context.textures->get(Texture::LadybugFlower), sf::Vector2f(100.f, 100.f), sf::Vector2f(.3f, .3f));
	mGameDrawer.setFlower(Flower::Node, context.textures->get(Texture::NodeFlower), sf::Vector2f(20.f, 20.f));
}

EditLevelState::~EditLevelState()
{
	save("niveau1.txt");
}

void EditLevelState::save(std::string name)
{
	std::ofstream file(name);
	mGameWorld.save(file);
	file.close();
}
