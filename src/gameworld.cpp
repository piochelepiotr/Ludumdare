#include "gameworld.hpp"
#include "insect/insect.inl"
#include "textureholder.hpp" // TODO on devrait pouvoir l’enlever si on gère mieux
#include "insectanchorlistener.hpp"
#include "anchor/anchorpool.hpp"
//#include "rosetree/branch.hpp"
#include "statecontext.hpp"

GameWorld::GameWorld(AnchorPool& anchor, StateContext& context) :
	mLadyBugs(),
	mAphids(),
	mBackGround(/*backGround*/),
    mInsectSprites(),
    mTotalCapacity(3),
    mLeftCapacity(mTotalCapacity),
    mAnchorPool(anchor)
{
	// TODO Tout ça, ça ne devrait pas être fait ici…
	sf::Sprite redLdb;
	redLdb.setTexture(context.textures->get(Texture::ID::NormalLadyBug));
	redLdb.setOrigin(50.0f, 70.0f);
	redLdb.setScale(.9f, .9f);
	mInsectSprites[static_cast<int>(LadyBug::RedLadybug)] = redLdb;

	sf::Sprite redBlackLdb;
	redBlackLdb.setTexture(context.textures->get(Texture::ID::DefensiveLadyBug));
	redBlackLdb.setOrigin(50.0f, 70.0f);
	redBlackLdb.setScale(.9f, .9f);
	mInsectSprites[static_cast<int>(LadyBug::RedBlackLadybug)] = redBlackLdb;

	sf::Sprite blackLdb;
	blackLdb.setTexture(context.textures->get(Texture::ID::OffensiveLadyBug));
	blackLdb.setOrigin(50.0f, 70.0f);
	blackLdb.setScale(.9f, .9f);
	mInsectSprites[static_cast<int>(LadyBug::BlackLadybug)] = blackLdb;

	sf::Sprite aphid;
	aphid.setTexture(context.textures->get(Texture::ID::Aphid));
	aphid.setOrigin(50.0f, 75.0f);
	aphid.setScale(0.6f, 0.6f);
	// TODO This is just horrible
	mInsectSprites[static_cast<int>(LadyBug::BlackLadybug)+1] = aphid;

	mBackGround.setTexture(context.textures->get(Texture::ID::BackGround));

	// TODO Mauvaise idée, si on modifie les Flowers…
	auto it = mFlowerSprites.insert(std::make_pair(Flower::RegularFlower,
				sf::Sprite(context.textures->get(Texture::ID::RegularFlower))));
	it.first->second.setOrigin(100.f, 100.f);
	it = mFlowerSprites.insert(std::make_pair(Flower::AphidFlower,
				sf::Sprite(context.textures->get(Texture::ID::AphidFlower))));
	it.first->second.setOrigin(100.f, 100.f);
	it.first->second.setColor(sf::Color::Green);
	it = mFlowerSprites.insert(std::make_pair(Flower::LadybugFlower,
				sf::Sprite(context.textures->get(Texture::ID::LadybugFlower))));
	it.first->second.setOrigin(100.f, 100.f);
	it.first->second.setColor(sf::Color::Red);
	/*
	for (auto flower : mRoseTree.getFlowers())
	{
		//ID<Flower> flower = stuff.first;
		switch (mRoseTree[flower].getType())
		{
			case Flower::Type::RegularFlower:
				mFlowers.push_back(new Flower(flower, 5, sf::seconds(60), Flower::Type::RegularFlower));
				break;
			case Flower::Type::AphidFlower:
				mFlowers.push_back(new Flower(flower, 5, sf::seconds(0), Flower::Type::AphidFlower));
				break;
			case Flower::Type::LadyBugFlower:
				mFlowers.push_back(new Flower(flower, 5, sf::seconds(3), Flower::Type::LadyBugFlower));
				break;
			default:
				break;
		}
	}
	*/
}

GameWorld::~GameWorld()
{
	// TODO Est-ce suffisant ?
	for (auto ladybug : mLadyBugs)
		delete ladybug;

	for (auto aphid : mAphids)
		delete aphid;
}


void GameWorld::render(sf::RenderTarget& target)
{
	// On commence par le fond d’écran
	target.draw(mBackGround);

	// Puis on dessine le rosier
	for (auto& id_branch : mRoseTree.getBranchs())
		id_branch.second.draw(target);
	for (auto& id_flower : mRoseTree.getFlowers())
		drawFlower(target, id_flower.second);
		

	// Ensuite viennent les insectes
	for (auto ldb : mLadyBugs) {
		ldb->draw(target, mInsectSprites[static_cast<size_t>(ldb->getType())]);
	}
	for (auto &apd : mAphids) {
		// TODO Just horrible…
		apd->draw(target, mInsectSprites[static_cast<size_t>(LadyBug::BlackLadybug)+1]);
	}

	// Puis enfin, on dessine l’interface
	// la barre de capacité
	sf::RectangleShape ext(sf::Vector2f(24.f, mTotalCapacity*10.f + 4));
	ext.setPosition(8.f, 8.f);
	ext.setFillColor(sf::Color::Green);
	target.draw(ext, sf::RenderStates::Default);
	sf::RectangleShape used(sf::Vector2f(20.f, (mTotalCapacity - mLeftCapacity)*10.f));
	used.setPosition(10.f, 10.f + mLeftCapacity*10.f);
	used.setFillColor(sf::Color::Black);
	target.draw(used, sf::RenderStates::Default);
}

