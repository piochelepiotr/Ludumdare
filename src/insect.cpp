#include "insect.hpp"
//#include "graph/graph.hpp"
#include <iostream>
#include "rosetree/flower.hpp"
#include "rosetree/branch.hpp"

sf::Vector2f Insect::getPosition() const {
    return mHitbox.getPosition();
}

void Insect::draw(sf::RenderTarget& target, sf::Sprite sprite) {
	if (isObjectiveReached())
	{
		// TODO Pour l’instant ça ne fait pas quelque chose d’intéressant…
		auto posVect = mRoseTree[getPrevFlower()].getPosition();
		sprite.setPosition(posVect);
		mHitbox.setPosition(posVect);
		target.draw(mHitbox);
		target.draw(sprite);
	}
	else
	{
		Branch const& b = getBranch();

		sf::Vector2f posVect = b.eval(mPos, getPrevFlower());
		sf::Vector2f speedVect = b.evalDerivative(mPos, getPrevFlower());
		mAngle = atan2(speedVect.y, speedVect.x);

		sprite.setRotation(mAngle * 180.0f / 3.14159265f + 90.0f);
		sprite.setPosition(posVect);
		mHitbox.setPosition(posVect);
		target.draw(mHitbox);
		target.draw(sprite);
	}
}

void Insect::move(sf::Time dt) {

	if (isObjectiveReached())
		return;

	float len = getBranch().getLength();
	mPos += mSpeed * dt.asSeconds() / len;
	if (mPos > 1.0f) {
		mPos = 0.0f;
		mPath.pop();
	}
}

Insect::Type Insect::getType() {
	return mType;
}


void Insect::setDisplayCircle(bool d)
{
    mDisplay = d;
}

Insect::Insect(Type mType, ID<Flower> flower, RoseTree const& rt, float fhitbox,
		float speed, float angle) :
	mType(mType), mPath(flower), mRoseTree(rt), mHitbox(fhitbox),
	mPos(0), mSpeed(speed), mAngle(angle)
{
	mHitbox.setOrigin(fhitbox, fhitbox);
}


Aphid::Aphid(AphidBehaviour::Type b, ID<Flower> spawn, RoseTree const& rt) :
	Insect(Insect::RegularAphid, spawn, rt, 10.f, 50.0f, 0.0f),
	mBehaviour(b, spawn, rt)
{
	move(sf::seconds(0.f));
	mPath = mBehaviour.getPath();
}


LadyBug::LadyBug(Insect::Type type, ID<Flower> spawn, RoseTree const& rt) :
	Insect(type, spawn, rt, 12.f, 50.f*1.5f, 0.0f), mDutyPath(spawn)
{
	// Juste pour faire la mise au point du path
	move(sf::seconds(0.f));
//	path.addBranch(spawn, spawnBranch);
//	path.addBranch(g[spawnBranch].getFirstNode(), spawnBranch);
//	path = AphidBehaviour(AphidBehaviour::Offensive, spawn, g).getPath();
}

void LadyBug::redefinePath(Path<Flower> newPath)
{
	mDutyPath = newPath;
	if (!mDutyPath.isCyclic())
		mRoseTree.makeCyclic(mDutyPath);

	std::cerr << "I'm here" << std::endl;
	// Trouver le chemin le plus court jusqu’à l’un de ces nœuds
	if (isObjectiveReached())
	{
		mRoseTree.getPathToCloserOf(newPath.getNodes().begin(), newPath.getNodes().end(), getPrevFlower(), mPath);
	}
	else
	{
		ID<Flower> prevFlower = getPrevFlower();
		mRoseTree.getPathToCloserOf(newPath.getNodes().begin(), newPath.getNodes().end(), getNextFlower(), mPath);
		mPath.insertNode(prevFlower);
	}
}


void LadyBug::move(sf::Time dt)
{
	Insect::move(dt);
	std::cerr << "I have to move" << std::endl;

	if (isObjectiveReached())
	{
		std::cerr << "My objective is reached (just like my tailor)." << std::endl;
		ID<Flower> position = getPrevFlower();
		mPath = mDutyPath;
		mPath.popUntil(position);
	}
}

float Insect::getPos() const
{
	if (isObjectiveReached())
		return 0.f;

	return getBranch().getPos(mPos, getPrevFlower());
}
