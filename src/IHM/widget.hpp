#pragma once

#include <SFML/Graphics.hpp>

#include <observable.hpp>

class FocusGroup;

/// @brief : base class for widget with conveniance function for alignment purpose
class Widget : public sf::Drawable, public Observable<Updatable>
{
	public:
		/// @brief updates the button state
		virtual void
		update (sf::Time t)=0;

		virtual
		~Widget();

		/// @brief reacts to mouse/keyboard event
		/// @return true if e has been used, false in other cases
		virtual bool
		event (sf::Event e)=0;

		virtual bool
		mouseEvent (sf::Event e, sf::Vector2f local)=0;
		
		/// @brief return the area covered by the widget
		virtual sf::FloatRect
		getArea () const=0;

		/// @brief return the shift required by the widget
		virtual sf::Vector2f
		getShift() const { return {0,0}; }

		const sf::Vector2f&
		getPosition() const;
		
		const sf::Vector2f&
		getSize() const;

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
		
		virtual void
		onPositionChange() {}

	private:

		virtual void
		setPosition (const sf::Vector2f& position);

		virtual void
		setSize (const sf::Vector2f& size);

		sf::Vector2f mPosition;
		sf::Vector2f mSize;
		FocusGroup* mFocusGroup=nullptr;
};

