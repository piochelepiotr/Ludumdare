#include "titlestate.hpp"
#include <iostream>
#include <functional>

TitleState::TitleState(StateStack& mystack, Context context)
: State(mystack, context)
, mBackgroundSprite()
, mText()
, mShowText(true)
, mTextEffectTime()
, mVerticalMenu({0.f,300.f}, 800)
, mPlayButton("Play", context.fonts->get(Font::Text), std::bind(&TitleState::play, this))
, mQuitButton("Quit", context.fonts->get(Font::Text), std::bind(&TitleState::quit, this))
{ 
    mText.setFont(mContext.fonts->get(Font::Text));
    mText.setPosition(250.,300.);
    mText.setString("press any button");

	mVerticalMenu.setHorizontalAlignment(VerticalMenu::CENTER);
	mVerticalMenu.append(mPlayButton);
	mVerticalMenu.append(mQuitButton);

	mFocusGroup.append(mPlayButton);
	mFocusGroup.append(mQuitButton);
}

bool TitleState::handleEvent(const sf::Event& event)
{
	
    if (event.type == sf::Event::KeyPressed)
    {
        /*requestStackPop();
        requestStackPush(States::Game);*/
		if (event.key.code == sf::Keyboard::Down) {
			mFocusGroup.next();
		}
		else if (event.key.code == sf::Keyboard::Up) {
			mFocusGroup.previous();
		}

		if (mFocusGroup.current())
			mFocusGroup.current()->event(event);
    }
	
    return true;
}

bool TitleState::update(sf::Time dt)
{
    mTextEffectTime += dt;

	// blinking text effect
    if (mTextEffectTime >= sf::seconds(0.7f))
    {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }
    return true;
}

void TitleState::draw()
{
    mContext.window->clear();
    mContext.window->draw(mBackgroundSprite);
    //if (mShowText)
        //mContext.window->draw(mText);
	mContext.window->draw(mPlayButton);
	mContext.window->draw(mQuitButton);
    mContext.window->display();
}

void TitleState::play()
{
	requestStateClear();
	requestStackPush(States::Game);
}

void TitleState::quit()
{
	requestStackPop();
}

