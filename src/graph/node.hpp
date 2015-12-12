#pragma once
#include <SFML/Graphics.hpp>

class Node
{
	public:
	typedef Texture::ID Type;
	inline Node(sf::Vector2f v) : m_pos(v), m_t(RegularNode) {}
	inline Node(float x, float y) : m_pos(x, y), m_t(RegularNode) {}
	bool operator<(Node const& other) const;
	bool operator==(Node const& other) const;
	inline sf::Vector2f const& getPosition() const { return m_pos; }
	inline sf::Vector2f& getPosition() { return m_pos; }

	private:
	sf::Vector2f m_pos;
	Type m_t;
};
