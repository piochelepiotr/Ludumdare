#pragma once

#include <SFML/Graphics.hpp>
#include <IHM/widget.hpp>

#include <functional>

/*struct TextButtonStyle {
	
};*/

//button.setStyle(TextButton::Focused, style);

class TextButton : public Widget {
	public:
		using TriggerFun = std::function<void()>;


		TextButton (
			sf::Font& font,                           /// font used by the widget
			TriggerFun callback = []{}   /// callback function called when the widget is triggered
		);

		TextButton (
			const sf::String& text, 
			sf::Font& font, 
			TriggerFun callback = []{}
		);

		/// @brief updates the button state
		void 
		update (sf::Time t) override;

		/// @brief reacts to mouse/keyboard event
		void 
		event (sf::Event e) override;

		/// @brief return the area covered by the widget
		sf::FloatRect
		getArea () const override;

		void 
		setText(const sf::String& text);

		const sf::String& 
		getText() const;

	protected:
		/// @brief Render button
		void
		render (sf::RenderTarget& target, sf::RenderStates state) const override;
		
		virtual void
		enableFocus ();
		
		virtual void
		disableFocus();

	private:
		void
		computeArea ();

		sf::Text       mText;
		TriggerFun     mCallback;
		sf::FloatRect  mArea;
};

