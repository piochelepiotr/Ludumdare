#include "editlevelstate.hpp"


EditLevelState::EditLevelState(StateStack& mystack, Context context)
: State(mystack, context)
, mFirstNode(250.f, 200.f)
{
    mGraph.addNode(Node::ID(250, 200));
    mGraph.addNode(Node::ID(350, 210));
    mGraph.addNode(Node::ID(450, 150));

    mGraph.newEdge(sf::Vector2f(300, 270), sf::Vector2f(250, 200));
    mGraph.newEdge(sf::Vector2f(300, 270), sf::Vector2f(350, 210));
    mGraph.newEdge(sf::Vector2f(450, 150), sf::Vector2f(350, 210));
    
    //mAnchors.addAnchor(AnchorItem(10.f), )
}

EditLevelState::~EditLevelState()
{

}

bool EditLevelState::handleEvent(const sf::Event& event)
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
		    mousePressed(event, mContext.window->mapPixelToCoords(sf::Mouse::getPosition(*mContext.window)));
		    break;
		case sf::Event::MouseButtonReleased:
		    mouseReleased(event, mContext.window->mapPixelToCoords(sf::Mouse::getPosition(*mContext.window)));
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
    return false;
}

void EditLevelState::draw()
{
    mGraph.draw(*getContext().window,sf::RenderStates::Default);
}

void EditLevelState::mousePressed(sf::Event event, sf::Vector2f pos)
{
    mAnchors.injectEvent(event, pos);
    //mFirstNode = mGraph.nodeAt(pos);
}

void EditLevelState::mouseReleased(sf::Event event, sf::Vector2f pos)
{
    mAnchors.injectEvent(event, pos);
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
