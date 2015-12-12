#pragma once

#include <SFML/Graphics.hpp>
#include <IHM/widget.hpp>

class TextButton : public Widget {
	public:
		using TriggerFun = std::function<(void)()>;


		TextButton (
			sf::Font& font,                           /// font used by the widget
			std::function<(void)()> callback = []{}   /// callback function called when the widget is triggered
		);

		TextButton (
			const sf::String& text, 
			sf::Font& font, 
			std::function<(void)() callback = []{}
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

		sf::String& 
		getText() const;

	protected:
		/// @brief Render button
		void
		render (sf::RenderTarget& target, sf::RenderState state) const override;

	private:
		void
		computeArea ();

		sf::Text                    mText;
		sf::function<(void)()>      mCallback;
		sf::FloatRect               mArea;
};

