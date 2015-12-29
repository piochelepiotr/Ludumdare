#include <editor/nodeanchorlistener.hpp>
#include "editlevelstate.hpp"

NodeAnchorListener::NodeAnchorListener(EditLevelState& editLevelState, ID<Flower> flower, sf::Vector2f position) : m_editLevelState(editLevelState), m_flower(flower), m_position(position)
{
}

sf::Vector2f NodeAnchorListener::getPosition()
{
	return m_position;
}

void NodeAnchorListener::onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f& position)
{
    m_editLevelState.onFlowerPressed(m_flower, button);
}

void NodeAnchorListener::onMouseButtonReleased(sf::Mouse::Button button, const sf::Vector2f& position)
{
	m_editLevelState.onFlowerReleased(m_flower, button);
}

void NodeAnchorListener::onMouseDragged(sf::Mouse::Button button, const sf::Vector2f& position)
{
}

void NodeAnchorListener::onMouseEnter()
{
}

void NodeAnchorListener::onMouseLeft()
{
}
