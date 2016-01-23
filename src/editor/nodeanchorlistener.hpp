#pragma once
#include "anchor/anchoractionlistener.hpp"
#include "id.hpp"

// TODO Il faudrait renommer ça pour que ça ait plus un rapport avec editor…
class Flower;
class EditLevelState;

class NodeAnchorListener : public AnchorActionListener {
    public:
	NodeAnchorListener(EditLevelState& editLevelState, ID<Flower> flower, sf::Vector2f position);
	
	void 
	onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f& position) override;
	
	/*
	void
	onMouseDragged(sf::Mouse::Button button, const sf::Vector2f& position) override;
	*/
	
	void
	onMouseButtonReleased(sf::Mouse::Button button, const sf::Vector2f& position) override;
	
	void
	onMouseEnter() override;
	
	void
	onMouseLeft() override;

	sf::Vector2f
	getPosition() override;


	private:
	EditLevelState& m_editLevelState;
	ID<Flower> m_flower;
	sf::Vector2f m_position;
};
