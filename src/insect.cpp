#include "insect.hpp"
//#include "graph/graph.hpp"
#include <iostream>
#include "rosetree/flower.hpp"
#include "rosetree/branch.hpp"

sf::Vector2f Insect::getPosition() const {
    return hitbox.getPosition();
}

void Insect::draw(sf::RenderTarget& target, RoseTree const& rt, sf::Sprite sprite) {
	if (isObjectiveReached())
	{
		// TODO Pour l’instant ça ne fait pas quelque chose d’intéressant…
		auto posVect = rt[getPrevFlower()].getPosition();
		sprite.setPosition(posVect);
		hitbox.setPosition(posVect);
		target.draw(hitbox);
		target.draw(sprite);
		std::cout << "holaalal" << std::endl;
	}
	else
	{
		Branch const& b = getBranch();

		sf::Vector2f posVect = b.eval(pos, getPrevFlower());
		sf::Vector2f speedVect = b.evalDerivative(pos, getPrevFlower());
		angle = atan2(speedVect.y, speedVect.x);

		sprite.setRotation(angle * 180.0f / 3.14159265f + 90.0f);
		sprite.setPosition(posVect);
		hitbox.setPosition(posVect);
		target.draw(hitbox);
		target.draw(sprite);
	}
}

void Insect::move(float dt, RoseTree const& rt) {
	if (isObjectiveReached())
		return;

	float len = getBranch().getLength();
	pos += speed * dt / len;
	if (pos > 1.0f) {
		pos = 0.0f;
		path.pop();
	}
}

Insect::Type Insect::getType() {
	return mType;
}


void Insect::setDisplayCircle(bool d)
{
    mDisplay = d;
}

Insect::Insect(Type mType, ID<Flower> flower, float fhitbox,
		float speed, float angle) :
	mType(mType), path(flower), hitbox(fhitbox),
	pos(0) , speed(speed) , angle(angle)
{
	hitbox.setOrigin(fhitbox, fhitbox);
}


Aphid::Aphid(AphidBehaviour::Type b, ID<Flower> spawn, RoseTree const& rt) :
	Insect(Insect::Aphid, spawn, 10.f, 50.0f, 0.0f),
	behaviour(b, spawn, rt)
{
	move(0.f, rt);
	path = behaviour.getPath();
}


LadyBug::LadyBug(Insect::Type type, ID<Flower> spawn, RoseTree const& rt) :
	Insect(type, spawn, 12.f, 50.f*1.5f, 0.0f), dutyPath(spawn)
{
	move(0.f, rt);
//	path.addBranch(spawn, spawnBranch);
//	path.addBranch(g[spawnBranch].getFirstNode(), spawnBranch);
//	path = AphidBehaviour(AphidBehaviour::Offensive, spawn, g).getPath();
}

void LadyBug::redefinePath(Path<Flower> newPath, RoseTree const& rt)
{
	dutyPath = newPath;
	if (!dutyPath.isCyclic())
		rt.makeCyclic(dutyPath);

	ID<Flower> nextFlower = isObjectiveReached() ? getPrevFlower() : getNextFlower();

	rt.getPathToCloserOf(newPath.getNodes().begin(), newPath.getNodes().end(), nextFlower, path);

	// Trouver le chemin le plus court jusqu’à l’un de ces nœuds
	
	/*
	ID<Flower> objective = nextFlower;
	float shortestDist = std::numeric_limits<float>::infinity();
	auto flowers = newPath.getNodes();
	for (auto id : flowers) {
		if (rt.getDist(nextFlower, id) < shortestDist) {
			shortestDist = rt.getDist(nextFlower, id);
			objective = id;
		}
	}
	rt.getPath(nextFlower, objective, path);
	*/
	path.insertNode(getPrevFlower());


}


void LadyBug::move(float dt, RoseTree const& rt)
{
	Insect::move(dt, rt);

	if (isObjectiveReached())
	{
		ID<Flower> position = getPrevFlower();
		path = dutyPath;
		path.popUntil(position);
	}
}

float Insect::getPos(RoseTree const& rt) const
{
	if (isObjectiveReached())
		return 0.f;

	return getBranch().getPos(pos, getPrevFlower());
}
