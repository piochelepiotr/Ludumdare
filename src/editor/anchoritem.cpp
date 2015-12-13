#include <editor/anchoritem.hpp>

AnchorItem::AnchorItem(float radius)
{
	setRadius(radius);
}

float AnchorItem::getRadius() const
{
	return mRadius;
}

void AnchorItem::setRadius(float radius)
{
	mRadius = radius;
}
