#include "insect.hpp"
#include "graph/graph.hpp"
#include <iostream>

// code d’Adrien
/*
void Insect::draw(sf::RenderTarget& target, Graph *g, sf::Sprite sprite) {
  Branch *b = g->getBranch(path.getBranchID(currentBranch));
  float cpos = pos;
  float sign = 1.0f;
  if (b->getSecondNode() == path.getNodeID(currentBranch)) {
    cpos = 1-pos;
    sign = -1.0f;
  }
  sf::Vector2f posVect = b->getSpline().evaluatePos(cpos);
  sf::Vector2f speedVect = b->getSpline().evaluateSpeed(cpos) * sign;
  angle = atan2(speedVect.y, speedVect.x);

  sprite.setRotation(angle * 180.0f / 3.14159265f + 90.0f);
  sprite.setPosition(posVect);
  hitbox.setPosition(posVect);
  hitbox.setRadius(30.f);
  hitbox.setOrigin(25.f,25.f);
  if(mDisplay)
    target.draw(hitbox);
  target.draw(sprite);
}

sf::Vector2f Insect::getPosition() const {
    return hitbox.getPosition();
}

void Insect::move(float dt, Graph* g) {
  float len = g->getBranch(path.getBranchID(currentBranch))->getLength();
  pos += speed * dt / len;
  if (pos > 1.0f) {
    pos = 0.0f;
    currentBranch += 1;
    if (currentBranch == path.size())
    {
        currentBranch = 0;
        reachedObjective = true;
    }
  }
}
  */ // Code d’Adrien fin

// Code d’Antonin
void Insect::draw(sf::RenderTarget& target, Graph const&g, sf::Sprite sprite) {
	Branch const&b = g[path.getBranchID(currentBranch)];
	float cpos = pos;
	float sign = 1.0f;
	if (b.getSecondNode() == path.getNodeID(currentBranch)) {
		cpos = 1 - cpos;
		sign = -1.0f;
	}

	sf::Vector2f posVect = b.getSpline().evaluatePos(cpos);
	sf::Vector2f speedVect = sign * b.getSpline().evaluateSpeed(cpos);
	angle = atan2(speedVect.y, speedVect.x);

	sprite.setRotation(angle * 180.0f / 3.14159265f + 90.0f);
	sprite.setPosition(posVect);
	hitbox.setPosition(posVect);
	target.draw(hitbox);
	target.draw(sprite);
}

void Insect::move(float dt, Graph const& g) {
	float len = g[path.getBranchID(currentBranch)].getLength();
	pos += speed * dt / len;
	if (pos > 1.0f) {
		pos = 0.0f;
		currentBranch += 1;
		if (currentBranch >= path.size())
		{
			currentBranch = 0;
			reachedObjective = true;
		}
	}
}
// Fin code Antonin

Insect::type Insect::getType() {
	return mType;
}


void Insect::setDisplayCircle(bool d)
{
    mDisplay = d;
}

Insect::Insect(type mType, float fhitbox ,int currentBranch , float pos,
		float speed, float angle, Node::ID obj, bool bo) :
	mType(mType)
	, hitbox(fhitbox)
	, currentBranch(currentBranch)
	, pos(pos)
	, speed(speed)
	, angle(angle)
	, objective(obj)
	, reachedObjective(bo)
{
	hitbox.setOrigin(fhitbox, fhitbox);
}


Aphid::Aphid(AphidBehaviour::ID b, Node::ID spawn, Graph const& g) :
	Insect(Insect::Aphid, 10, 0, 0.0f, 50.0f, 0.0f, spawn, false),
	behaviour(b, spawn, g)
{
	path = behaviour.getPath();
	objective = behaviour.getObjective();
}


LadyBug::LadyBug(Insect::type type, Node::ID spawn, Graph const& g) :
	Insect(type, 12, 0, 0.0f, 50.f*1.5f, 0.0f, spawn, true)
{
    Branch::ID spawnBranch = g.getNeighbours(spawn).begin()->second;
	// ^ Is that really cool
    path.addBranch(spawn, spawnBranch);
    path.addBranch(g[spawnBranch].getFirstNode(), spawnBranch);
//	path = AphidBehaviour(AphidBehaviour::Offensive, spawn, g).getPath();
}

void LadyBug::RedefinePath(Path newPath, Graph const &g) {
	futurePath = newPath;
	if (!futurePath.isCyclic(g))
		futurePath.makeCyclic(g);

	Node::ID nextNode = g[path.getBranchID(currentBranch)].getOtherNode(path.getNodeID(currentBranch));

	float shortestDist = std::numeric_limits<float>::infinity();
	std::set<Node::ID> nodes = newPath.getNodes(g);
	for (auto id : nodes) {
		if (g.getDist(nextNode, id) < shortestDist) {
			shortestDist = g.getDist(nextNode, id);
			objective = id;
		}
	}

	Node::ID prevNode = path.getNodeID(currentBranch);
	Branch::ID currBranch = path.getBranchID(currentBranch);
	path = g.getPath(nextNode, objective);
	path.insertBranch(prevNode, currBranch);
	reachedObjective = false;
}


void LadyBug::move(float dt, Graph const& g) {
	float len = g[path.getBranchID(currentBranch)].getLength();
	pos += speed * dt / len;
	//im like not sure at all the objective stuff is safe
	//get ready for segfaults <3
	if (pos > 1.0f) {
		pos = 0.0f;
		currentBranch += 1;
		if (currentBranch >= path.size()) {
			currentBranch = 0;
			if (!reachedObjective) {
				reachedObjective = true;
				path = futurePath;
			}
		}
	}
}

float Insect::getPos(Graph const& g)
{
	Branch const& b = g[path.getBranchID(currentBranch)];
	float cpos = pos;
	if (b.getSecondNode() != path.getNodeID(currentBranch))
	{
		cpos = 1-pos;
	}
	return cpos;
}

