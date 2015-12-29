#pragma once

#include "state.hpp"
//#include "graph/graph.hpp"
#include "editor/anchorpool.hpp"
#include "editor/nodeanchorlistener.hpp"
#include "rosetree/rosetree.hpp"

class EditLevelState : public State
{
	public:
	EditLevelState(StateStack& mystack, Context context);
	virtual ~EditLevelState();
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
	void handlePlayerInput(sf::Keyboard::Key , bool);
	void onFlowerPressed(ID<Flower> flower, sf::Mouse::Button button);
	void onFlowerReleased(ID<Flower> flower, sf::Mouse::Button button);
	ID<Flower> addFlower(sf::Vector2f v, Flower::Type type);
	void removeFlower(ID<Flower> flower);
	void addEdge(ID<Flower> f1, ID<Flower> f2);

	void save(std::string name);
	void load(std::string name);


	std::pair<bool, ID<Flower> > getFlowerDragged()
	{ return std::make_pair(m_isFlowerDragged, mFirstFlower); }

	Texture::ID nextType(Texture::ID type);

	private:
	void mousePressed(sf::Event event, sf::Vector2f pos);
	void mouseReleased(sf::Event event, sf::Vector2f pos);
	void updateAnchors();

	RoseTree mRoseTree;
	AnchorPool mAnchors;
	std::map<ID<Flower>,  NodeAnchorListener*> mFlowerToAnchors;

	bool m_isFlowerDragged;
	ID<Flower> mFirstFlower;
};
