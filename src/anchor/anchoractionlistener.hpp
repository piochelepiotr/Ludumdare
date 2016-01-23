#pragma once 
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

class AnchorActionListener
{
	public:
		virtual ~AnchorActionListener()=default;
	    
		virtual void 
		onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f& position) {};
		
		/*
		virtual void
		onMouseDragged(sf::Mouse::Button button, const sf::Vector2f& position) {}
		*/
		
		virtual void
		onMouseButtonReleased(sf::Mouse::Button button, const sf::Vector2f& position) {}
		
		virtual void
		onMouseEnter() {}
		
		virtual void
		onMouseLeft() {}
	
		virtual sf::Vector2f
		getPosition()=0;
};

