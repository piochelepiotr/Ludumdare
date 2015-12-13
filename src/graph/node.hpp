#pragma once
#include <SFML/Graphics.hpp>
#include "textureholder.hpp"

class Node
{
	public:
		typedef Texture::ID Type;
		struct ID
		{
			ID(sf::Vector2f v) : id(v) {};
			ID(Node n) : id(n.getPosition()) {};
			ID(float x, float y) : id(x, y) {};
			bool operator<(Node::ID const& other) const;
			bool operator==(Node::ID const& other) const;
			sf::Vector2f id;
			Type type;
		};

		bool operator<(Node const& other) const
		{ return Node::ID(*this) < Node::ID(other); }
		bool operator==(Node const& other) const
		{ return Node::ID(*this) < Node::ID(other); }

		inline Node(Node::ID id) : m_pos(id.id), m_t(id.type) {}

		inline sf::Vector2f const& getPosition() const { return m_pos; }
		inline sf::Vector2f& getPosition() { return m_pos; }

		Type getType();

	private:
		sf::Vector2f m_pos;
		Type m_t;
};
