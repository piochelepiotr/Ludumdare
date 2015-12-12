#include <IHM/widget.hpp>

void
Widget::setPosition (const sf::Vector2f& position)
{
	mPosition = position;
}

const sf::Vector2f&
Widget::getPosition () const {
	return mPosition;
}

void
Widget::draw (sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform.translate(mPosition);
	render(target, states);
}
