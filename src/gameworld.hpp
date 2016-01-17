#pragma once
#include "SFML/Graphics.hpp"
#include "insect.hpp"
#include "rosetree/flower.hpp"

class StateContext;// TODO À enlever au plus vite: on n’a besoin de ça que pour StateContext, qui ne sert que pour les Sprites


// FIXME Seems there is a problem when you click an insect, you can't do anything else anymore

class AnchorPool;

class GameWorld
{
	public:
		GameWorld(AnchorPool &ap, StateContext& context); // TODO À modifier au plus vite…
		GameWorld& operator= (GameWorld& world);
		~GameWorld();

		void render (sf::RenderTarget& target);

		void update (sf::Time dt);

		void load(std::istream& is) { mRoseTree.load(is); }
		ID<Flower> addFlower(sf::Vector2f position, Flower::Type type)
		{ return mRoseTree.addFlower(position, type); }
		ID<Branch> addBranch(ID<Flower> f1, ID<Flower> f2)
		{ return mRoseTree.addBranch(f1, f2); }
		IDstaticmap<Flower>& getFlowers()
		{ return mRoseTree.getFlowers(); }




		Aphid& spawnAphid (ID<Flower> flower);
		LadyBug& spawnLadyBug (ID<Flower> flower, LadyBug::Type type);

		ID<Flower> spawnNode (sf::Vector2f position, Flower::Type type);


		// Capacity
		int getCapacity(){return mCapacity;};
		void increaseCapacity(){mCapacity++;};
		int getUsedCapacity(){return mUsedCapacity;};
		void setUsedCapacity(int newUsedCapacity){mUsedCapacity = newUsedCapacity;};
	private:
		//inline RoseTree& getGraph() { return mRoseTree; }
		void drawFlower(sf::RenderTarget& target, Flower const& flower) const; // TODO Should not be here

		RoseTree mRoseTree;
		std::vector<LadyBug*> mLadyBugs;
		std::vector<Aphid*> mAphids;
		//std::vector<Flower*> mFlowers;
		sf::Sprite mBackGround; // TODO Ces trois lignes ne devraient pas être là
		sf::Sprite mInsectSprites[4];
		std::map<Flower::Type, sf::Sprite> mFlowerSprites;
		int mCapacity;
		int mUsedCapacity;
		AnchorPool& mAnchorPool; // TODO C’est un peu bizarre qu’il soit là lui…
};
