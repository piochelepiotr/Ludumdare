#pragma once
#include <deque>

template <typename Node>
class Path
{
	public:
	// Crée un chemin avec un seul nœud
	Path(ID<Node> n);

	// Ajoute un nouveau nœud à la fin du chemin
	void addNode(ID<Node> n);
	// Insère un nouveau nœud au début du chemin
	void insertNode(ID<Node> n);

	// Renvoie le premier nœud du chemin
	ID<Node> getFirstNode() const;
	// Renvoie les deux premiers nœuds du chemin
	std::pair<ID<Node>, ID<Node> > getTwoFirstNodes() const;
	// Renvoie tous les nœuds parcourus par le chemin
	std::deque<ID<Node> > const& getNodes() const;

	// Renvoie le premier nœud et le supprime du chemin
	ID<Node> pop();
	// Enlève tous les nœuds jusqu’au nœud n (celui-ci n’est pas enlevé)
	void popUntil(ID<Node> n);
	// Enlève tous les nœuds du chemin, ne laisse que le nœud n0
	void reset(ID<Node> n0);
	// Vrai si le chemin n’a qu’un seul nœud.
	bool isEmpty() const;

	// Vrai si le chemin est cyclique.
	bool isCyclic() const;

	private:
	std::deque<ID<Node> > mPath;
};


// Définition des fonctions

template <typename Node>
Path<Node>::Path(ID<Node> n) : mPath(1, n)
{}

template <typename Node>
void Path<Node>::addNode(ID<Node> n)
{ mPath.push_back(n); }

template <typename Node>
void Path<Node>::insertNode(ID<Node> n)
{ mPath.push_front(n); }

template <typename Node>
ID<Node> Path<Node>::getFirstNode() const
{ return mPath.front(); }

template <typename Node>
std::pair<ID<Node>, ID<Node> > Path<Node>::getTwoFirstNodes() const
{
	auto it = mPath.begin();
	return std::make_pair(*it, *(it+1));
}

template <typename Node>
std::deque<ID<Node> > const& Path<Node>::getNodes() const
{ return mPath; }
/*
	std::set<ID<Node> > nodesSet;
	for (auto it : mPath)
		nodesSet.insert_hint(nodesSet.end(), *it);
	return nodesSet;
}
*/


template <typename Node>
ID<Node> Path<Node>::pop()
{
	ID<Node> front = mPath.front();
	mPath.pop_front();
	return front;
}


template <typename Node>
void Path<Node>::popUntil(ID<Node> n)
{
	while (mPath.front() != n)
		mPath.pop_front();
}

template <typename Node>
void Path<Node>::reset(ID<Node> n0)
{
	mPath = std::deque<ID<Node> >(1, n0);
}

template <typename Node>
bool Path<Node>::isEmpty() const
{
	return mPath.size() == 1;
}

template <typename Node>
bool Path<Node>::isCyclic() const
{
	return mPath.front() == mPath.back();
}
