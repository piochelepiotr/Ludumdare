#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "textureholder.hpp"
#include "font.hpp"
#include "player.hpp"
#include "state.hpp"
#include "application.hpp"

#include "graph/graph.hpp"

int main()
{
	Graph g;
	g.addNode(Node::ID(250, 200));
	g.addNode(Node::ID(350, 210));
	g.addNode(Node::ID(450, 150));
	auto b1 = g.newEdge(sf::Vector2f(300, 270), sf::Vector2f(250, 200));
	auto b2 = g.newEdge(sf::Vector2f(300, 270), sf::Vector2f(350, 210));
	auto b3 = g.newEdge(sf::Vector2f(450, 150), sf::Vector2f(350, 210));
	std::cout << g.distance(Node::ID(250, 200), Node::ID(300, 270)) << std::endl;
	std::cout << g.isCulDeSac(b2) << std::endl;



    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1280, 1024), "Jeu qu'on va peut-etre appeler « Rose Bud », mais on n'est pas sur");
	//window.clear();
	//g.draw(window, sf::RenderStates::Default);
	//window.display();
	//sf::sleep(sf::milliseconds(100000));

    window.setFramerateLimit(90);
    TextureHolder textures;
    FontHolder fonts;

	fonts.load(Font::Text, "fonts/text.ttf");

    Player player;
    struct State::Context context(window, textures, fonts, player);
    Application app(context);
    int truc = app.run();


    return truc;
}
