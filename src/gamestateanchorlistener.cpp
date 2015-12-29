#include "gamestateanchorlistener.hpp"
#include "gamestate.hpp"

#include <iostream>
// NodeAnchor

NodeAnchor::NodeAnchor(GameState& gameState, ID<Flower> flower, sf::Vector2f position) :
	m_gameState(gameState), m_flower(flower), m_position(position)
{
}

sf::Vector2f NodeAnchor::getPosition()
{
    return m_position;
}

void NodeAnchor::onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f& position)
{
    m_gameState.onFlowerPressed(m_flower);
}

void NodeAnchor::onMouseButtonReleased(sf::Mouse::Button button, const sf::Vector2f& position)
{
	m_gameState.onFlowerReleased(m_flower);
}

void NodeAnchor::onMouseDragged(sf::Mouse::Button button, const sf::Vector2f& position)
{
}

void NodeAnchor::onMouseEnter()
{
}

void NodeAnchor::onMouseLeft()
{
}


// LadybugAnchor



