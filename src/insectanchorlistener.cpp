#include <insectanchorlistener.hpp>

#include <editor/anchoractionlistener.hpp>
#include <insect.hpp>

InsectAnchorListener::InsectAnchorListener(Insect& insect) : mInsect(insect) {
}

void
InsectAnchorListener::onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f& position) {
}

void
InsectAnchorListener::onMouseDragged(sf::Mouse::Button button, const sf::Vector2f& position) {
}

void
InsectAnchorListener::onMouseButtonReleased(sf::Mouse::Button button, const sf::Vector2f& position) {
}

void
InsectAnchorListener::onMouseEnter() {
}

void
InsectAnchorListener::onMouseLeft() {
}

sf::Vector2f
InsectAnchorListener::getPosition() {
    return mInsect.getPosition();
}

