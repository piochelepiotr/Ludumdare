#include <editor/nodeanchorlistener.hpp>

NodeAnchorListener::NodeAnchorListener(Graph& graph, Node::ID node) : m_graph(graph), m_node(node)
{
}

sf::Vector2f NodeAnchorListener::getPosition()
{
	return m_graph[node].getPosition();
}

void NodeAnchorListener::onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f& position)
{
} // TODO

void NodeAnchorListener::onMouseButtonReleased(sf::Mouse::Button button, const sf::Vector2f& position)
{

}

void NodeAnchorListener::onMouseDragged(sf::Mouse::Button button, const sf::Vector2f& position)
{
} // TODO

void NodeAnchorListener::onMouseEnter()
{
} // TODO

void NodeAnchorListener::onMouseLeft()
{
} // TODO
