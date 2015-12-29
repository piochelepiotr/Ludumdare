#pragma once
#include "state.hpp"
#include "gameworld.hpp"
#include "dialogbox.hpp"
//#include "graph/graph.hpp"
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

		void addFlower(sf::Vector2f position, Flower::Type type);
		void addBranch(ID<Flower> f1, ID<Flower> f2);

		void onFlowerPressed(ID<Flower> flower);
		void onFlowerReleased(ID<Flower> flower);

        void updateAnchors();

	private:
		GameWorld mGameWorld;
		RoseTree mRoseTree;

		AnchorPool mAnchors;
		ID<Flower> mDraggedFlower;
		bool mIsDragged;

};
