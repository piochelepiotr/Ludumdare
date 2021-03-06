#pragma once
#include "utils/id.hpp"
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
	inline Branch(ID<Flower> f1, ID<Flower> f2, Type t, RoseTree& rt);

	// Renvoie une des deux fleurs de départ de la branche
	inline ID<Flower> getFirstFlower() const;
	inline ID<Flower> getSecondFlower() const;
	// Renvoie le type de la branche
	inline Type getType() const;
	// Renvoie la longueur physique de la branche
	inline float getLength() const;
	// Renvoie le nombre de coccinelles présentes sur cette branche
	inline unsigned int getLadybugNumber() const;
	// Renvoie la Spline de la branche
	inline Spline const& getSpline() const;

	// Changer le nombre de coccinelles présentes sur cette branche
	inline void setLadybugNumber(unsigned int nb);
	// Changer le type de la branche
	inline void setType(Type t = RegularBranch);


	// Renvoie l’avancée réelle si l’avancée est pos relativement à la fleur f0
	inline float getPos(float pos, ID<Flower> f0) const;
	// Renvoie la position du point à l’avancée pos (entre 0 et 1),
	// en considérant firstFlower comme le point de départ
	inline sf::Vector2f eval(float pos, ID<Flower> firstFlower) const;
	// Renvoie la dérivée du point à l’avancée pos (entre 0 et 1),
	// en considérant firstFlower comme le point de départ
	sf::Vector2f evalDerivative(float pos, ID<Flower> firstFlower) const;

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
	inline Branch(HelpCreator hc);


	// Crée la SplineShape pour les fleurs f1 et f2
	static Spline createSpline(Flower& f1, Flower& f2);


	ID<Flower> mFirstFlower;
	ID<Flower> mSecondFlower;
	Type mType;
	Spline mSpline;
	unsigned int mLadybugNumber; // TODO Is this really important ?
};
