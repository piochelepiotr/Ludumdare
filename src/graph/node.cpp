#include "node.hpp"

bool Node::operator<(Node const& other) const
{
	sf::Vector2f const& p1 = getPosition(), p2 = other.getPosition();
	return p1.y > p2.y || p1.y == p2.y && p1.x < p2.x;
}


bool Node::operator==(Node const& other) const
{
	return getPosition() == other.getPosition();
}

Node::Type Node::getType()
{
	return m_t;
}
