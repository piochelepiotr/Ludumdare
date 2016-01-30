#include "insect/insect.inl"


void Insect::move(sf::Time dt) {
	if (isObjectiveReached())
		return;

	float len = getRealBranch().getLength();
	mPos += mSpeed * dt.asSeconds() / len;
	if (mPos > 1.0f) {
		mPos = 0.0f;
		mPath.pop();
	}

	// On actualise les informations sur la position et tout ça
	if (isObjectiveReached())
	{
		mRealPosition = mRoseTree[getPrevFlower()].getPosition();
	}
	else
	{
		Branch const& b = getRealBranch();
		mRealPosition = b.eval(mPos, getPrevFlower());
		sf::Vector2f speed = b.evalDerivative(mPos, getPrevFlower());
		mAngle = atan2(speed.y, speed.x);
	}
	
}


Insect::Insect(RoseTree const& rt, ID<Flower> spawnFlower, float speed) :
	mRoseTree(rt), mPath(spawnFlower), mSpeed(speed), mPos(0)
{
	mRealPosition = mRoseTree[getPrevFlower()].getPosition();
}


Aphid::Aphid(RoseTree const& rt, ID<Flower> spawnFlower, AphidBehaviour::Type t) :
	Insect(rt, spawnFlower, 50.0f), mBehaviour(t, spawnFlower, rt)
{
	move(sf::seconds(0.f));
	mPath = mBehaviour.getPath();
}


void Ladybug::redefinePath(Path<Flower> newPath)
{
	mDutyPath = newPath;
	if (!mDutyPath.isCyclic())
		mRoseTree.makeCyclic(mDutyPath);

	//std::cerr << "I'm here" << std::endl;
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


void Ladybug::move(sf::Time dt)
{
	Insect::move(dt);

	if (isObjectiveReached())
	{
		//std::cerr << "My objective is reached (just like my tailor)." << std::endl;
		ID<Flower> position = getPrevFlower();
		mPath = mDutyPath;
		mPath.popUntil(position);
	}
}

Ladybug::Type Ladybug::getType() {
	return mType;
}

float Insect::getPos() const
{
	if (isObjectiveReached())
		return 0.f;

	return getRealBranch().getPos(mPos, getPrevFlower());
}
