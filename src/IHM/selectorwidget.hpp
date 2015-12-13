#pragma once

#include <IHM/widget.hpp>
#include <functional>

class SelectorWidget : public Widget
{
	public:
		using TriggerFun = std::function<void(int)>;
		
		SelectorWidget(sf::Font& font, TriggerFun callback=[](int){});
		
		void 
		event ( sf::Event e ) override;

		sf::FloatRect 
		getArea() const override;

		bool 
		mouseEvent ( sf::Event e, sf::Vector2f local ) override;
		
		void 
		update ( sf::Time t ) override;
		
		void
		addEntry(int id, const sf::String& name);
		
		void
		removeEntry(int id);
		
		void
		removeEntry(const sf::String& name);
		
		void
		next();
		
		void
		previous();
	
	protected:
		
		void
		recompute();	
		
		virtual void
		enableFocus () override;
		
		virtual void
		disableFocus() override;
	
		virtual void render ( sf::RenderTarget& target, sf::RenderStates states ) const;

	private:
	
		sf::Text                                    mText;
		std::size_t                                 mCursor = 0;
		std::vector< std::pair<int, sf::String> >   mEntries;
		TriggerFun                                  mCallback;
	
};
