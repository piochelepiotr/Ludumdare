#pragma once
#include "SFML/Graphics.hpp"
#include <graph/graph.hpp>
#include "insect.hpp"
#include "graph/flower.hpp"
#include "editor/anchorpool.hpp"

enum NodeType{};

class GameWorld
{
	public:
		GameWorld()=default; //this shouldnt exist. gameworld needs sprites!
		GameWorld(GameWorld& world)=default;
		//Graph& operator= (GameWorld& world);
		GameWorld(sf::Sprite redLdb, sf::Sprite redBlackLdb, sf::Sprite BlackLdb, sf::Sprite aphid,sf::Sprite backGround, Graph& g);
		~GameWorld();

		void
			render (sf::RenderTarget& target);

		void
			update (sf::Time dt);

		void
			spawnInsect (Insect::type type, Node node);

		void
			spawnNode (NodeType type, sf::Vector2f position);

		int getCapacity(){return mCapacity;};
		void increaseCapacity(){mCapacity++;};
		int getUsedCapacity(){return mUsedCapacity;};
		void setUsedCapacity(int newUsedCapacity){mUsedCapacity = newUsedCapacity;};
	private:
		Graph* mGraph;
		std::vector<LadyBug> mLadyBugs;
		std::vector<Aphid> mAphids;
		std::vector<Flower> mFlowers;
		sf::Sprite mBackGround;
		sf::Sprite mInsectSprites[4];
		int mCapacity;
		int mUsedCapacity;
		AnchorPool mAnchorPool;
};
