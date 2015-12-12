#pragma once
#include "state.hpp"

class GameState : public State
{
    public:
        GameState(StateStack& mystack, Context context);
        virtual ~GameState();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
        void handlePlayerInput(sf::Keyboard::Key , bool);
	
    private:
	
};
