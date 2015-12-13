#pragma once

#include "state.hpp"
#include "graph/graph.hpp"
#include "editor/anchorpool.hpp"
#include "editor/nodeanchorlistener.hpp"

class EditLevelState : public State
{
    public:
        EditLevelState(StateStack& mystack, Context context);
        virtual ~EditLevelState();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
        void handlePlayerInput(sf::Keyboard::Key , bool);
	void onNodePressed(Node::ID node);
	void onNodeReleased(Node::ID node);
	void addNode(Node::ID node);
	void addEdge(Node::ID n1, Node::ID);

	std::pair<bool, Node::ID> getNodeDragged()
	{ return std::make_pair(m_isNodeDragged, mFirstNode); }

    private:
	void mousePressed(sf::Event event, sf::Vector2f pos);
	void mouseReleased(sf::Event event, sf::Vector2f pos);
	
	Graph mGraph;
	AnchorPool mAnchors;

	bool m_isNodeDragged;
	Node::ID mFirstNode;
};
