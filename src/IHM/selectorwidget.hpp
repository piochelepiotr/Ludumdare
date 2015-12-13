#pragma once

#include <IHM/widget.hpp>

class SelectorWidget : public Widget
{
	public:
		virtual void 
		event ( sf::Event e );

		virtual sf::FloatRect 
		getArea() const;

		virtual bool 
		mouseEvent ( sf::Event e, sf::Vector2f local );
		
		virtual void 
		update ( sf::Time t );
		
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
	
		virtual void render ( sf::RenderTarget& target, sf::RenderStates states ) const;

	private:
	
		sf::Text                                    mText;
		std::size_t                                 mCursor = 0;
		std::vector< std::pair<int, sf::String> >   mEntries;
	
};
