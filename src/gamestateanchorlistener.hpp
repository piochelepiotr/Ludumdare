#pragma once
#include "anchor/anchoractionlistener.hpp"
#include "id.hpp"

// TODO Ressemble vraiment beaucoup à NodeAnchorListener (pour l’éditeur)…
// Il faudrait peut-être les fusionner

class Flower;
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
