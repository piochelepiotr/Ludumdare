#pragma once 
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

class AnchorActionListener
{
	public:
		virtual void 
		onMouseButtonPressed() {};
		
		virtual void
		onMouseDragged(sf::Mouse::Button button, const sf::Vector2f& position) {}
		
		virtual void
		onMouseButtonReleased() {}
		
		virtual void
		onMouseEnter() {}
		
		virtual void
		onMouseLeft() {}
	
};

