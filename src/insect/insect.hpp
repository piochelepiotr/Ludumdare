#pragma once
#include "behaviour.hpp"
#include <SFML/Graphics.hpp>

class Insect {
	public:
	// Nouvel insect sur l’arbre rt, apparaît sur spawnFlower, de vitesse speed
	Insect(RoseTree const& rt, ID<Flower> spawnFlower, float speed);

	// Renvoie l’ID de la branche de l’insecte (erreur si le chemin est fini)
	inline ID<Branch> getBranch() const;
	// Renvoie sa position sur cette branche (entre 0 et 1, avec 0 si au début)
	float getPos() const;
	// Renvoie la fleur sur laquelle était l’insecte
	inline ID<Flower> getPrevFlower() const;
	// true <=> l’insecte a atteint son objectif
	inline bool isObjectiveReached() const;

	// Renvoie sa position dans l’espace
	inline sf::Vector2f getPosition() const;

	// Dessin de l’insecte
	void draw(sf::RenderTarget& target, sf::Sprite sprite);

	protected:
	// L’insecte se déplace de dt
	void move(sf::Time dt);

	// Renvoie la prochaine fleur du chemin (erreur si le chemin est fini)
	inline ID<Flower> getNextFlower() const;
	// Renvoie la branche où est l’insecte (erreur si le chemin est fini)
	inline Branch const& getRealBranch() const;

	RoseTree const& mRoseTree; // Arbre sur lequel on est
	Path<Flower> mPath; // Chemin actuellement suivi
	float const mSpeed; // Vitesse de parcours des branches

	float mPos; // Position sur la branche actuelle (entre 0 et 1)
	sf::Vector2f mRealPosition; // Position réelle dans l’espace
	float mAngle; // Angle de l’insecte
};

class Aphid : public Insect {
	public:
	// Nouveau puceron sur l’arbre rt, à la fleur spawnFlower, et de type t
	Aphid(RoseTree const& rt, ID<Flower> spawnFlower, AphidBehaviour::Type t);
	// Bouge le puceron de dt
	inline void move(sf::Time dt);

	private:
	AphidBehaviour mBehaviour; // Son comportement, qui dicte son chemin
};

class LadyBug : public Insect {
	public:
	// Différents types pour différents comportements
	enum Type {RedLadybug, RedBlackLadybug, BlackLadybug};

	public:
	// Nouvelle Coccinelle sur l’arbre rt, fleur spawnFlower, de type t
	inline LadyBug(RoseTree const& rt, ID<Flower> spawnFlower, LadyBug::Type t);

	// Le type de coccinelle
	Type getType();
	// On definit un nouveau chemin de ronde pour la coccinelle
	void redefinePath(Path<Flower> newPath);

	void move(sf::Time dt);
	// void setBusy(bool bo) {busy = bo;};
	//sf::Time getBusyTime() { return busyTime; };
	
	// La coccinelle se régale avec aphid (ne détruit pas aphid)
	inline void eatAnAphid(Aphid& aphid);
	// true <=> La coccinelle mange, ne la dérangeons pas.
	inline bool isEating();
	// la coccinelle digère pendant le temps dt
	inline void decreaseEatingTime(sf::Time dt);

	private:
	Path<Flower> mDutyPath; // Chemin de ronde de la coccinelle
	sf::Time mEatingTime = sf::seconds(0); // Temps avant la fin de la digestion
	Type mType; // Type de coccinelle, i.e. son comportement
};

