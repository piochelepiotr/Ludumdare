#pragma once
#include <SFML/Graphics.hpp>
#include "../textureholder.hpp"

class Node
{
	public:
		typedef Texture::ID Type;
		struct ID
		{
			ID(sf::Vector2f v) : id(v), type(Node::Type::RegularNode) {};
			ID(Node n) : id(n.getPosition()), type(n.getType()) {};
			ID(float x, float y) : id(x, y), type(Node::Type::RegularNode) {};
			bool operator<(Node::ID const& other) const;
			bool operator==(Node::ID const& other) const;
			bool operator!=(Node::ID const& other) const
			{ return !(*this == other); }
			sf::Vector2f id;
			Type type;
		};

		bool operator<(Node const& other) const
		{ return Node::ID(*this) < Node::ID(other); }
		bool operator==(Node const& other) const
		{ return Node::ID(*this) == Node::ID(other); }
		bool operator!=(Node const& other) const
		{ return Node::ID(*this) != Node::ID(other); }

		inline Node(Node::ID id) : m_pos(id.id), m_t(id.type) {}

		inline sf::Vector2f const& getPosition() const { return m_pos; }
		inline sf::Vector2f& getPosition() { return m_pos; }

		Type getType();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	protected:
		sf::Vector2f m_pos;
	public:
        Type m_t;
	protected:
		sf::Vector2f m_derivee;
};
