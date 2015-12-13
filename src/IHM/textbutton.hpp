#pragma once

#include <SFML/Graphics.hpp>
#include <IHM/widget.hpp>

#include <functional>

struct TextButtonStyle {
	TextButtonStyle() = default;
	
	TextButtonStyle(sf::Color c, sf::Font* f, std::size_t s) : color(c), font(f), char_size(s) {}
	
	sf::Color color;
	sf::Font* font;
	std::size_t char_size=18;
	
	sf::Color frame_color=sf::Color::White;
	float thickness=0.f;
	
	sf::Color fill_color= sf::Color::Transparent;
	
	enum StyleType {
		Normal,
		Focus
	};
};

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
		
		TextButton (
			const sf::String& text,
			TextButtonStyle normal,
			TextButtonStyle focus,
			TriggerFun callback = []{}
		);

		/// @brief updates the button state
		void 
		update (sf::Time t) override;

		/// @brief reacts to mouse/keyboard event
		void 
		event (sf::Event e) override;

		bool 
		mouseEvent(sf::Event e, sf::Vector2f local) override;
	
		/// @brief return the area covered by the widget
		sf::FloatRect
		getArea () const override;

		void 
		setText(const sf::String& text);

		const sf::String& 
		getText() const;
		
		void 
		setStyle(TextButtonStyle style);
		
		void
		defineStyle(TextButtonStyle::StyleType type, TextButtonStyle style);

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
		
		TextButtonStyle mStyleNormal;
		TextButtonStyle mStyleFocus;
		
		TextButtonStyle::StyleType mStyleType;
};

