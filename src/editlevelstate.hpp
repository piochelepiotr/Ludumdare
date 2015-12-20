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
	void onNodePressed(Node::ID node, sf::Mouse::Button button);
	void onNodeReleased(Node::ID node, sf::Mouse::Button button);
	void addNode(Node::ID node);
	void removeNode(Node::ID node);
	void addEdge(Node::ID n1, Node::ID);
	
	void save(std::string name);
	void load(std::string name);
	

	std::pair<bool, Node::ID> getNodeDragged()
	{ return std::make_pair(m_isNodeDragged, mFirstNode); }
	
	Texture::ID nextType(Texture::ID type);

    private:
	void mousePressed(sf::Event event, sf::Vector2f pos);
	void mouseReleased(sf::Event event, sf::Vector2f pos);
	void updateAnchors();
	
	Graph mGraph;
	AnchorPool mAnchors;
	std::map<Node::ID, NodeAnchorListener*> mNodeToAnchors;

	bool m_isNodeDragged;
	Node::ID mFirstNode;
};
