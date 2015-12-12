#include <IHM/textbutton.hpp>

TextButton::TextButton (sf::Font& font, TextButton::TriggerFun callback) : 
	mText("button",font),
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
TextButton::render (sf::RenderTarget& target, sf::RenderStates states) const {
	auto box = sf::RectangleShape({getArea().width, getArea().height});
	box.setPosition(getPosition());
	box.setFillColor(sf::Color::White);
	target.draw(box);
	target.draw(mText, states);
}

void
TextButton::event (sf::Event e) {
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code = sf::Keyboard::Return)
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

const sf::String&
TextButton::getText() const {
	return mText.getString();
}

void
TextButton::computeArea() {
	mArea = mText.getGlobalBounds();
}
