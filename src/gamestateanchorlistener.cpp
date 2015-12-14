#include "gamestateanchorlistener.hpp"
#include "gamestate.hpp"

#include <iostream>
// NodeAnchor

NodeAnchor::NodeAnchor(GameState& gameState, Node::ID node) : m_gameState(gameState), m_node(node)
{
}

sf::Vector2f NodeAnchor::getPosition()
{
    return m_node.id;
}

void NodeAnchor::onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f& position)
{
	std::cout << "node pressed" << std::endl;
    m_gameState.onNodePressed(m_node);
}

void NodeAnchor::onMouseButtonReleased(sf::Mouse::Button button, const sf::Vector2f& position)
{
	std::cout << "node released iiiiiiiiiiiiiiiiiiiiii" << std::endl;
	m_gameState.onNodeReleased(m_node);
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



