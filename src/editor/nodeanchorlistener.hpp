#pragma once
#include "graph/graph.hpp"
#include "editor/anchoractionlistener.hpp"

class NodeAnchorListener : public AnchorActionListener {
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


	private:
	Graph& m_graph;
	Node::ID m_node;
};
