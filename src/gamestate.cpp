#include "gamestate.hpp"

#include <iostream>

GameState::GameState(StateStack& mystack, Context context)
: State(mystack, context)
  , mDialogbox(context.fonts->get(Font::Text), L"Souhaitez vous declencher la fin de l univers")
  , mYes(context.fonts->get(Font::Text), "YES", std::bind(&GameState::finDeUnivers, this))
  , mNo(context.fonts->get(Font::Text), "NO", std::bind(&DialogBox::close, &mDialogbox))
{
	mDialogbox.setPosition(600,600);
	mDialogbox.addButton(mYes);
	mDialogbox.addButton(mNo);
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
		case sf::Event::MouseButtonReleased: {
			sf::Vector2f mouse = getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window));
			mDialogbox.injectEvent(event, mouse);
			break;
		}
	    
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
  sf::Vector2f mouse = getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window));
  mDialogbox.injectMouse(mouse);
  mGameWorld.update(dt);
  return true;
}

void GameState::draw()
{
	getContext().window->draw(mDialogbox);
}

void GameState::finDeUnivers()
{
	std::cout << "BOOM" << std::endl;
}
