#pragma once
#include <map>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "cpp_std_11.hpp"
#include "player.hpp"
#include "textureholder.hpp"
#include "font.hpp"

class StateStack;

namespace States
{
    enum ID { Title, Menu, Pause, Game, Speech };
}

class State
{
    public:
        typedef std::unique_ptr<State> Ptr;
        struct Context
        {
            Context(sf::RenderWindow& win, TextureHolder& textu, FontHolder& fon, Player& myplayer)
            {
                window = &win;
                textures = &textu;
                fonts = &fon;
                player = &myplayer;
            }
            sf::RenderWindow* window;
            TextureHolder* textures;
            FontHolder* fonts;
            Player* player;
        };
    public:
        State(StateStack& mystack, Context context);
        virtual ~State();
        virtual void draw() = 0;
        virtual bool update(sf::Time dt) = 0;
        virtual bool handleEvent(const sf::Event& event) = 0;
    protected:
        void requestStackPush(States::ID stateID);
        void requestStackPop();
        void requestStateClear();
        Context getContext() const;
    protected:
        StateStack* mStack;
        Context mContext;
};
