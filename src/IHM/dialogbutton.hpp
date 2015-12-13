#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

class DialogButton : public sf::Drawable
{
	public:
		using TriggerFun = std::function<void()>;
		
		DialogButton(sf::Font& font, TriggerFun callback=[]{});
		DialogButton(sf::Font& font, const sf::String& text, TriggerFun callback=[]{});
	
		void setText(const sf::String& text);
		
	protected:
		virtual void draw ( sf::RenderTarget& target, sf::RenderStates states ) const;
		
	private:
		sf::Text mText;
		sf::RectangleShape mBox;
		sf::Vector2f mPosition;
		sf::Vector2f mSize;
		
};