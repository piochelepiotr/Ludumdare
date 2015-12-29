#pragma once
#include "editor/anchoractionlistener.hpp"
//#include "graph/node.hpp"
#include "id.hpp"
#include "rosetree/flower.hpp"

class GameState;

class NodeAnchor : public AnchorActionListener
{
	public:
	NodeAnchor(GameState& gamestate, ID<Flower> node, sf::Vector2f position);
	
	void onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f& position) override;
	void onMouseDragged(sf::Mouse::Button button, const sf::Vector2f& position) override;
	void onMouseButtonReleased(sf::Mouse::Button button, const sf::Vector2f& position) override;
	void onMouseEnter() override;
	void onMouseLeft() override;
	sf::Vector2f getPosition() override;


	private:
	GameState& m_gameState;
	ID<Flower> m_flower;
	sf::Vector2f m_position;
};
