#include "insect.hpp"
#include "graph/graph.hpp"
#include <iostream>

void Insect::draw(sf::RenderTarget& target, Graph *g, sf::Sprite sprite) {
  Branch *b = g->getBranch(path.getBranchID(currentBranch));
  float cpos = pos;
  if (b->getSecondNode() == path.getNodeID(currentBranch))
    cpos = 1 - pos;
  sf::Vector2f posVect = b->getSpline().evaluatePos(cpos);
  sf::Vector2f speedVect = b->getSpline().evaluateSpeed(cpos);
  angle = atan2(speedVect.y, speedVect.x);

  sprite.setRotation(angle * 180.0f / 3.14159265f + 90.0f);
  sprite.setPosition(posVect);
  hitbox.setPosition(posVect);
  target.draw(hitbox);
  target.draw(sprite);
}

void Insect::move(float dt, Graph* g) {
  float len = g->getBranch(path.getBranchID(currentBranch))->getLength();
  pos += speed * dt / len;
  if (pos > 1.0f) {
    pos = 0.0f;
    currentBranch += 1;
    if (currentBranch == path.size())
      currentBranch = 0;
  }
}

Insect::type Insect::getType() {
  return mType;
}

Insect::Insect(type mType, float fhitbox
	       ,int currentBranch
	       , float pos, float speed, float angle) : mType(mType)
						      , hitbox(fhitbox)
						      , currentBranch(currentBranch)
						      , pos(pos)
						      , speed(speed)
						      , angle(angle)
{
  hitbox.setOrigin(fhitbox, fhitbox);
}

Aphid::Aphid(AphidBehaviour::ID b, Node spawn, Graph *g) : Insect(Insect::Aphid, 10, 0, 0.0f, 1.0f, 0.0f)
						    , behaviour(b, spawn, *g)
{
  path = behaviour.getPath();
}


LadyBug::LadyBug(Insect::type type, Node spawn, Graph *g) : Insect(type, 12, 0, 0.0f, 1.5f, 0.0f)
							  , objective(spawn)
							  , reachedObjective(true)
{

}

void LadyBug::RedefinePath(Path newPath, Graph &g) {
  futurePath = newPath;
  if (!futurePath.isCyclic(g))
    futurePath.makeCyclic(g);

  Node::ID nextNode = path.getNodeID(currentBranch);
  if (currentBranch + 1 == path.size())
    nextNode = path.getLastNodeID(g);
  else
    nextNode = path.getNodeID(currentBranch + 1);

  float shortestDist = 1e16; //not pretty :s
  std::set<Node::ID> nodes = newPath.getNodes(g);
  for (auto &id : nodes) {
    if (g.getDist(id, nextNode) < shortestDist) {
      shortestDist = g.getDist(id, nextNode);
      objective = id;
    }
  }
  Node::ID prevNode = path.getNodeID(currentBranch);
  Branch::ID currBranch = path.getBranchID(currentBranch);
  path = g.getPath(nextNode, objective);
  path.insertBranch(prevNode, currBranch);
  reachedObjective = false;
}


void LadyBug::move(float dt, Graph* g) {
  float len = g->getBranch(path.getBranchID(currentBranch))->getLength();
  pos += speed * dt / len;
  //im like not sure at all the objective stuff is safe
  //get ready for segfaults <3
  if (pos > 1.0f) {
    pos = 0.0f;
    currentBranch += 1;
    if (currentBranch == path.size()) {
      currentBranch = 0;
      if (!reachedObjective) {
	reachedObjective = true;
	path = futurePath;
      }
    }
  }
}
