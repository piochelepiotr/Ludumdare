#pragma once

#include <SFML/Graphics.hpp>
#include <IHM/widget.hpp>

class TextButton : public Widget {
	public:
		TextButton (sf::Font& font);

		TextButton (const sf::String& text, sf::Font& font);

		/// @brief updates the button state
		void 
		update (sf::Time t) override;

		/// @brief reacts to mouse/keyboard event
		void 
		event (sf::Event e) override;

		/// @brief return the area covered by the widget
		sf::FloatRect
		getArea () const override;

		/// @brief return the shift required by the widget
		sf::Vector2f
		getShift const override;

		void 
		setText(const sf::String& text);

		sf::String& 
		getText() const;

	protected:
		/// @brief Render button
		void
		render (sf::RenderTarget& target, sf::RenderState state) const override;

	private:
		sf::Text	mText;

};

