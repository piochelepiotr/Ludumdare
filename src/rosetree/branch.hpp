#pragma once
#include "id.hpp"
#include "math/spline.hpp"

class Flower;
class RoseTree;

class Branch
{
	public:
	// Types possibles pour une branche
	enum Type {
		None,
		RegularBranch
	};

	// Construit une branche de type t entre f1 et f2
	Branch(ID<Flower> f1, ID<Flower> f2, Type t, RoseTree& rt);

	// Renvoie une des deux fleurs de départ de la branche
	ID<Flower> getFirstFlower() const;
	ID<Flower> getSecondFlower() const;
	// Renvoie la longueur physique de la branche
	float getLength() const;
	// Renvoie le nombre de coccinelles présentes sur cette branche
	unsigned int getLadybugNumber() const;
	// Renvoie le type de la branche
	Type getType() const;

	// Changer le nombre de coccinelles présentes sur cette branche
	void setLadybugNumber(unsigned int nb);
	// Changer le type de la branche
	void setType(Type t = RegularBranch);


	// Renvoie l’avancée réelle si l’avancée est pos relativement à la fleur f0
	float getPos(float pos, ID<Flower> f0) const;
	// Renvoie la position du point à l’avancée pos (entre 0 et 1),
	// en considérant firstFlower comme le point de départ
	sf::Vector2f eval(float pos, ID<Flower> firstFlower) const;
	// Renvoie la dérivée du point à l’avancée pos (entre 0 et 1),
	// en considérant firstFlower comme le point de départ
	sf::Vector2f evalDerivative(float pos, ID<Flower> firstFlower) const;

	void draw(sf::RenderTarget& target) const;

	private:

	// Used to create a branch correctly
	struct HelpCreator
	{
		HelpCreator(ID<Flower> _f1, ID<Flower> _f2, Type _t, RoseTree& _rt);
		ID<Flower> f1ID;
		ID<Flower> f2ID;
		Type type;
		Flower* f1;
		Flower* f2;
	};
	Branch(HelpCreator hc);


	// Crée la SplineShape pour les fleurs f1 et f2
	static SplineShape createSplineShape(Flower& f1, Flower& f2);


	ID<Flower> mFirstFlower;
	ID<Flower> mSecondFlower;
	Type mType;
	SplineShape mSplineShape; // TODO Should we really have the shape here ? Maybe just need a Spline…
	unsigned int mLadybugNumber; // TODO Is this really important ?
};
