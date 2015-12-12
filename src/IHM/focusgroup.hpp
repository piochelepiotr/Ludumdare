#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

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
