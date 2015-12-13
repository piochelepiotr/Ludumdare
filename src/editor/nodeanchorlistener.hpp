#pragma once

class NodeAnchorListener : public NodeAnchorListener {
    public:
	NodeAnchorListener(Graph& graph, Node::ID node);
	
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
};