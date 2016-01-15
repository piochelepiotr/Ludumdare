#include "gamestate.hpp"
#include "rosetree/flower.hpp"
#include <fstream>

GameState::GameState(StateStack& mystack, Context context) :
	State(mystack, context),
	mGameWorld(mRoseTree, mAnchors, context),
	mDraggedFlower(noID)
{
	std::ifstream file("niveau1.txt");
	mRoseTree.load(file);
	file.close();
	updateAnchors();
	/*
	Node::ID n0(sf::Vector2f(500, 900));
	Node::ID n1(sf::Vector2f(300, 800));
	Node::ID n2(600, 700);
	Node::ID n3(400, 550);

	addNode(n1);
	addNode(n2);
	addNode(n3);

	Flower nid(Node::ID(700, 600), 5, sf::seconds(1), Texture::ID::AphidFlower);
	addNode(nid);
	Flower fleur(Node::ID(200, 740), 5, sf::seconds(60), Texture::ID::LadyBugFlower);
	addNode(fleur);

	g.newEdge(n0, n2);
	g.newEdge(n0, n1);
	g.newEdge(nid, n2);
	g.newEdge(n1, fleur);
	*/
    sf::Sprite redLdb;
    sf::Sprite redBlackLdb;
    sf::Sprite blackLdb;
    sf::Sprite aphid;
    sf::Sprite backGround;

	//mGameWorld = GameWorld(redLdb, redBlackLdb, blackLdb, aphid, backGround, mRoseTree, mAnchors);
}

GameState::~GameState()
{

}

bool GameState::handleEvent(const sf::Event& event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				requestStackPush(States::Menu);
			else
				handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::MouseButtonPressed:
			mAnchors.injectEvent(event, getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window)));
			break;

		case sf::Event::MouseButtonReleased:
			mAnchors.injectEvent(event, getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window)));
			mIsDragged = false;
			break;

        default:
            break;
    }
    return true;
}

void GameState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{

}

bool GameState::update(sf::Time dt)
{
	bool b = mAnchors.injectMouse(getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window)));
	getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window));
	mGameWorld.update(dt);
	return b;
}

void GameState::draw()
{
    mGameWorld.render(*mContext.window);
}




void GameState::addFlower(sf::Vector2f position, Flower::Type type)
{
	ID<Flower> id = mRoseTree.addFlower(position, type);
	mAnchors.addAnchor<NodeAnchor>(AnchorItem(10.f), *this, id, position);
}

void GameState::addBranch(ID<Flower> f1, ID<Flower> f2)
{
	if (mGameWorld.getCapacity() - mGameWorld.getUsedCapacity())
	{
		mRoseTree.addBranch(f1, f2);
		mGameWorld.setUsedCapacity(mGameWorld.getUsedCapacity()+1);
	}
}



void GameState::onFlowerPressed(ID<Flower> flower)
{
	mDraggedFlower = flower;
	mIsDragged = true;
}

void GameState::onFlowerReleased(ID<Flower> flower)
{
	if (mIsDragged && mDraggedFlower != flower)
		addBranch(mDraggedFlower, flower);
}

void GameState::updateAnchors()
{
    auto flowers = mRoseTree.getFlowers();
    for(auto& id_flower : flowers)
    {
		mAnchors.addAnchor<NodeAnchor>(AnchorItem(10.f), *this,
				id_flower.first, id_flower.second.getPosition());
    }
}
