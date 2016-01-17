#pragma once

#include <editor/anchoractionlistener.hpp>

// TODO LATER Pour l’instant rien n’est fait, il faudrait
// - gérer l’appui
// - peut-être mettre en surbrillance les Insects qu’on survole

class Insect;

class InsectAnchorListener : public AnchorActionListener
{

    public:
	InsectAnchorListener(Insect& insect);

	void
	onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f& position) override;

	void
	onMouseDragged(sf::Mouse::Button button, const sf::Vector2f& position) override;

	void
	onMouseButtonReleased(sf::Mouse::Button button, const sf::Vector2f& position) override;

	void
	onMouseEnter() override;

	void
	onMouseLeft() override;

	sf::Vector2f
	getPosition() override;

    private:
        Insect&  mInsect;

};
