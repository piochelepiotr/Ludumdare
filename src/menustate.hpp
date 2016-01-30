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
        void draw() override;
        bool update(sf::Time dt) override;
        bool handleEvent(const sf::Event& event) override;
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
