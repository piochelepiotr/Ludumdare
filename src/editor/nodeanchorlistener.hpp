#pragma once
#include "editor/anchoractionlistener.hpp"
#include "graph/node.hpp"

class EditLevelState;

class NodeAnchorListener : public AnchorActionListener {
    public:
	NodeAnchorListener(EditLevelState& editLevelState, Node::ID node);
	
	void 
	onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f& position) override;
	
	void
	onMouseDragged(sf::Mouse::Button button, const sf::Vector2f& position) override;
	
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
	Node::ID m_node;
};
