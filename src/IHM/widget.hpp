#pragma once

#include <SFML/Graphics.hpp>

#include <IHM/layout.hpp>
#include <IHM/focusgroup.hpp>

#include <observable.hpp>

/// @brief : base class for widget with conveniance function for alignment purpose
class Widget : public sf::Drawable, public Observable<Updatable>
{
	public:
		/// @brief updates the button state
		virtual void 
		update (sf::Time t)=0;

		virtual 
		~Widget() = default;

		/// @brief reacts to mouse/keyboard event
		virtual void 
		event (sf::Event e)=0;

		/// @brief return the area covered by the widget
		virtual sf::FloatRect
		getArea () const=0;

		/// @brief return the shift required by the widget
		virtual sf::Vector2f
		getShift() const { return {0,0}; }

		const sf::Vector2f&
		getPosition() const;

		void
		setFocusGroup(FocusGroup* group);

		FocusGroup*
		getFocusGroup();

		void
		focus();

	protected:
		friend class Layout;
		friend class FocusGroup;

		/// @brief Render button
		void
		draw (sf::RenderTarget& target, sf::RenderStates states) const;

		virtual void
		render (sf::RenderTarget& target, sf::RenderStates states) const=0;

		virtual void
		enableFocus () {}

		virtual void
		disableFocus() {}

	private:

		virtual void
		setPosition (const sf::Vector2f& position);


		sf::Vector2f mPosition;
		FocusGroup* mFocusGroup;
};

