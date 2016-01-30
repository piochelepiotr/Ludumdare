#pragma once
#include "rosetree/graph.hpp"
#include "utils/idmanagement.hpp"

class Branch;
class Flower;

class RoseTree
{
	public:
	// Flowers
	template <typename... Args> inline ID<Flower> addFlower(Args&&... args);
	void removeFlower(ID<Flower> f);
	inline Flower const& getFlower(ID<Flower> f) const;
	inline Flower const& operator [] (ID<Flower> f) const;
	inline Flower& getFlower(ID<Flower> f);
	inline Flower& operator [] (ID<Flower> f);
	inline IDstaticmap<Flower> const& getFlowers() const;
	inline IDstaticmap<Flower>& getFlowers();
	inline std::set<ID<Flower> > const getNeighbours(ID<Flower> f) const;

	// Branchs
	// Renvoie noID si il y a déjà une telle branche
	ID<Branch> addBranch(ID<Flower> f1, ID<Flower> f2);
	void removeBranch(ID<Branch> b);
	inline void removeBranch(ID<Flower> f1, ID<Flower> f2);
	inline Branch const& getBranch(ID<Branch> b) const;
	inline Branch const& getBranch(ID<Flower> f1, ID<Flower> f2) const;
	inline Branch const& getBranch(std::pair<ID<Flower>,ID<Flower>> pair) const;
	inline Branch& getBranch(ID<Branch> b);
	inline Branch& getBranch(ID<Flower> f1, ID<Flower> f2);
	inline Branch& getBranch(std::pair<ID<Flower>, ID<Flower> > pair);
	inline ID<Branch> getBranchID(ID<Flower> f1, ID<Flower> f2) const;
	inline ID<Branch> getBranchID(std::pair<ID<Flower>, ID<Flower>> pair) const;
	inline IDstaticmap<Branch> const& getBranchs() const;

	// Paths
	// Renvoie la longueur entre f1 et f2
	inline float getDist(ID<Flower> f1, ID<Flower> f2) const;
	// Met le plus court chemin entre f1 et f2 dans path
	inline void getPath(ID<Flower> f1, ID<Flower> f2, Path<Flower>& path) const;
	// Met dans path le plus court chemin entre f1
	// et le plus proche nœud de [begin, end)
	template <typename Iterator>
	inline void getPathToCloserOf(Iterator begin, Iterator end,
				ID<Flower> f1, Path<Flower>& path) const;
	// Met dans path le plus court chemin entre f1 et
	// le plus proche nœud vérifiant p
	template <typename Pred>
	inline void getPathToCloserWith(ID<Flower> f1, Path<Flower>& path, Pred p) const;
	// Complète le chemin path pour qu’il soit cyclique.
	inline void makeCyclic(Path<Flower>& path) const;

	// File interaction
	void load(std::istream& is);
	void save(std::ostream& os) const;

	private:
	// Les fonctions en 'soft' font la même chose, mais sans interagir
	// avec le graphe (on suppose que l’ajout où la suppression dans le
	// graphe se fera autrement)
	template <typename... Args>
	inline ID<Flower> softAddFlower(Args&&... args);
	std::pair<ID<Branch>,float> softAddBranch(ID<Flower> f1, ID<Flower> f2); // /!\ suppose que la branche n’existe pas
	inline void softRemoveBranch(ID<Branch> b);

	PonderateGraph<Flower, Branch, float> mGraph;
	IDstaticmap<Flower> mFlowers;
	IDstaticmap<Branch> mBranchs;
};

