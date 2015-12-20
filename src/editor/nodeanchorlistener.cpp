#include <editor/nodeanchorlistener.hpp>
#include "editlevelstate.hpp"

NodeAnchorListener::NodeAnchorListener(EditLevelState& editLevelState, Node::ID node) : m_editLevelState(editLevelState), m_node(node)
{
}

sf::Vector2f NodeAnchorListener::getPosition()
{
    return m_node.id;
}

void NodeAnchorListener::onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f& position)
{
    m_editLevelState.onNodePressed(m_node, button);
}

void NodeAnchorListener::onMouseButtonReleased(sf::Mouse::Button button, const sf::Vector2f& position)
{
	m_editLevelState.onNodeReleased(m_node, button);
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
