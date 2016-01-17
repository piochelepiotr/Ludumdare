#pragma once

#include <SFML/Graphics.hpp>

class Player;
class TextureHolder;
class FontHolder;


struct StateContext
{
	StateContext(sf::RenderWindow& win, TextureHolder& textu, FontHolder& fon, Player& myplayer)
	{
		window = &win;
		textures = &textu;
		fonts = &fon;
		player = &myplayer;
	}
	sf::RenderWindow* window;
	TextureHolder* textures;
	FontHolder* fonts;
	Player* player;
};
 
