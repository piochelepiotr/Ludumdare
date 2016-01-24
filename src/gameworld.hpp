#pragma once
#include "SFML/Graphics.hpp"
#include "insect/insect.hpp"
#include "rosetree/flower.hpp"
#include "rosetree/rosetree.hpp"

template <typename T> class IDstaticmap;
class StateContext;// TODO À enlever au plus vite: on n’a besoin de ça que pour StateContext, qui ne sert que pour les Sprites

class GameWorld
{
	public:
	enum Mode { // Flags for the mode of this GameWorld
		EditMode,
		GameMode
	};

	GameWorld(StateContext& context, Mode mode); // TODO À modifier au plus vite…
	GameWorld& operator= (GameWorld& world);
	~GameWorld();

	void render (sf::RenderTarget& target);

	void update (sf::Time dt);

	inline void load(std::istream& is);
	inline void save(std::ostream& os) const;
	inline ID<Flower> addFlower(sf::Vector2f position, Flower::Type type);
	inline void removeFlower(ID<Flower>);
	ID<Branch> addBranch(ID<Flower> f1, ID<Flower> f2);
	inline IDstaticmap<Flower>& getFlowers();


	Aphid& spawnAphid (ID<Flower> flower);
	LadyBug& spawnLadyBug (ID<Flower> flower, LadyBug::Type type);

	inline ID<Flower> spawnFlower (sf::Vector2f position, Flower::Type type);
	inline Flower::Type nextType(ID<Flower> f);


	// Capacity
	inline void useCapacity(int usedCapacity);
	inline int getLeftCapacity();
	inline int getTotalCapacity();
	inline void increaseTotalCapacity();

	private:
	void drawFlower(sf::RenderTarget& target, Flower const& flower) const; // TODO Should not be here

	RoseTree mRoseTree;
	std::vector<LadyBug*> mLadyBugs;
	std::vector<Aphid*> mAphids;
	sf::Sprite mBackGround; // TODO Ces trois lignes ne devraient pas être là
	sf::Sprite mInsectSprites[4];
	std::map<Flower::Type, sf::Sprite> mFlowerSprites;
	int mTotalCapacity;
	int mLeftCapacity;

	Mode mMode;
};
