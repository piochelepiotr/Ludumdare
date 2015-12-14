#include "editlevelstate.hpp"
#include <iostream>


EditLevelState::EditLevelState(StateStack& mystack, Context context)
: State(mystack, context)
, mFirstNode(0.f,0.f)
{
    mTypes.push_back(Texture::ID::RegularNode);
    mTypes.push_back(Texture::ID::LadyBugFlower);
    mTypes.push_back(Texture::ID::AphidFlower);
    mTypes.push_back(Texture::ID::Flower);
    mTypes.push_back(Texture::ID::SemperFlower);
    addNode(Node::ID(250, 200));
    addNode(Node::ID(350, 210));
    addNode(Node::ID(450, 150));

    mGraph.newEdge(sf::Vector2f(300, 270), sf::Vector2f(250, 200));
    mGraph.newEdge(sf::Vector2f(300, 270), sf::Vector2f(350, 210));
    mGraph.newEdge(sf::Vector2f(450, 150), sf::Vector2f(350, 210));
    load("niveau1");
    //mAnchors.addAnchor(AnchorItem(10.f), )
}

EditLevelState::~EditLevelState()
{
    save("niveau1");
}

bool EditLevelState::handleEvent(const sf::Event& event)
{
    auto mouse = mContext.window->mapPixelToCoords(sf::Mouse::getPosition(*mContext.window));
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
		    mousePressed(event, mouse);
		    break;
		case sf::Event::MouseButtonReleased:
		    mouseReleased(event, mouse);
		    break;

        default:
	        break;
    }
    return false;
}

void EditLevelState::handlePlayerInput(sf::Keyboard::Key, bool)
{

}

bool EditLevelState::update(sf::Time dt)
{
    return mAnchors.injectMouse(mContext.window->mapPixelToCoords(sf::Mouse::getPosition(*mContext.window)));
}

void EditLevelState::draw()
{
    mGraph.draw(*getContext().window,sf::RenderStates::Default);
}

void EditLevelState::mousePressed(sf::Event event, sf::Vector2f pos)
{
	if (!mAnchors.injectEvent(event, pos))
	{
		addNode(Node::ID(pos));
	}
	//mFirstNode = mGraph.nodeAt(pos);
}

void EditLevelState::mouseReleased(sf::Event event, sf::Vector2f pos)
{
    mAnchors.injectEvent(event, pos);
	if (m_isNodeDragged)
	{
	}
	m_isNodeDragged = false;
    //Node::ID secondNode = mGraph.nodeAt(pos);
    //if(mFirstNode.id.x >= 0 && secondNode.id.x >= 0 && !(mFirstNode.id == secondNode.id))
    //{
	//mGraph.newEdge(mFirstNode,secondNode);
    //}
    //else
    //{
	//mGraph.addNode(Node::ID(pos.x,pos.y));
    //}
}

void EditLevelState::onNodePressed(Node::ID node)
{
    mFirstNode = node;
	m_isNodeDragged = true;
}


void EditLevelState::onNodeReleased(Node::ID node)
{
	std::cout << node.id.x << "  " << mFirstNode.id.x << std::endl;
    if(m_isNodeDragged)
    {
	if(mFirstNode != node)
	{
		mGraph.forceNewEdge(mFirstNode,node);
	}
	else
	{
	    mGraph[node].setType(nextType(mGraph[node].getType()));
	}
    }
	m_isNodeDragged = false;
}

void EditLevelState::addNode(Node::ID node)
{
    mGraph.addNode(node);
    mAnchors.addAnchor<NodeAnchorListener>(AnchorItem(10.f), *this, node);
	m_isNodeDragged = false;
}

void EditLevelState::addEdge(Node::ID n1, Node::ID)
{

}

void EditLevelState::load(std::string name)
{
    mGraph.charge(name);
    updateAnchors();
}

//void EditLevelState::save(std::__cxx11::string name)
void EditLevelState::save(std::string name)
{
    mGraph.save(name);
}

void EditLevelState::updateAnchors()
{
    //mAnchors.clear()
    std::vector<Node::ID> nodes = mGraph.getNodes();
    for(auto node : nodes)
    {
	mAnchors.addAnchor<NodeAnchorListener>(AnchorItem(10.f), *this, node);
    }
    m_isNodeDragged = false;
}

Texture::ID EditLevelState::nextType(Texture::ID type)
{
    int l = mTypes.size();
    for(int i = 0; i < l; i++)
    {
	if(type == mTypes[i])
	{
	    if(i == l-1)
		return mTypes[0];
	    else
		return mTypes[i+1];
	}
    }
    return mTypes[0];
}


