#include "insect.hpp"
#include "graph/graph.hpp"
#include <iostream>

sf::Vector2f Insect::getPosition() const {
    return hitbox.getPosition();
}

void Insect::draw(sf::RenderTarget& target, Graph const&g, sf::Sprite sprite) {
	if (isObjectiveReached())
	{
		// TODO Pour l’instant ça ne fait pas quelque chose d’interressant…
		auto posVect = g[getPrevNode()].getPosition();
		sprite.setPosition(posVect);
		hitbox.setPosition(posVect);
		target.draw(hitbox);
		target.draw(sprite);
		std::cout << "holaalal" << std::endl;
	}
	else
	{
		Branch const& b = g[getBranch()];

		sf::Vector2f posVect = b(pos, getPrevNode());
		sf::Vector2f speedVect = b.derivative(pos, getPrevNode());
		angle = atan2(speedVect.y, speedVect.x);

		sprite.setRotation(angle * 180.0f / 3.14159265f + 90.0f);
		sprite.setPosition(posVect);
		hitbox.setPosition(posVect);
		target.draw(hitbox);
		target.draw(sprite);
	}
}

void Insect::move(float dt, Graph const& g) {
	if (isObjectiveReached())
		return;

	float len = g[getBranch()].getLength();
	pos += speed * dt / len;
	if (pos > 1.0f) {
		pos = 0.0f;
		path.popBranch(g);
	}
}

Insect::type Insect::getType() {
	return mType;
}


void Insect::setDisplayCircle(bool d)
{
    mDisplay = d;
}

Insect::Insect(type mType, Node::ID node, float fhitbox,
		float speed, float angle) :
	mType(mType), path(node), hitbox(fhitbox),
	pos(0) , speed(speed) , angle(angle)
{
	hitbox.setOrigin(fhitbox, fhitbox);
}


Aphid::Aphid(AphidBehaviour::ID b, Node::ID spawn, Graph const& g) :
	Insect(Insect::Aphid, spawn, 10.f, 50.0f, 0.0f),
	behaviour(b, spawn, g)
{
	move(0.f, g);
	path = behaviour.getPath();
}


LadyBug::LadyBug(Insect::type type, Node::ID spawn, Graph const& g) :
	Insect(type, spawn, 12.f, 50.f*1.5f, 0.0f), dutyPath(spawn)
{
	move(0.f, g);
//	path.addBranch(spawn, spawnBranch);
//	path.addBranch(g[spawnBranch].getFirstNode(), spawnBranch);
//	path = AphidBehaviour(AphidBehaviour::Offensive, spawn, g).getPath();
}

void LadyBug::redefinePath(Path newPath, Graph const &g)
{
	dutyPath = newPath;
	if (!dutyPath.isCyclic(g))
		dutyPath.makeCyclic();

	Node::ID nextNode = isObjectiveReached() ? getPrevNode() : g[getBranch()].getOtherNode(getPrevNode());

	Node::ID objective = nextNode;
	float shortestDist = std::numeric_limits<float>::infinity();
	std::set<Node::ID> nodes = newPath.getNodes(g);
	for (auto id : nodes) {
		if (g.getDist(nextNode, id) < shortestDist) {
			shortestDist = g.getDist(nextNode, id);
			objective = id;
		}
	}

	path = g.getPath(nextNode, objective);
	path.insertBranch(getPrevNode(), getBranch());
}


void LadyBug::move(float dt, Graph const& g)
{
	Insect::move(dt, g);

	if (isObjectiveReached())
	{
		Node::ID position = getPrevNode();
		path = dutyPath;
		path.popUntil(position, g);
	}
}

float Insect::getPos(Graph const& g) const
{
	if (isObjectiveReached())
		return 0.f;

	return g[getBranch()].isFirstNode(path.getPrevNode()) ? pos : 1.f - pos;
}
