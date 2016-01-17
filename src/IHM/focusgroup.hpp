#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

namespace sf {
	class Event;
}

class Widget;

class FocusGroup 
{
	friend class Widget;
	
		/// @brief add a widget to the focus group
		void
		append (Widget& widget);

		void
		remove (Widget& widget);
	
	public:
		~FocusGroup();
		
		void
		setFocus (Widget& widget);

		Widget*
		next ();

		Widget*
		previous ();

		Widget*
		current ();

		void
		unfocus();
		
		bool
		mouseEvent(sf::Event event, sf::Vector2f local);
		
	private:
		std::vector<Widget*> mWidgets;
		Widget*              mCurrent=nullptr;
		static FocusGroup*   mCurrentFocusGroup;

};
