#pragma once
#include "state/state.hpp"

#include <IHM/textbutton.hpp>
#include <IHM/verticalmenu.hpp>
#include <IHM/focusgroup.hpp>

class TitleState : public State
{
    public:
        TitleState(StateStack& mystack, StateContext context);
        void draw() override;
        bool update(sf::Time dt) override;
        bool handleEvent(const sf::Event& event) override;
    private:
		
		void play();
		void quit();
		void editor();
		
        sf::Sprite mBackgroundSprite;
        //sf::Text mText;
        //bool mShowText;
        //sf::Time mTextEffectTime;

		VerticalMenu mVerticalMenu;
		FocusGroup   mFocusGroup;
		TextButton   mPlayButton;
		TextButton   mSettingsButton;
		TextButton   mQuitButton;
		TextButton   mLevelEditorButton;
};
