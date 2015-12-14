#include "gamestate.hpp"
#include "graph/flower.hpp"

GameState::GameState(StateStack& mystack, Context context)
: State(mystack, context), mDraggedNode(0, 0)
{
	Graph& g = mGraph;
	g.charge("niveau1");
	/*addNode(Node::ID(350, 210));
	Flower nid(Node::ID(450, 150), 5, sf::seconds(1), Texture::ID::AphidFlower);
	addNode(nid);
	Flower fleur(Node::ID(250, 200), 5, sf::seconds(60), Texture::ID::LadyBugFlower);
	addNode(fleur);
	g.newEdge(sf::Vector2f(300, 170), sf::Vector2f(250, 200));
	g.newEdge(sf::Vector2f(300, 170), sf::Vector2f(350, 210));
	g.newEdge(sf::Vector2f(450, 150), sf::Vector2f(350, 210));*/

    context.textures->load(Texture::ID::OffensiveLadyBug, "graphics/ldb3.png");
    context.textures->load(Texture::ID::NormalLadyBug, "graphics/ldb.png");
    context.textures->load(Texture::ID::DefensiveLadyBug, "graphics/ldb2.png");
    context.textures->load(Texture::ID::Aphid, "graphics/puceron.png");
    context.textures->load(Texture::ID::BackGround, "graphics/bg.png");
    sf::Sprite redLdb;
    redLdb.setTexture(context.textures->get(Texture::ID::NormalLadyBug));
    sf::Sprite redBlackLdb;
    redBlackLdb.setTexture(context.textures->get(Texture::ID::DefensiveLadyBug));
    sf::Sprite blackLdb;
    blackLdb.setTexture(context.textures->get(Texture::ID::OffensiveLadyBug));
    sf::Sprite aphid;
    aphid.setTexture(context.textures->get(Texture::ID::Aphid));
    sf::Sprite backGround;
    backGround.setTexture(context.textures->get(Texture::ID::BackGround));

	mGameWorld = GameWorld(redLdb, redBlackLdb, blackLdb, aphid, backGround, g);
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




void GameState::addNode(Node::ID node)
{
	mGraph.addNode(node);
	mAnchors.addAnchor<NodeAnchor>(AnchorItem(10.f), *this, node);
}

void GameState::addEdge(Node::ID n1, Node::ID n2)
{
	if (mGameWorld.getCapacity() - mGameWorld.getUsedCapacity())
	{
		mGraph.newEdge(n1, n2);
		mGameWorld.increaseUsedCapacity();
	}
}



void GameState::onNodePressed(Node::ID node)
{
	mDraggedNode = node;
	mIsDragged = true;
}

void GameState::onNodeReleased(Node::ID node)
{
	if (mIsDragged && mDraggedNode != node)
		addEdge(mDraggedNode, node);
}

void GameState::updateAnchors()
{
    std::vector<Node::ID> nodes = mGraph.getNodes();
    for(auto node : nodes)
    {
	mAnchors.addAnchor<NodeAnchor>(AnchorItem(10.f), *this, node);
    }
}


/*
void GameState::finDeUnivers()
{
	std::cout << "BOOM" << std::endl;
}
*/
