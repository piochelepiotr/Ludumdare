#pragma once

#include <vector>
class Widget;

class FocusGroup 
{
	public:
		/// @brief add a widget to the focus group
		void
		append (Widget& widget);

		void
		remove (Widget& widget);

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
		
	private:
		std::vector<Widget*> mWidgets;
		Widget*              mCurrent=nullptr;
		static FocusGroup*   mCurrentFocusGroup;

};
