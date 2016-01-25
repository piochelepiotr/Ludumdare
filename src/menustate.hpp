#pragma once
#include "state/state.hpp"

#include <IHM/textbutton.hpp>
#include <IHM/verticalmenu.hpp>
#include <IHM/selectorwidget.hpp>
#include <IHM/focusgroup.hpp>

class MenuState : public State
{
    public:
        MenuState (StateStack& mystack, StateContext context);
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
		
		void resume();
		void main_screen();
		void setSoundState(int);
		void quit();

		VerticalMenu     mVerticalMenu;
		FocusGroup       mFocusGroup;
		TextButton       mResumeButton;
		TextButton       mMainScreenButton;
		SelectorWidget   mSoundButton;
		TextButton       mQuitButton;
};
