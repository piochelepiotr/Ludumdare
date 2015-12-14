#pragma once
#include "state.hpp"
#include "gameworld.hpp"
#include "dialogbox.hpp"
#include "graph/graph.hpp"
#include <IHM/dialogbutton.hpp>


#include "editor/anchorpool.hpp"
#include "gamestateanchorlistener.hpp"


class GameState : public State
{
    public:
        GameState(StateStack& mystack, Context context);
        virtual ~GameState();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
        void handlePlayerInput(sf::Keyboard::Key , bool);

		void addNode(Node::ID node);
		void addEdge(Node::ID n1, Node::ID n2);

		void onNodePressed(Node::ID node);
		void onNodeReleased(Node::ID node);

        void updateAnchors();


//		void finDeUnivers();
	private:
		GameWorld mGameWorld;
		Graph mGraph;

		AnchorPool mAnchors;
		Node::ID mDraggedNode;
		bool mIsDragged;

};
