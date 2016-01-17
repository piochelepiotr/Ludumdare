#include <IHM/textbutton.hpp>

TextButton::TextButton (sf::Font& font, TextButton::TriggerFun callback) : 
	TextButton("button",font, callback)
{
}

TextButton::TextButton (const sf::String& text, sf::Font& font, TextButton::TriggerFun callback) : 
	mText(text, font),
	mCallback(callback)
{
		mStyleNormal = {sf::Color::White, &font, 18};
		mStyleFocus  = {sf::Color::Red, &font, 18};
		setStyle(mStyleNormal);
		
		mStyleType = TextButtonStyle::Normal;
}

TextButton::TextButton(const sf::String& text, TextButtonStyle normal, TextButtonStyle focus, TriggerFun callback) :
	mText(),
	mCallback(callback),
	mStyleNormal(normal),
	mStyleFocus(focus)
{
	setStyle(mStyleNormal);
}


void
TextButton::update (sf::Time t) {
	// DO NOTHING
}

void
TextButton::render (sf::RenderTarget& target, sf::RenderStates states) const {
	auto box = sf::RectangleShape({getArea().width, getArea().height});
	box.setPosition(getPosition());
	box.setFillColor(sf::Color::White);
	//target.draw(box);
	target.draw(mText, states);
}

void
TextButton::event (sf::Event e) {
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Return)
		{
			mCallback();
		}
	}
}

bool 
TextButton::mouseEvent(sf::Event e, sf::Vector2f local) {
	auto area = getArea();
	area.left += getPosition().x;
	area.top  += getPosition().y;
	
	if (e.type == sf::Event::MouseMoved) {
		if (area.contains(local)) {
			focus();
			return true;
		}
	}
	else if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
		if (area.contains(local)) {
			mCallback();
			return true;
		}
	}
	return false;
}


sf::FloatRect
TextButton::getArea() const {
	return mArea;
}

void
TextButton::setText(const sf::String& text) {
	mText.setString(text);
	computeArea();
	notify();
}

const sf::String&
TextButton::getText() const {
	return mText.getString();
}

void
TextButton::computeArea() {
	mArea = mText.getGlobalBounds();
}

void
TextButton::enableFocus ()
{
	mStyleType = TextButtonStyle::Focus;
	setStyle(mStyleFocus);
}

void
TextButton::disableFocus()
{
	mStyleType = TextButtonStyle::Normal;
	setStyle(mStyleNormal);
}

void TextButton::setStyle(TextButtonStyle style)
{
	mText.setColor(style.color);
	if(style.font)
		mText.setFont(*style.font);
	mText.setCharacterSize(style.char_size);
	computeArea();
	notify();
}

void TextButton::defineStyle(TextButtonStyle::StyleType type, TextButtonStyle style)
{
	switch (type)
	{
		case TextButtonStyle::Focus:
			mStyleFocus = style; break;
		case TextButtonStyle::Normal:
			mStyleNormal = style; break;
		default: break;
	}
	if (mStyleType == type)
		setStyle(style);
}
