#pragma once

#include <IHM/layout.hpp>
#include <observer.hpp>

class Widget;

class VerticalMenu : public Layout, public Observer<Updatable> {

	public:

		VerticalMenu (float width=50.f);

		VerticalMenu (sf::Vector2f position, float width);

		enum HorizontalAlignment {
			LEFT,
			CENTER,
			RIGHT
		};
		
		void
		setPosition(sf::Vector2f position);
		
		void
		setWidth(float width);

		/// @brief set the alignment policy for widgets
		void
		setHorizontalAlignment (HorizontalAlignment align);

		/// @brief append a widget to the bottom of the layout
		void
		append (Widget& widget);

		/// @brief remove a widget from the layout
		void
		remove (Widget& widget);

		virtual void
		onUpdate(Observable< Updatable >& source);
		
		
		
	protected:
		void
		recompute () override;


	private:
		std::vector<Widget*> mWidgets;
		float                mWidth;
		sf::Vector2f         mPosition;
		HorizontalAlignment  mAlignPolicy = CENTER;
};
