#pragma once

class AnchorItem
{
	public:
		inline AnchorItem(float radius=10.f);

		//virtual void
		//setPosition (const sf::Vector2f& position) =0;
		
		inline void
		setRadius (float radius);

		//virtual sf::Vector2f
		//getPosition () const =0;
		
		inline float
		getRadius () const;

		inline float
		getSquareRadius () const;
	
	private:
		float mRadius;
};


// AnchorItem inline functions

AnchorItem::AnchorItem(float radius) : mRadius(radius)
{
}

void
AnchorItem::setRadius(float radius)
{
	mRadius = radius;
}

float
AnchorItem::getRadius() const
{
	return mRadius;
}

float
AnchorItem::getSquareRadius() const
{
	return mRadius * mRadius;
}
