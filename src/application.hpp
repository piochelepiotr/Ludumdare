#pragma once
#include "statestack.hpp"

class Application
{
    public:
        Application(State::Context context);
        void registerStates();
        void processInput();
        void update(sf::Time dt);
        void render();
        int run();
    private:
        StateStack mStateStack;
        sf::RenderWindow* mWindow;
};
