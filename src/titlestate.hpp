#pragma once
#include <SFML/Graphics.hpp>
#include "state.hpp"

#include <IHM/textbutton.hpp>
#include <IHM/verticalmenu.hpp>

class TitleState : public State
{
    public:
        TitleState(StateStack& mystack, Context context);
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
