#pragma once
#include <SFML/System.hpp>
#include <string>


class Flower
{
	public:
	enum Type {
		RegularFlower,
		AphidFlower,
		LadybugFlower,
		Node,
		TypeEnumSize // Permet de connaître la taille de cette enum
	};

	//Flower() = delete;
	Flower(sf::Vector2f position, Type type);

	// Renvoie le type de fleur
	Type getType() const;
	// Le type de la fleur devient t
	void setType(Type t);
	// Passe au type suivant, et renvoie le nouveau type
	Type nextType();

	// Fait perdre un point à la fleur, renvoie false si elle n’a plus de vie
	bool loseOnePoint();

	// Renvoie la position de la fleur
	sf::Vector2f getPosition() const;

	// Renvoie la dérivée des splines en ce point.
	sf::Vector2f getDerivative() const;
	// Renvoie la dérivée des splines en ce point.
	// Si elle n’est pas encore définie, alors elle prend la valeur deriv
	sf::Vector2f initDerivative(sf::Vector2f deriv);

	// TODO Peut-être pas une bonne idée…
	void setTimeLeft(sf::Time t);
	// Update TODO is that a good idea ?
	// Renvoie true si la fleur peut lâcher un insecte, ou autre événement.
	bool update(sf::Time dt);

	// Transforme une fleur quelconque en un nœud simple, comme les autres.
	void becomeNode();

	private:
	sf::Vector2f mPosition;
	sf::Vector2f mDerivative;
	Type mType;
	int mLife;
	sf::Time mTimeLeft;
};


std::ostream& operator<<(std::ostream& os, Flower::Type const& type);
std::istream& operator>>(std::istream& is, Flower::Type& type);
