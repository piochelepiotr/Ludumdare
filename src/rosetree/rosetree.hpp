#pragma once
#include "rosetree/graph.hpp"

class Branch;
class Flower;

class RoseTree
{
	public:
		// Flowers
		template <typename... Args> ID<Flower> addFlower(Args&&... args);
		void removeFlower(ID<Flower> f);
		Flower const& getFlower(ID<Flower> f) const;
		Flower const& operator [] (ID<Flower> f) const;
		Flower& getFlower(ID<Flower> f);
		Flower& operator [] (ID<Flower> f);
		IDstaticmap<Flower> const& getFlowers() const;
		IDstaticmap<Flower>& getFlowers();
		std::set<ID<Flower> > const getNeighbours(ID<Flower> f) const;

		// Branchs
		ID<Branch> addBranch(ID<Flower> f1, ID<Flower> f2);
		void removeBranch(ID<Branch> b);
		void removeBranch(ID<Flower> f1, ID<Flower> f2);
		Branch const& getBranch(ID<Branch> b) const;
		Branch const& getBranch(ID<Flower> f1, ID<Flower> f2) const;
		Branch const& getBranch(std::pair<ID<Flower>, ID<Flower> > pair) const;
		Branch& getBranch(ID<Branch> b);
		Branch& getBranch(ID<Flower> f1, ID<Flower> f2);
		Branch& getBranch(std::pair<ID<Flower>, ID<Flower> > pair);
		ID<Branch> getBranchID(ID<Flower> f1, ID<Flower> f2) const;
		ID<Branch> getBranchID(std::pair<ID<Flower>, ID<Flower> > pair) const;
		IDstaticmap<Branch> const& getBranchs() const;

		// Paths
		// Renvoie la longueur entre f1 et f2
		float getDist(ID<Flower> f1, ID<Flower> f2) const;
		// Met le plus court chemin entre f1 et f2 dans path
		void getPath(ID<Flower> f1, ID<Flower> f2, Path<Flower>& path) const;
		// Met dans path le plus court chemin entre f1
		// et le plus proche nœud de [begin, end)
		template <typename Iterator>
		void getPathToCloserOf(Iterator begin, Iterator end,
				ID<Flower> f1, Path<Flower>& path) const;
		// Met dans path le plus court chemin entre f1 et
		// le plus proche nœud vérifiant p
		template <typename Pred>
		void getPathToCloserWith(ID<Flower> f1, Path<Flower>& path, Pred p) const;
		// Complète le chemin path pour qu’il soit cyclique.
		void makeCyclic(Path<Flower>& path) const;

		// File interaction
		void load(std::istream& is);
		void save(std::ostream& os) const;

		// Drawing
//		void draw (sf::RenderTarget& ,sf::RenderStates) const;

	private:
		// Supprime une branche qui est déja supprimée dans le graphe
		void softRemoveBranch(ID<Branch> b);

		PonderateGraph<Flower, Branch, float> mGraph;
		IDstaticmap<Flower> mFlowers;
		IDstaticmap<Branch> mBranchs;
};


// Functions définitions

template <typename... Args>
ID<Flower> RoseTree::addFlower(Args&&... args)
{
	return mGraph.addNode(mFlowers.addObj(args...)->first);
}

template <typename Iterator>
void RoseTree::getPathToCloserOf(Iterator begin, Iterator end, ID<Flower> f1, Path<Flower>& path) const
{ mGraph.getPathToCloserOf(begin, end, f1, path); }

template <typename Pred>
void RoseTree::getPathToCloserWith(ID<Flower> f1, Path<Flower>& path, Pred p) const
{ mGraph.getPathToCloserWith(f1, path, p); }
