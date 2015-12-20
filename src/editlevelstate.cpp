#include "editlevelstate.hpp"
#include <iostream>


EditLevelState::EditLevelState(StateStack& mystack, Context context)
	: State(mystack, context)
	  , mFirstNode(0.f,0.f)
{
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
		addNode(Node::ID(pos));
	//mFirstNode = mGraph.nodeAt(pos);
}

void EditLevelState::mouseReleased(sf::Event event, sf::Vector2f pos)
{
	mAnchors.injectEvent(event, pos);
	m_isNodeDragged = false;
}

void EditLevelState::onNodePressed(Node::ID node, sf::Mouse::Button button)
{
	mFirstNode = node;
	m_isNodeDragged = true;
}


void EditLevelState::onNodeReleased(Node::ID node, sf::Mouse::Button button)
{
	if(m_isNodeDragged)
	{
		if(mFirstNode != node)
			mGraph.forceNewEdge(mFirstNode,node);
		else
		{
			switch (button)
			{
				case sf::Mouse::Right:
					removeNode(node);
					break;
				case sf::Mouse::Left:
					// FIXME
					mGraph[node].nextType();
					break;
				default:
					break;
			}
		}
	}
}

void EditLevelState::addNode(Node::ID node)
{
	mGraph.addNode(node);
	auto ptr = mAnchors.addAnchor<NodeAnchorListener>(AnchorItem(10.f), *this, node);
	mNodeToAnchors[node] = ptr;
	//m_isNodeDragged = false;
}

void EditLevelState::removeNode(Node::ID node)
{
	mGraph.removeNode(node);
	auto it = mNodeToAnchors.find(node);
	mAnchors.removeAnchor<NodeAnchorListener>(it->second);
	mNodeToAnchors.erase(it);
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
	//mAnchors.clear();
	std::vector<Node::ID> nodes = mGraph.getNodes();
	for(auto node : nodes)
	{
		auto ptr = mAnchors.addAnchor<NodeAnchorListener>(AnchorItem(10.f), *this, node);
		mNodeToAnchors[node] = ptr;
	}
	m_isNodeDragged = false;
}
