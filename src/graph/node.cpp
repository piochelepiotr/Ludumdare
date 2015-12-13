#include "node.hpp"

bool Node::ID::operator<(Node::ID const& other) const
{
	return id.y > other.id.y || (id.y == other.id.y && id.x < other.id.x);
}

bool Node::ID::operator==(Node::ID const& other) const
{
	return id == other.id;
}

Node::Type Node::getType()
{
	return m_t;
}


void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape c(50);
	c.setFillColor(sf::Color::Red);
	sf::Transform movement;
	movement.translate(m_pos);
	states.transform *= movement;
	target.draw(c, states);
}
