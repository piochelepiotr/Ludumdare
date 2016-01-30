#include "textureholder.hpp"
#include "font.hpp"
#include "player.hpp"
#include "application.hpp"

#include <iostream>


int main() noexcept
{
	std::cerr << sizeof(sf::Sprite) << std::endl;
	std::cerr << sizeof(sf::Transformable) << std::endl;
	std::cerr << sizeof(sf::Drawable) << std::endl;
	std::cerr << sizeof(sf::Transform) << std::endl;

	sf::RenderWindow window(sf::VideoMode(1280, 1024), "Jeu qu'on va peut-etre appeler « RoseBud », mais on n'est pas sur");
	TextureHolder textures;
	FontHolder fonts;
	Player player;
	struct StateContext context(window, textures, fonts, player);

	// Set the window params
	window.setFramerateLimit(90);
	// TODO This is useless here…
	auto view = window.getDefaultView();
	view.setSize(1280,1024);
	window.setView(view);

	// Load textures
	context.textures->load(Texture::OffensiveLadybug, "graphics/ldb3.png");
	context.textures->load(Texture::NormalLadybug, "graphics/ldb.png");
	context.textures->load(Texture::DefensiveLadybug, "graphics/ldb2.png");
	context.textures->load(Texture::Aphid, "graphics/puceron.png");
	context.textures->load(Texture::Background, "graphics/bg.png");
	context.textures->load(Texture::RegularFlower, "graphics/bigflower.png");
	// TODO Ces images ne sont pas utilitées comme prévues
	context.textures->load(Texture::AphidFlower, "graphics/flower1.png");
	context.textures->load(Texture::LadybugFlower, "graphics/flower3.png");
	context.textures->load(Texture::NodeFlower, "../ld33/graphics/items/pan2.png");

	// Load fonts
	fonts.load(Font::Text, "fonts/text.ttf");
	fonts.load(Font::Standard, "fonts/standard.ttf");

	// Set the player params

	// And Now, start the application
	Application app(context);
	int truc = app.run();

	return truc;
}
