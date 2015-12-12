#include <IHM/layout.hpp>
#include <IHM/widget.hpp>

void
Layout::setWidgetPosition(Widget& widget, const sf::Vector2f& position) {
	widget.setPosition(position);
}

