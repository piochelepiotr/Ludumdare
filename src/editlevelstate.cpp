#include "editlevelstate.hpp"
#include <fstream>
#include "rosetree/branch.hpp"


EditLevelState::EditLevelState(StateStack& mystack, StateContext context)
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
	load("niveau1.txt");
	//mAnchors.addAnchor(AnchorItem(10.f), )
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

}

EditLevelState::~EditLevelState()
{
	save("niveau1.txt");
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
	getContext().window->clear();
	for (auto& id_branch : mRoseTree.getBranchs())
		id_branch.second.draw(*getContext().window);
	for (auto& id_flower : mRoseTree.getFlowers())
		drawFlower(*getContext().window, id_flower.second);
	// mRoseTree.draw(*getContext().window,sf::RenderStates::Default);
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
					mRoseTree[flower].nextType();
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
	//std::cout << "EditLevelState::removeFlower" << std::endl;
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
	for(auto& id_flower : flowers)
	{
		auto ptr = mAnchors.addAnchor<NodeAnchorListener>(AnchorItem(10.f), *this, id_flower.first, id_flower.second.getPosition());
		mFlowerToAnchors[id_flower.first] = ptr;
	}
	m_isFlowerDragged = false;
}


void EditLevelState::drawFlower(sf::RenderTarget& target, Flower const& flower) const
{
	if (flower.getType() == Flower::Node)
		return;
	sf::Transform transform;
	transform.translate(flower.getPosition()).scale(0.3f, 0.3f);
	target.draw(mFlowerSprites.find(flower.getType())->second, transform);
}
