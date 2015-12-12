#include "titlestate.hpp"

TitleState::TitleState(StateStack& mystack, Context context)
: State(mystack, context)
, mBackgroundSprite()
, mText()
, mShowText(true)
, mTextEffectTime()
{
    mContext.fonts->load(Font::Text, "font/text.ttf");
    mText.setFont(mContext.fonts->get(Font::Text));
    mText.setPosition(250.,300.);
    mText.setString("press any button");
}

bool TitleState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Game);
    }
    return true;
}

bool TitleState::update(sf::Time dt)
{
    mTextEffectTime += dt;
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
    //mContext.window->draw(mBackgroundSprite);
    if (mShowText)
        mContext.window->draw(mText);
    mContext.window->display();
}
