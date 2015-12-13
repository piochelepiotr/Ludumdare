#include <dialogbox.hpp>
#include <IHM/dialogbutton.hpp>

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
	if (!mIsVisible) return;
	auto s = states; //copy
	states.transform.translate(mPosition);
	
	target.draw(mBox, states);
	target.draw(mArrow, states);
	target.draw(mText, states);
	
	for(auto button : mButtons)
		target.draw(*button, s);
}

void DialogBox::injectEvent ( sf::Event event, const sf::Vector2f& mouse )
{
	if (!mIsVisible) return;
	switch (event.type) {
		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
			for(auto button : mButtons) {
				button->injectEvent(event, mouse);
			}
			break;
			
		default:
			break;
	}
}

void DialogBox::injectMouse (const sf::Vector2f& mouse) 
{
	if (!mIsVisible) return;
	for(auto button : mButtons)
		button->injectMouse(mouse);
}

void DialogBox::compute () {
	
	float minHeight = 0.f;
	float minWidth = 0.f;
	
	for(auto button : mButtons) {
		minWidth += button->getNeededSize().x;
		minWidth += mButtonMargin;
	}
	if (mButtons.size() >= 1)
		minWidth -= mButtonMargin;
	
	float h = 0.f;
	for (auto button : mButtons)
	{
		h = std::max(h, button->getNeededSize().y);
	}
	
	minHeight = h + mText.getLocalBounds().height + 4*mPadding;
	
	minWidth = std::max(mText.getLocalBounds().width+2*mPadding, minWidth);
	
	mBox = sf::RectangleShape({minWidth, minHeight}); // precalculée
	mBox.setPosition(-minWidth/2, mArrowHeight);
	mBox.setFillColor(sf::Color::Cyan);
	
	mArrow = sf::ConvexShape(3);
	mArrow.setPosition(0.f,0.f);
	mArrow.setFillColor(sf::Color::Cyan);
	mArrow.setPoint(0, sf::Vector2f {-mArrowWidth/2.f, mArrowHeight} );	
	mArrow.setPoint(1, sf::Vector2f {0.f,0.f} );
	mArrow.setPoint(2, sf::Vector2f {mArrowWidth/2.f, mArrowHeight} );	
	
	float w = mText.getLocalBounds().width;
	mText.setPosition(-w/2, mArrowHeight + mPadding);
	
	float y = mArrowHeight + 3* mPadding + mText.getLocalBounds().height;
	float x = -minWidth/2 + mPadding;
	

	auto p = getPosition();
	for(auto button : mButtons) {
		button->setPosition({x+p.x,y+p.y});
		button->setSize({(minWidth-mButtons.size()*mPadding)/ (mButtons.size()), h});
		x += mPadding + (minWidth- (mButtons.size()+1)*mPadding) /(mButtons.size());
	}
}


void DialogBox::setOrientation ( Orientation::Orientation orientation )
{
	mOrientation = orientation;
}

void DialogBox::setPosition ( const sf::Vector2f& position )
{
	mPosition = position;
	compute();
}
void DialogBox::setPosition ( float x, float y )
{
	setPosition({x,y});
}

sf::Vector2f DialogBox::getPosition() const
{
	return mPosition;
}


void DialogBox::addButton ( DialogButton& button )
{
	mButtons.push_back(&button);
	compute();
}

void DialogBox::removeButton ( DialogButton& button )
{
	auto it = std::find(mButtons.begin(), mButtons.end(), &button);
	if (it != mButtons.end())
	{
		mButtons.erase(it);
	}
	compute();
}

void DialogBox::close()
{
	mIsVisible = false;
}

