#include <dialogbox.hpp>

DialogBox::DialogBox ( const sf::Font& font, const sf::String& text )
{
	mText.setString(text);
	mText.setFont(font);
	compute();
}

void DialogBox::setFont ( const sf::Font& font )
{
	mText.setFont(font);
}

void DialogBox::setText ( const sf::String& text )
{
	mText.setString(text);
}

void DialogBox::draw ( sf::RenderTarget& target, sf::RenderStates states ) const
{
	states.transform.translate(mPosition);
	target.draw(mBox, states);
	target.draw(mArrow, states);
	target.draw(mText, states);
}

void DialogBox::injectEvent ( sf::Event event, const sf::Vector2f& mouse )
{
	
}

void DialogBox::compute () {
	
	mBox = sf::RectangleShape({mWidth, mHeight}); // precalculée
	mBox.setPosition(-mWidth/2, mArrowHeight);
	mBox.setFillColor(sf::Color::Cyan);
	
	mArrow = sf::ConvexShape(3);
	mArrow.setPosition(0.f,0.f);
	mArrow.setFillColor(sf::Color::Red);
	mArrow.setPoint(0, sf::Vector2f {-mArrowWidth/2.f, mArrowHeight} );	
	mArrow.setPoint(1, sf::Vector2f {0.f,0.f} );
	mArrow.setPoint(2, sf::Vector2f {mArrowWidth/2.f, mArrowHeight} );	
	
	float w = mText.getLocalBounds().width;
	mText.setPosition(-w/2, mArrowHeight + mPadding);
}


void DialogBox::setOrientation ( Orientation::Orientation orientation )
{
	mOrientation = orientation;
}

void DialogBox::setPosition ( const sf::Vector2f& position )
{
	mPosition = position;
}
void DialogBox::setPosition ( float x, float y )
{
	setPosition({x,y});
}

