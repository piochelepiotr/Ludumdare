#pragma once
#include <SFML/System/Vector2.hpp>

class AnchorItem
{
	public:
		AnchorItem(float radius=10.f);
		
		virtual void
		setPosition (const sf::Vector2f& position) =0;
		
		void 
		setRadius (float radius);

		virtual sf::Vector2f
		getPosition () const =0;
		
		float
		getRadius () const;
	
	private:
		float mRadius;
};
