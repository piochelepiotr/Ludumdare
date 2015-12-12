#pragma once

#include <SFML/Graphics.hpp>

#include <IHM/layout.hpp>

class Widget;

class VerticalMenu : public Layout {

	public:

		VerticalMenu (float width);

		VerticalMenu (sf::Vector2f position, float width);

		enum HorizontalAlignment {
			LEFT,
			CENTER,
			RIGHT
		};

		/// @brief set the alignment policy for widgets
		void
		setHorizontalAlignment (HorizontalAlignment align);

		/// @brief append a widget to the bottom of the layout
		void 
		append (Widget& widget);

		/// @brief remove a widget from the layout
		void
		remove (Widget& widget);

	protected:
		void
		recompute () override;


	private:
		std::vector<Widget*> mWidgets;
		float                mWidth;
		sf::Vector2f         mPosition;
		HorizontalAlignment  mAlignPolicy = CENTER;
};
