#include "titlestate.hpp"
#include <iostream>
#include <functional>

TitleState::TitleState(StateStack& mystack, Context context)
: State(mystack, context)
, mBackgroundSprite()
, mText()
, mShowText(true)
, mTextEffectTime()
, mVerticalMenu()
, mFocusGroup()
, mPlayButton("Play", context.fonts->get(Font::Text), std::bind(&TitleState::play, this))
, mSettingButton("Setting", context.fonts->get(Font::Text), []{})
, mQuitButton("Quit", context.fonts->get(Font::Text), std::bind(&TitleState::quit, this))

{ 
	TextButtonStyle normal;
	normal.color = sf::Color::White;
	normal.font = &context.fonts->get(Font::Text);
	normal.char_size = 180;
	
	TextButtonStyle focus;
	focus.color = sf::Color::Red;
	focus.font = &context.fonts->get(Font::Text);
	focus.char_size = 200;
	
	mPlayButton.defineStyle(TextButtonStyle::Normal, normal);
	mPlayButton.defineStyle(TextButtonStyle::Focus, focus);
	mQuitButton.defineStyle(TextButtonStyle::Normal, normal);
	mQuitButton.defineStyle(TextButtonStyle::Focus, focus);
	mSettingButton.defineStyle(TextButtonStyle::Normal, normal);
	mSettingButton.defineStyle(TextButtonStyle::Focus, focus);
	
	mVerticalMenu.setHorizontalAlignment(VerticalMenu::CENTER);
	mVerticalMenu.append(mPlayButton);
	mVerticalMenu.append(mSettingButton);
	mVerticalMenu.append(mQuitButton);
	
	float width = context.window->getSize().x;
	mVerticalMenu.setWidth(width/2);
	sf::Vector2f position = {width/2, context.window->getSize().y / 3.f};
	mVerticalMenu.setPosition(position);

	mPlayButton.setFocusGroup(&mFocusGroup);
	mSettingButton.setFocusGroup(&mFocusGroup);
	mQuitButton.setFocusGroup(&mFocusGroup);
}

bool TitleState::handleEvent(const sf::Event& event)
{
	
    if (event.type == sf::Event::KeyPressed)
    {
		if (event.key.code == sf::Keyboard::Down) {
			mFocusGroup.next();
		}
		else if (event.key.code == sf::Keyboard::Up) {
			mFocusGroup.previous();
		}

		if (mFocusGroup.current())
			mFocusGroup.current()->event(event);
    }
    else if (
		event.type == sf::Event::MouseButtonPressed
		|| event.type == sf::Event::MouseButtonReleased
		|| event.type == sf::Event::MouseMoved
	){
		auto w = getContext().window;
		return mFocusGroup.mouseEvent(event, 
			w->mapPixelToCoords(sf::Mouse::getPosition(*w))
		);
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
	mContext.window->draw(mSettingButton);
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

