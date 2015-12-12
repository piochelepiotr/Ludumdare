#include "gamestate.hpp"

GameState::GameState(StateStack& mystack, Context context)
: State(mystack, context)
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
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
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
    return true;
}

void GameState::draw()
{

}