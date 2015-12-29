#include "editlevelstate.hpp"
#include <fstream>


EditLevelState::EditLevelState(StateStack& mystack, Context context)
	: State(mystack, context)
	  , mFirstFlower(noID)
{
	/*
	ID<Flower> f1 = addFlower(sf::Vector2f(250, 200), Flower::Type::RegularFlower);
	ID<Flower> f2 = addFlower(sf::Vector2f(350, 210), Flower::Type::RegularFlower);
	ID<Flower> f3 = addFlower(sf::Vector2f(450, 150), Flower::Type::RegularFlower);

	addBranch(sf::Vector2f(300, 270), sf::Vector2f(250, 200));
	mGraph.newEdge(sf::Vector2f(300, 270), sf::Vector2f(350, 210));
	mGraph.newEdge(sf::Vector2f(450, 150), sf::Vector2f(350, 210));
	*/
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
//	mRoseTree.draw(*getContext().window,sf::RenderStates::Default);
}

void EditLevelState::mousePressed(sf::Event event, sf::Vector2f pos)
{
	if (!mAnchors.injectEvent(event, pos))
		addFlower(pos, Flower::Type::RegularFlower);
	//mFirstFlower = mGraph.flowerAt(pos);
}

void EditLevelState::mouseReleased(sf::Event event, sf::Vector2f pos)
{
	mAnchors.injectEvent(event, pos);
	m_isFlowerDragged = false;
}

void EditLevelState::onFlowerPressed(ID<Flower> flower, sf::Mouse::Button button)
{
	mFirstFlower = flower;
	m_isFlowerDragged = true;
}


void EditLevelState::onFlowerReleased(ID<Flower> flower, sf::Mouse::Button button)
{
	if(m_isFlowerDragged)
	{
		if(mFirstFlower != flower)
			mRoseTree.addBranch(mFirstFlower,flower);
		else
		{
			switch (button)
			{
				case sf::Mouse::Right:
					removeFlower(flower);
					break;
				case sf::Mouse::Left:
					// FIXME
					mRoseTree[flower].changeType();
					break;
				default:
					break;
			}
		}
	}
}

ID<Flower> EditLevelState::addFlower(sf::Vector2f v, Flower::Type type)
{
	ID<Flower> id = mRoseTree.addFlower(v, type);
	auto ptr = mAnchors.addAnchor<NodeAnchorListener>(AnchorItem(10.f), *this, id, v);
	mFlowerToAnchors[id] = ptr;
	//m_isFlowerDragged = false;
	return id;
}

void EditLevelState::removeFlower(ID<Flower> flower)
{
	mRoseTree.removeFlower(flower);
	auto it = mFlowerToAnchors.find(flower);
	mAnchors.removeAnchor<NodeAnchorListener>(it->second);
	mFlowerToAnchors.erase(it);
}

void EditLevelState::addEdge(ID<Flower> n1, ID<Flower>)
{

}

void EditLevelState::load(std::string name)
{
	std::ifstream file(name);
	mRoseTree.load(file);
	file.close();
	updateAnchors();
}

//void EditLevelState::save(std::__cxx11::string name)
void EditLevelState::save(std::string name)
{
	std::ofstream file(name);
	mRoseTree.save(file);
	file.close();
}

void EditLevelState::updateAnchors()
{
	//mAnchors.clear();
	auto flowers = mRoseTree.getFlowers();
	for(auto id_flower : flowers)
	{
		auto ptr = mAnchors.addAnchor<NodeAnchorListener>(AnchorItem(10.f), *this, id_flower.first, id_flower.second.getPosition());
		mFlowerToAnchors[id_flower.first] = ptr;
	}
	m_isFlowerDragged = false;
}
