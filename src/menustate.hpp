#pragma once
#include <SFML/Graphics.hpp>
#include "state.hpp"

#include <IHM/textbutton.hpp>
#include <IHM/verticalmenu.hpp>

class MenuState : public State
{
    public:
        MenuState (StateStack& mystack, Context context);
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
		
		void resume();
		void main_screen();
		void save();
		void quit();

		VerticalMenu mVerticalMenu;
		FocusGroup   mFocusGroup;
		TextButton   mResumeButton;
		TextButton   mMainScreenButton;
		TextButton   mSaveButton;
		TextButton   mQuitButton;
};