Aphid& GameWorld::spawnAphid(ID<Flower> flower)
{
	mAphids.push_back(new Aphid(mRoseTree, flower, AphidBehaviour::Offensive));
	return *mAphids.back();
}

LadyBug& GameWorld::spawnLadyBug(ID<Flower> flower, LadyBug::Type type)
{
	LadyBug& ladybug = *(new LadyBug(mRoseTree, flower, type));
	mLadyBugs.push_back(&ladybug);
	// TODO Doit-on donner un chemin par défaut aux LadyBug ?
	// TODO Cela dépend du type de LadyBug, non ?
	// TODO Peut-être attendre un clic ici pour que LadyBug apparaîsse…
	// Pour l’instant, on va lui donner un chemin par défaut :
	//		Elle va jusqu’à un nœud voisin de la fleur et elle revient;
	//		Si il n’y a pas de voisin, elle reste là…
	auto& neighbours = mRoseTree.getNeighbours(flower);
	if (!neighbours.empty())
	{
		Path<Flower> p(flower);
		p.addNode(*neighbours.begin());
		ladybug.redefinePath(p);
	}
	mAnchorPool.addAnchor<InsectAnchorListener>(AnchorItem(20.f), ladybug);
	return ladybug;
}

void GameWorld::update(sf::Time dt)
{
	// Commençons par mettre à jour les LadyBugs
	for (auto ladybug : mLadyBugs)
	{
		// Si ladybug n’est pas déjà en train de manger,
		// elle mange un Aphid assez proche sur sa branche
		if (ladybug->isEating())
			ladybug->decreaseEatingTime(dt);
		else
		{
			ladybug->move(dt);

			// TODO C’est toujours pas la bonne solution
			if (!ladybug->isObjectiveReached())
			{
				ID<Branch> currentBranch = ladybug->getBranch();
				float currentPos = ladybug->getPos();

				for (auto it = mAphids.begin() ; it != mAphids.end() ; ++it)
				{
					Aphid& aphid = **it;
					// TODO Il faudrait changer ces conditions
					if (aphid.getBranch() == currentBranch &&
							std::abs(currentPos - aphid.getPos()) < 0.1f)
					{
						ladybug->eatAnAphid(aphid);
						delete &aphid;
						mAphids.erase(it);
						break;
					}
				}
			}
		}
	}

	// On s’occupe des Aphids. Si l’un d’entre eux atteint une fleur,
	// alors il se suicide, et enlève un point à la fleur.
	// Comme il est plus facile d’ajouter en fin de tableau que de supprimer,
	// on crée un nouveau tableau auquel on n'ajoute tous ceux qu’on enlève pas
	// (tordu, n’est-il pas ? c’est pourquoi TODO Changer ça (ou pas))
	std::vector<Aphid*> newAphids;
	for (auto aphid : mAphids)
	{
		aphid->move(dt);
		if (aphid->isObjectiveReached())
		{
			Flower& flower = mRoseTree[aphid->getPrevFlower()];
			// TODO Est-ce ce qu’il faut faire ?
			if (!flower.loseOnePoint())
				flower.becomeNode();
			delete aphid;
		}
		else
		{
			newAphids.push_back(aphid);
		}
	}
	mAphids = std::move(newAphids);

	// Et maintenant, les fleurs. Il faut juste libérer, délivrer les insectes
	// qui peuvent l’être.
	for (auto& ID_n_flower : mRoseTree.getFlowers())
	{
		Flower& flower = ID_n_flower.second;
		if (flower.update(dt))
		{
			switch(flower.getType())
			{
				case Flower::AphidFlower:
					spawnAphid(ID_n_flower.first);
					flower.setTimeLeft(sf::seconds(0.9f)); // TODO Ne pas le fixer à 2
					break;
				case Flower::LadybugFlower:
					spawnLadyBug(ID_n_flower.first, LadyBug::BlackLadybug);
					flower.becomeNode(); // Doit-on faire ça ?
					break;
				default:
					break;
			}
		}
	}
}


void GameWorld::drawFlower(sf::RenderTarget& target, Flower const& flower) const
{
	if (flower.getType() == Flower::Node)
		return;
	sf::Transform transform;
	transform.translate(flower.getPosition()).scale(0.3f, 0.3f);
	target.draw(mFlowerSprites.find(flower.getType())->second, transform);
}
