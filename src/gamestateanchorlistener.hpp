#pragma once
#include "editor/anchoractionlistener.hpp"
#include "graph/node.hpp"

class GameState;

class NodeAnchor : public AnchorActionListener
{
	public:
	NodeAnchor(GameState& gamestate, Node::ID node);
	
	void onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f& position) override;
	void onMouseDragged(sf::Mouse::Button button, const sf::Vector2f& position) override;
	void onMouseButtonReleased(sf::Mouse::Button button, const sf::Vector2f& position) override;
	void onMouseEnter() override;
	void onMouseLeft() override;
	sf::Vector2f getPosition() override;


	private:
	GameState& m_gameState;
	Node::ID m_node;
};
