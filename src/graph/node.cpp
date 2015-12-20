#include "node.hpp"

Node::Type const Node::types[] = {
	Node::Type::RegularNode,
	Node::Type::LadyBugFlower,
	Node::Type::AphidFlower,
	Node::Type::Flower,
	Node::Type::SemperFlower,
	Node::Type::None
};



bool Node::ID::operator<(Node::ID const& other) const
{
	return id.y > other.id.y || (id.y == other.id.y && id.x < other.id.x);
}

bool Node::ID::operator==(Node::ID const& other) const
{
	return id == other.id;
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape c(10);
	c.setOrigin(10, 10);
	if (m_t == Texture::ID::AphidFlower)
        c.setFillColor(sf::Color::Yellow);
    else if (m_t == Texture::ID::Flower)
        c.setFillColor(sf::Color::Magenta);
        else if (m_t == Texture::ID::LadyBugFlower)
        c.setFillColor(sf::Color::Blue);
    else
        c.setFillColor(sf::Color::Red);
	sf::Transform movement;
	movement.translate(m_pos);
	states.transform *= movement;
	target.draw(c, states);
}

Node::Type Node::nextType()
{
	int i = 0;
	auto t = types[0];
	while (getType() != t && t != Node::Type::None)
		t = types[++i];
	++i;
	if (types[i] == Node::Type::None)
		i = 0;
	t = types[i];
	
	setType(t);
	return t;

}
