#include "editor/editlevelstate.hpp"
#include <fstream>
#include "rosetree/branch.hpp"
#include "gameworld.inl"


EditLevelState::EditLevelState(StateStack& mystack, StateContext context) :
	State(mystack, context),
	mGameWorld(context, GameWorld::EditMode),
	mFAManager(mGameWorld, true)
{
	load("niveau1.txt");
	auto it = mFlowerSprites.insert(std::make_pair(Flower::RegularFlower,
				sf::Sprite(context.textures->get(Texture::ID::RegularFlower))));
	it.first->second.setOrigin(100.f, 100.f);
	it = mFlowerSprites.insert(std::make_pair(Flower::AphidFlower,
				sf::Sprite(context.textures->get(Texture::ID::AphidFlower))));
	it.first->second.setOrigin(100.f, 100.f);
	it.first->second.setColor(sf::Color::Green);
	it = mFlowerSprites.insert(std::make_pair(Flower::LadybugFlower,
				sf::Sprite(context.textures->get(Texture::ID::LadybugFlower))));
	it.first->second.setOrigin(100.f, 100.f);
	it.first->second.setColor(sf::Color::Red);

}

EditLevelState::~EditLevelState()
{
	save("niveau1.txt");
}

bool EditLevelState::handleEvent(const sf::Event& event)
{
	auto mouse = mContext.window->mapPixelToCoords(sf::Mouse::getPosition(*mContext.window));
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
			mFAManager.injectEvent(event, mouse);
			break;

		default:
			break;
	}
	return false;
}

void EditLevelState::handlePlayerInput(sf::Keyboard::Key, bool)
{

}

bool EditLevelState::update(sf::Time dt)
{
	bool b = mFAManager.injectMouse(getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window)));
	mGameWorld.update(dt);
	return b;
}

void EditLevelState::draw()
{
	getContext().window->clear();
	mGameWorld.render(*getContext().window);
}


void EditLevelState::load(std::string name)
{
	std::ifstream file(name);
	mGameWorld.load(file);
	file.close();
	mFAManager.rebuildAnchors();
}

void EditLevelState::save(std::string name)
{
	std::ofstream file(name);
	mGameWorld.save(file);
	file.close();
}
