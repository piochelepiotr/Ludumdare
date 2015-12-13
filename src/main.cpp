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

int main()
{
	Graph g;
	g.addNode(Node::ID(250, 200));
	g.addNode(Node::ID(350, 210));
	g.addNode(Node::ID(450,150));
	g.newEdge(sf::Vector2f(300, 270), sf::Vector2f(250, 200));
	auto b2 = g.newEdge(sf::Vector2f(300, 270), sf::Vector2f(350, 210));
	g.newEdge(sf::Vector2f(450, 150), sf::Vector2f(350, 210));
	//std::cout << g.isCulDeSac(b2) << std::endl;



    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1280, 1024), "Jeu qu'on va peut-etre appeler « Rose Bud », mais on n'est pas sur");
	sf::sleep(sf::milliseconds(100));
	window.clear();
	g.draw(window, sf::RenderStates::Default);
	window.display();
	sf::sleep(sf::milliseconds(1000));
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
    Application app(context);
    int truc = app.run();


    return truc;
}
