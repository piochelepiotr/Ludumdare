#pragma once
#include "state.hpp"
#include "gameworld.hpp"
#include "editor/anchorpool.hpp"


class GameState : public State
{
    public:
        GameState(StateStack& mystack, StateContext context);
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
		AnchorPool mAnchors;
		ID<Flower> mDraggedFlower;
		bool mIsDragged;

};
