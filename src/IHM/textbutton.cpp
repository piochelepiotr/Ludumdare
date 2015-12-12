#include <IHM/textbutton.hpp>

TextButton::TextButton (sf::Font& font, TextButton::TriggerFun callback) : 
	mText(font),
	mCallback(callback){
	computeArea();
}

TextButton::TextButton (const sf::String& text, sf::Font& font, TextButton::TriggerFun callback) : 
	mText(text, font),
	mCallback(callback){
	computeArea();
}

void
TextButton::update (sf::Time t) {
	// DO NOTHING
}

void
TextButton::event (sf::Event e) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code = sf::Keyboard::Enter)
		{
			mCallback();
		}
	}
}

sf::FloatRect
TextButton::getArea() const {
	return mArea;
}

void
TextButton::setText(const sf::String& text) {
	mText.setString(text);
	computeArea();
}

sf::String&
TextButton::getText() const {
	return mText.getString();
}

void
TextButton::computeArea() {
	mArea = mText.getGlobalBounds();
}
