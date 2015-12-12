#include "application.hpp"
#include "titlestate.hpp"
#include "gamestate.hpp"
#include <iostream>

Application::Application(State::Context context)
: mStateStack(context)
, mWindow(context.window)
{
    registerStates();
    mStateStack.pushState(States::Title);
    sf::Event event;
    mStateStack.handleEvent(event);
}

void Application::registerStates()
{
    mStateStack.registerState<TitleState>(States::Title);
    //mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    //mStateStack.registerState<PauseState>(States::Pause);
    //mStateStack.registerState<SpeechState>(States::Speech);
}

void Application::processInput()
{
    sf::Event event;
    while(mWindow->pollEvent(event))
    {
        mStateStack.handleEvent(event);
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::render()
{
    mStateStack.draw();
}

int Application::run()
{
    sf::Clock clock;
    sf::Time dt=clock.restart();
    while(!mStateStack.isEmpty())
    {
        dt = clock.restart();
        processInput();
        update(dt);
        render();
    }
    mWindow->close();
    return 0;
}
