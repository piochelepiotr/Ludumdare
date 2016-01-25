#include <IHM/verticalmenu.hpp>
#include <IHM/widget.hpp>

VerticalMenu::VerticalMenu (float width) :
	mWidth(width)
{
}


VerticalMenu::VerticalMenu (sf::Vector2f position, float width) :
	mWidth(width),
	mPosition(position)
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
	widget.addListener(*this);
	recompute();
}

void
VerticalMenu::remove (Widget& widget)
{
	auto it = std::find(mWidgets.begin(), mWidgets.end(), &widget);
	if (it != mWidgets.end())
	{
		mWidgets.erase(it);
		widget.removeListener(*this);
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
	else if (mAlignPolicy == LEFT) {
		
		for (auto w : mWidgets)
		{
			sf::Vector2f position = {
				x_center,
				y_pos
			};
			setWidgetPosition(*w, position);
			
			y_pos += w->getArea().height+5.f;
		}
	}
	else if (mAlignPolicy == RIGHT) {
		
		for (auto w : mWidgets)
		{
			sf::Vector2f position = {
				x_center + mWidth - w->getArea().width,
				y_pos
			};
			setWidgetPosition(*w, position);
			
			y_pos += w->getArea().height+5.f;
		}
	}
}


void VerticalMenu::onUpdate(Observable< Updatable >& source)
{
	recompute();
}

void VerticalMenu::setPosition(sf::Vector2f position)
{
	mPosition = position;
	recompute();
}

void VerticalMenu::setWidth(float width)
{
	mWidth = width;
	recompute();
}
