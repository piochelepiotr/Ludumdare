#pragma once
#include "behaviour.hpp"
#include "rosetree/rosetree.hpp"
#include "rosetree/path.hpp"
#include <SFML/Graphics.hpp>

class Insect {
	public:

		// TODO : Il faudrait en fait faire des types pour les Ladybugs, pas pour les insects.
	enum Type {RedLadybug, RedBlackLadybug, BlackLadybug, RegularAphid};

	Insect(Type mType, ID<Flower> node, RoseTree const& rt, float fhitbox, float speed, float angle);
	void move(sf::Time dt); // TODO C’est très casse-gueule, parce qu’il y a aussi une méthode move pour les coccinelles…
	void draw(sf::RenderTarget& target, sf::Sprite sprite);

	Type getType();
	Branch const& getBranch() const { return mRoseTree.getBranch(mPath.getTwoFirstNodes()); }
	ID<Branch> getBranchID() const { return mRoseTree.getBranchID(mPath.getTwoFirstNodes()); }
	float getPos() const;
	bool isObjectiveReached() const { return mPath.isEmpty(); }
	ID<Flower> getPrevFlower() const { return mPath.getFirstNode(); }
	ID<Flower> getNextFlower() const { return mPath.getTwoFirstNodes().second; }
	//  ID<Flower> getObjective() { return objective; }
	sf::Vector2f getPosition() const;

	void setDisplayCircle(bool display);

	protected:
	Type mType;
	Path<Flower> mPath;
	RoseTree const& mRoseTree;
	sf::CircleShape mHitbox;
	float mPos;
	float mSpeed;
	float mAngle;
	//  ID<Flower> objective;
	bool mDisplay=false; // TODO We must remove this, just for debugging
};

class Aphid : public Insect {
	public:
	Aphid(AphidBehaviour::Type b, ID<Flower> spawn, RoseTree const& rt);
	private:
	AphidBehaviour mBehaviour;
};

class LadyBug : public Insect {
	public:
	LadyBug(Insect::Type type, ID<Flower> spawn, RoseTree const& rt);
	void redefinePath(Path<Flower> newPath);
	void move(sf::Time dt);
	// void setBusy(bool bo) {busy = bo;};
	//sf::Time getBusyTime() { return busyTime; };
	void eatAnAphid(Aphid& aphid) { mEatingTime = sf::seconds(0.2f); }
	bool isEating() { return mEatingTime > sf::seconds(0); }
	void decreaseEatingTime(sf::Time dt) { mEatingTime -= dt; }

	private:
	Path<Flower> mDutyPath;
	sf::Time mEatingTime = sf::seconds(0);
};

