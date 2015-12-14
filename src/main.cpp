#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "textureholder.hpp"
#include "font.hpp"
#include "player.hpp"
#include "state.hpp"
#include "application.hpp"

#include "graph/graph.hpp"
#include "graph/flower.hpp"
#include "path.hpp"


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1280, 1024), "Jeu qu'on va peut-etre appeler « RoseBud », mais on n'est pas sur");

	Graph g;

	/*g.addNode(Node::ID(250, 200));
	g.addNode(Node::ID(350, 210));
	g.addNode(Node::ID(450,150));
	g.forceNewEdge(sf::Vector2f(250, 200),sf::Vector2f(300, 170));
	g.forceNewEdge(sf::Vector2f(350, 210),sf::Vector2f(300, 300));
	g.forceNewEdge(sf::Vector2f(450, 150), sf::Vector2f(350, 210));
	g.save("niveau1");
	g.charge("niveau1");
	std::cout << g.isCulDeSac(b2) << std::endl;
	window.clear();

	g.draw(window, sf::RenderStates::Default);
	g.save("niveau1");
	window.display();
	sf::sleep(sf::milliseconds(2000));

	Path p = g.getPath(Node::ID(300, 300), Node::ID(450, 150));
	std::cout << p.length(g) << std::endl;
	std::cout << p.getSize() << std::endl;
	for (int i = 0 ; i < p.getSize() ; i++)
	{
		std::cout << g[p[i].first].getPosition().x << " " << g[p[i].first].getPosition().y << std::endl;
	}

*/
    auto view = window.getDefaultView();
    view.setSize(1280,1024);
    window.setView(view);

    window.setFramerateLimit(90);
    TextureHolder textures;
    FontHolder fonts;

	fonts.load(Font::Text, "fonts/text.ttf");
	fonts.load(Font::Standard, "fonts/standard.ttf");

    Player player;
    struct State::Context context(window, textures, fonts, player);
    context.textures->load(Texture::ID::OffensiveLadyBug, "graphics/ldb3.png");
    context.textures->load(Texture::ID::NormalLadyBug, "graphics/ldb.png");
    context.textures->load(Texture::ID::DefensiveLadyBug, "graphics/ldb2.png");
    context.textures->load(Texture::ID::Aphid, "graphics/puceron.png");
    context.textures->load(Texture::ID::BackGround, "graphics/bg.png");
    Application app(context);
    int truc = app.run();


    return truc;
}
