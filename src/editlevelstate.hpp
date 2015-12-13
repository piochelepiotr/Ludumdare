#pragma once

#include "state.hpp"
#include "graph/graph.hpp"

class EditLevelState : public State
{
    public:
        EditLevelState(StateStack& mystack, Context context);
        virtual ~EditLevelState();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
        void handlePlayerInput(sf::Keyboard::Key , bool);
    private:
	void mousePressed(sf::Vector2f pos);
	void mouseReleased(sf::Vector2f pos);
	Graph mGraph;
	Node::ID mFirstNode;
};