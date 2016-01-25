#include "menustate.hpp"
#include "font.hpp"


using namespace std::placeholders;

MenuState::MenuState(StateStack& mystack, StateContext context)
: State(mystack, context)
, mVerticalMenu()
, mFocusGroup()
, mResumeButton("Resume", context.fonts->get(Font::Text), std::bind(&MenuState::resume, this))
, mMainScreenButton("Go to main screen", context.fonts->get(Font::Text), std::bind(&MenuState::main_screen, this))
, mSoundButton(context.fonts->get(Font::Text), [this](int x) { setSoundState(x);})
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
	//mSoundButton.defineStyle(TextButtonStyle::Normal, normal);
	//mSoundButton.defineStyle(TextButtonStyle::Focus, focus);
	mQuitButton.defineStyle(TextButtonStyle::Normal, normal);
	mQuitButton.defineStyle(TextButtonStyle::Focus, focus);
	
	mSoundButton.addEntry(1, "Sound ON");
	mSoundButton.addEntry(0, "Sound OFF");
	
	mVerticalMenu.setHorizontalAlignment(VerticalMenu::CENTER);
	mVerticalMenu.append(mResumeButton);
	mVerticalMenu.append(mMainScreenButton);
	mVerticalMenu.append(mSoundButton);
	mVerticalMenu.append(mQuitButton);
	
	float width = context.window->getSize().x;
	mVerticalMenu.setWidth(width/2);
	sf::Vector2f position = {width/4, context.window->getSize().y / 3.f};
	mVerticalMenu.setPosition(position);

	mResumeButton.setFocusGroup(&mFocusGroup);
	mMainScreenButton.setFocusGroup(&mFocusGroup);
	mSoundButton.setFocusGroup(&mFocusGroup);
	mQuitButton.setFocusGroup(&mFocusGroup);
}

bool MenuState::handleEvent(const sf::Event& event)
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
				case sf::Keyboard::Escape:
					resume();
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

bool MenuState::update(sf::Time dt)
{
	return false;
}

void MenuState::draw()
{
	sf::Vector2f size = mContext.window->getView().getSize();
	sf::RectangleShape background (size);
	background.setFillColor(sf::Color(0,0,0,175));
	mContext.window->draw(background);
	//mContext.window->draw(mText);
	mContext.window->draw(mResumeButton);
	mContext.window->draw(mMainScreenButton);
	mContext.window->draw(mSoundButton);
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

void MenuState::setSoundState(int state)
{

}
