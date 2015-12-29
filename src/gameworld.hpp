#pragma once
#include "SFML/Graphics.hpp"
//#include <graph/graph.hpp>
#include "insect.hpp"
//#include "graph/flower.hpp"
#include "editor/anchorpool.hpp"
#include "state.hpp" // TODO À enlever au plus vite
#include "rosetree/flower.hpp"

#include <memory>

//class Node;

//enum NodeType{};

class GameWorld
{
	public:
		GameWorld(RoseTree &rt, AnchorPool &ap, State::Context& context);// : mRoseTree(rt), mAnchorPool(ap) {} //this shouldnt exist. gameworld needs sprites! // TODO À modifier au plus vite…
		//GameWorld(GameWorld& world)=default;
		GameWorld& operator= (GameWorld& world);
		//GameWorld(sf::Sprite redLdb, sf::Sprite redBlackLdb, sf::Sprite BlackLdb, sf::Sprite aphid,sf::Sprite backGround, RoseTree& g, AnchorPool& anchor);
		~GameWorld();

		void render (sf::RenderTarget& target);

		void update (sf::Time dt);

		Insect* spawnInsect (Insect::Type type, ID<Flower> flower);

		ID<Flower> spawnNode (sf::Vector2f position, Flower::Type type);

		int getCapacity(){return mCapacity;};
		void increaseCapacity(){mCapacity++;};
		int getUsedCapacity(){return mUsedCapacity;};
		void setUsedCapacity(int newUsedCapacity){mUsedCapacity = newUsedCapacity;};
	private:
		//inline RoseTree& getGraph() { return mRoseTree; }

		RoseTree& mRoseTree;
		std::vector<LadyBug*> mLadyBugs;
		std::vector<Aphid*> mAphids;
		//std::vector<Flower*> mFlowers;
		sf::Sprite mBackGround; // TODO Ces deux lignes devraient pas être là
		sf::Sprite mInsectSprites[4];
		int mCapacity;
		int mUsedCapacity;
		AnchorPool& mAnchorPool;
};
