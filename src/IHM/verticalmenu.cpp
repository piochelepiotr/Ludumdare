#include <IHM/verticalmenu.hpp>
#include <IHM/widget.hpp>

VerticalMenu::VerticalMenu (float width) :
	mWidth(width)
{
}


VerticalMenu::VerticalMenu (sf::Vector2f position, float width) :
	mPosition(position),
	mWidth(width)
{
}


void
VerticalMenu::setHorizontalAlignment (HorizontalAlignment align) 
{
	mAlignPolicy = align;
	recompute();
}

void
VerticalMenu::append (Widget& widget)
{
	mWidgets.push_back(&widget);
	recompute();
}

void
VerticalMenu::remove (Widget& widget)
{
	auto it = std::find(mWidgets.begin(), mWidgets.end(), &widget);
	if (it != mWidgets.end())
	{
		mWidgets.erase(it);
		recompute();
	}
}

void
VerticalMenu::recompute() {
	float x_center = mPosition.x;
	float y_pos = mPosition.y;

	if (mAlignPolicy == CENTER) {

		for (auto w : mWidgets)
		{
			sf::Vector2f position = {
				x_center + mWidth/2 - w->getArea().width/2, 
				y_pos
			};

			setWidgetPosition(*w, position);

			y_pos += w->getArea().height+5.f;
		}
	}
}


