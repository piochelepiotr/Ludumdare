#pragma once
#include "state.hpp"

#include <IHM/textbutton.hpp>
#include <IHM/verticalmenu.hpp>
#include <IHM/focusgroup.hpp>

class TitleState : public State
{
    public:
        TitleState(StateStack& mystack, StateContext context);
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
		
		void play();
		void quit();
		void editor();
		
        sf::Sprite mBackgroundSprite;
        sf::Text mText;
        bool mShowText;
        sf::Time mTextEffectTime;

		VerticalMenu mVerticalMenu;
		FocusGroup   mFocusGroup;
		TextButton   mPlayButton;
		TextButton   mSettingsButton;
		TextButton   mQuitButton;
		TextButton   mLevelEditorButton;
};
