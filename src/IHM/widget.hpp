#pragma once

#include <SFML/Graphics.hpp>

/// @brief : base class for widget with conveniance function for alignment purpose
class Widget : public sf::Drawable
{
	public:
		/// @brief updates the button state
		virtual void 
		update (sf::Time t)=0;

		/// @brief reacts to mouse/keyboard event
		virtual void 
		event (sf::Event e);

		/// @brief return the area covered by the widget
		virtual sf::FloatRect
		getArea () const=0;

		/// @brief return the shift required by the widget
		virtual sf::Vector2f
		getShift() const { return {0,0}; }

	protected:
		/// @brief Render button
		virtual void
		render (sf::RenderTarget& target, sf::RenderState state) const=0;
}

