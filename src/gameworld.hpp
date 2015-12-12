#pragma once
#include "SFML/Graphics.hpp"
#include <graph/graph.hpp>

struct Node {};
enum NodeType{};

class GameWorld
{
    public:
	GameWorld();
	~GameWorld();
	
	void
	render (sf::RenderTarget& target);
	
	void
	update (sf::Time time);
	
	void
	spawnInsect (InsectType type, Node node);
	
	void
	spawnNode (NodeType type, sf::Vector2f position);
	
    private:
	Graph mGraph;
	std::multimap<int,sf::Sprite>mDrawableObjects;
	std::vector<Insect>mLadyBugs;
	std::vector<Insect>mAphids;
	sf::Sprite mBackGround;
};