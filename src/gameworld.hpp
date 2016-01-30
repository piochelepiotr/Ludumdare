#pragma once
#include "SFML/Graphics.hpp"
#include "insect/insect.hpp"
#include "rosetree/flower.hpp"
#include "rosetree/rosetree.hpp"

template <typename T> class IDstaticmap;

/// \brief Gère l’univers du jeu (insectes, arbre…).
class GameWorld
{
	public:
	enum Mode { // Flags for the mode of this GameWorld
		EditMode,
		GameMode
	};

	public:
	GameWorld(Mode mode);
	GameWorld& operator= (GameWorld& world) = delete;
	GameWorld(GameWorld& world) = delete;
	~GameWorld();
	void update (sf::Time dt);

	// Flowers
	public:
	inline ID<Flower> addFlower(sf::Vector2f position, Flower::Type type);
	inline void removeFlower(ID<Flower>);
	inline ID<Flower> spawnFlower (sf::Vector2f position, Flower::Type type);
	inline Flower::Type nextType(ID<Flower> f);

	// Branchs
	public:
	ID<Branch> addBranch(ID<Flower> f1, ID<Flower> f2);

	// Insects
	public:
	Aphid& spawnAphid (ID<Flower> flower);
	Ladybug& spawnLadybug (ID<Flower> flower, Ladybug::Type type);

	// Get everything
	public:
	inline IDstaticmap<Flower> const& getFlowers() const;
	inline IDstaticmap<Branch> const& getBranchs() const;
	inline std::vector<Ladybug*> const& getLadybugs() const;
	inline std::vector<Aphid*> const& getAphids() const;

	// Input-Output
	public:
	inline void load(std::istream& is);
	inline void save(std::ostream& os) const;

	// Capacity
	public:
	inline int getRemainingCapacity() const;
	inline int getTotalCapacity() const;
	private:
	inline void useCapacity(int usedCapacity);
	inline void increaseTotalCapacity();

	// Attirbutes
	private:
	RoseTree mRoseTree;
	std::vector<Ladybug*> mLadybugs;
	std::vector<Aphid*> mAphids;
	int mTotalCapacity;
	int mRemainingCapacity;
	Mode mMode;
};
