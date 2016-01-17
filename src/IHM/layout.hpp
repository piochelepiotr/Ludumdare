#pragma once

#include <SFML/System/Vector2.hpp>

class Widget;

class Layout 
{

	protected:

		/// @brief update the widget size and alignment
		virtual void
		recompute()=0;

		virtual void
		setWidgetPosition(Widget& widget, const sf::Vector2f& position); 
};

