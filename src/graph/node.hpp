#pragma once
#include <SFML/Graphics.hpp>

class Node
{
	public:
	inline Node(sf::Vector2f v) : m_pos(v) {}
	inline Node(float x, float y) : m_pos(x, y) {}
	bool operator<(Node const& other) const;
	inline sf::Vector2f const& getPosition() const { return m_pos; }
	inline sf::Vector2f& getPosition() { return m_pos; }
	private:
	sf::Vector2f m_pos;
};
