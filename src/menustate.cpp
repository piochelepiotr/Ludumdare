#include <menustate.hpp>
#include <iostream>
#include <functional>

MenuState::MenuState(StateStack& mystack, Context context)
: State(mystack, context)
, mVerticalMenu()
, mFocusGroup()
, mResumeButton("Resume", context.fonts->get(Font::Text), std::bind(&MenuState::resume, this))
, mMainScreenButton("Go to main screen", context.fonts->get(Font::Text), std::bind(&MenuState::main_screen, this))
, mSaveButton("Save game", context.fonts->get(Font::Text), std::bind(&MenuState::save, this))
, mQuitButton("Quit", context.fonts->get(Font::Text), std::bind(&MenuState::quit, this))
{ 
	TextButtonStyle normal;
	normal.color = sf::Color::White;
	normal.font = &context.fonts->get(Font::Text);
	normal.char_size = 100;
	
	TextButtonStyle focus;
	focus.color = sf::Color::Red;
	focus.font = &context.fonts->get(Font::Text);
	focus.char_size = 120;
	
	mResumeButton.defineStyle(TextButtonStyle::Normal, normal);
	mResumeButton.defineStyle(TextButtonStyle::Focus, focus);
	mMainScreenButton.defineStyle(TextButtonStyle::Normal, normal);
	mMainScreenButton.defineStyle(TextButtonStyle::Focus, focus);
	mSaveButton.defineStyle(TextButtonStyle::Normal, normal);
	mSaveButton.defineStyle(TextButtonStyle::Focus, focus);
	mQuitButton.defineStyle(TextButtonStyle::Normal, normal);
	mQuitButton.defineStyle(TextButtonStyle::Focus, focus);
	
	mVerticalMenu.setHorizontalAlignment(VerticalMenu::CENTER);
	mVerticalMenu.append(mResumeButton);
	mVerticalMenu.append(mMainScreenButton);
	mVerticalMenu.append(mSaveButton);
	mVerticalMenu.append(mQuitButton);
	
	float width = context.window->getSize().x;
	mVerticalMenu.setWidth(width/2);
	sf::Vector2f position = {width/4, context.window->getSize().y / 3.f};
	mVerticalMenu.setPosition(position);

	mResumeButton.setFocusGroup(&mFocusGroup);
	mMainScreenButton.setFocusGroup(&mFocusGroup);
	mSaveButton.setFocusGroup(&mFocusGroup);
	mQuitButton.setFocusGroup(&mFocusGroup);
}

bool MenuState::handleEvent(const sf::Event& event)
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

bool MenuState::update(sf::Time dt)
{

    return true;
}

void MenuState::draw()
{
        //mContext.window->draw(mText);
	mContext.window->draw(mResumeButton);
	mContext.window->draw(mMainScreenButton);
	mContext.window->draw(mSaveButton);
	mContext.window->draw(mQuitButton);
}

void MenuState::resume()
{
	requestStackPop();
}

void MenuState::quit()
{
	requestStackClear();
}

void MenuState::main_screen()
{
	requestStackClear();
	requestStackPush(States::Title);
}

void MenuState::save()
{
	//FIXME
}
