#pragma once

#include <SFML/Graphics.hpp>
#include <IHM/widget.hpp>

namespace Orientation {
	enum Orientation {
		TOP,
		BOTTOM
	};
}

class DialogBox : public sf::Drawable
{
	public:
		
		
		DialogBox(const sf::Font& font, const sf::String& text = "");
		virtual ~DialogBox() = default;
		
		void setFont(const sf::Font& font);
		void setText(const sf::String& text);
		void setOrientation(Orientation::Orientation orientation);
		
		virtual void
		injectEvent (sf::Event event, const sf::Vector2f& mouse);
		
		void compute();
		
		void setPosition (float x, float y);
		void setPosition (const sf::Vector2f& position);
		
	protected:
		virtual void draw ( sf::RenderTarget& target, sf::RenderStates states ) const;
		
	private:
		sf::Text                 mText;
		Orientation::Orientation mOrientation;
		sf::Vector2f             mPosition;
		sf::RectangleShape       mBox;
		sf::ConvexShape          mArrow;
		
		float mArrowHeight = 20.f;
		float mArrowWidth  = 40.f;
		float mWidth       = 250.f;
		float mHeight      = 160.f;
		float mPadding     = 5.f;
};