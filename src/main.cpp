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
	g.newEdge(sf::Vector2f(300, 270), sf::Vector2f(250, 200));
	g.newEdge(sf::Vector2f(300, 270), sf::Vector2f(350, 210));


    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1280, 1024), "SpaceCheologue");
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
