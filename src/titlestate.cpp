#include "titlestate.hpp"
#include "font.hpp"

TitleState::TitleState(StateStack& mystack, StateContext context)
: State(mystack, context)
, mBackgroundSprite()
//, mText()
//, mShowText(true)
//, mTextEffectTime()
, mVerticalMenu()
, mFocusGroup()
, mPlayButton("Play", context.fonts->get(Font::Text), std::bind(&TitleState::play, this))
, mSettingsButton("Settings", context.fonts->get(Font::Text), []{})
, mQuitButton("Quit", context.fonts->get(Font::Text), std::bind(&TitleState::quit, this))
,mLevelEditorButton("Level editor", context.fonts->get(Font::Text), std::bind(&TitleState::editor, this))

{
	TextButtonStyle normal;
	normal.color = sf::Color::White;
	normal.font = &context.fonts->get(Font::Text);
	normal.char_size = 150;
	
	TextButtonStyle focus;
	focus.color = sf::Color::Red;
	focus.font = &context.fonts->get(Font::Text);
	focus.char_size = 170;
	
	mPlayButton.defineStyle(TextButtonStyle::Normal, normal);
	mPlayButton.defineStyle(TextButtonStyle::Focus, focus);
	mQuitButton.defineStyle(TextButtonStyle::Normal, normal);
	mQuitButton.defineStyle(TextButtonStyle::Focus, focus);
	mSettingsButton.defineStyle(TextButtonStyle::Normal, normal);
	mSettingsButton.defineStyle(TextButtonStyle::Focus, focus);
	mLevelEditorButton.defineStyle(TextButtonStyle::Normal, normal);
	mLevelEditorButton.defineStyle(TextButtonStyle::Focus, focus);
	
	mVerticalMenu.setHorizontalAlignment(VerticalMenu::CENTER);
	mVerticalMenu.append(mPlayButton);
	mVerticalMenu.append(mSettingsButton);
	mVerticalMenu.append(mQuitButton);
	mVerticalMenu.append(mLevelEditorButton);
	
	float width = context.window->getSize().x;
	mVerticalMenu.setWidth(width/2);
	sf::Vector2f position = {width/2, context.window->getSize().y / 3.f};
	mVerticalMenu.setPosition(position);

	mPlayButton.setFocusGroup(&mFocusGroup);
	mSettingsButton.setFocusGroup(&mFocusGroup);
	mQuitButton.setFocusGroup(&mFocusGroup);
	mLevelEditorButton.setFocusGroup(&mFocusGroup);
}

bool TitleState::handleEvent(const sf::Event& event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Down:
					mFocusGroup.next();
					return true;
				case sf::Keyboard::Up:
					mFocusGroup.previous();
					return true;
				default:
					if (mFocusGroup.current())
						return mFocusGroup.current()->event(event);
					break;
			}
			break;

		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
		case sf::Event::MouseMoved:
			mFocusGroup.mouseEvent(event, getMousePos());
			return true;

		default:
			break;
	}
	return false;
}

bool TitleState::update(sf::Time dt)
{
	/*
    mTextEffectTime += dt;

	// blinking text effect
    if (mTextEffectTime >= sf::seconds(0.7f))
    {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }
	*/
    return true;
}

void TitleState::draw()
{
    mContext.window->draw(mBackgroundSprite);
    //if (mShowText)
        //mContext.window->draw(mText);
	mContext.window->draw(mPlayButton);
	mContext.window->draw(mSettingsButton);
	mContext.window->draw(mQuitButton);
	mContext.window->draw(mLevelEditorButton);
}

void TitleState::play()
{
    requestStackClear();
    requestStackPush(States::Game);
}

void TitleState::quit()
{
    requestStackPop();
}

void TitleState::editor()
{
    requestStackClear();
    requestStackPush(States::Editor);
}
