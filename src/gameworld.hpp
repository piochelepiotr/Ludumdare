#pragma once
#include "SFML/Graphics.hpp"
#include <graph/graph.hpp>
#include <splinerenderer.hpp>
#include "insect.hpp"



enum NodeType{};

class GameWorld
{
public:
  GameWorld(); //this shouldnt exist. gameworld needs sprites!
  GameWorld(sf::Sprite redLdb, sf::Sprite redBlackLdb, sf::Sprite BlackLdb, sf::Sprite aphid);
  ~GameWorld();
	
  void
  render (sf::RenderTarget& target);
	
  void
  update (sf::Time dt);
	
  void
  spawnInsect (Insect::type type, Node node);
	
  void
  spawnNode (NodeType type, sf::Vector2f position);
	
private:
  Graph mGraph;
  SplineRenderer mSplineRenderer;
  std::vector<LadyBug>mLadyBugs;
  std::vector<Aphid>mAphids;
  sf::Sprite mBackGround;
  sf::Sprite mInsectSprites[4];
};
