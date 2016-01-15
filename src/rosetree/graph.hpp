#pragma once
#include <set>
#include "id.hpp"
#include <limits>


template <typename Node, typename Edge>
class Graph
{
	public:
		// Efface tout ce qu’il y a dans le graphe
		void clear();

		// Renvoie le nombre de nœuds dans le graphe
		inline std::size_t getNodeNumber() const;
		// Renvoie le nombre d’arêtes dans le graphe
		inline std::size_t getEdgeNumber() const;

		// Ajoute le nœud n dans le graphe et renvoie n
		ID<Node> addNode(ID<Node> n);
		// Enlève le nœud n, renvoie l’ID des branches qu’on a dû retirer
		std::set<ID<Edge> > removeNode(ID<Node> n);

/*		// Ajoute une arête dans entre n1 et n2 déjà existants, renvoie son ID
		ID<Edge> addEdge(ID<Node> n1, ID<Node> n2); */ // TODO ? Cette fonction est-elle vraiment utile ?…
		// Ajoute l’arête e entre n1 et n2, et renvoie e
		// (il ne faut pas que e soit déjà dans le graphe)
		ID<Edge> addEdge(ID<Node> n1, ID<Node> n2, ID<Edge> e);
		// Enlève l’arête entre n1 et n2
		void removeEdge(ID<Node> n1, ID<Node> n2);
		// Enlève l’arête e
		void removeEdge(ID<Edge> e);

		// Renvoie l’ensemble des nœuds du graphes
		std::set<ID<Node> > getNodes() const;
		// Renvoie l’ensemble de tous les voisins de n1
		std::set<ID<Node> > getNeighbours(ID<Node> n1) const;
		// Renvoie une table associative qui a un nœud n2 donne l’arête entre n1 et n2
		std::map<ID<Node>, ID<Edge> > const& getNeighboursMap(ID<Node> n1) const;
		std::map<ID<Node>, ID<Edge> >& getNeighboursMap(ID<Node> n1);
		std::map<ID<Node>, ID<Edge> > const& operator [] (ID<Node> n1) const;
		std::map<ID<Node>, ID<Edge> >& operator [] (ID<Node> n1);
		// Renvoie l’arête qui relie n1 et n2 (ou noID s’il n’y en a pas)
		ID<Edge> getEdge(ID<Node> n1, ID<Node> n2) const;
		// Renvoie les deux nœuds de l’arête e
		std::pair<ID<Node>, ID<Node>> getNodes(ID<Edge> e) const;

	protected:
		std::map<ID<Node>, std::map<ID<Node>, ID<Edge> > >  mNodesToEdge;
		std::map<ID<Edge>, std::pair<ID<Node>, ID<Node> > > mEdgeToNodes;

};

#include "rosetree/path.hpp"

// Graph qui contient aussi des distances pour chaque branche
template <typename Node, typename Edge, typename Dist = float>
class PonderateGraph : public Graph<Node, Edge>
{
	public:
		// Efface tout ce qu’il y a dans le graphe
		void clear();

		// Renvoie la distance du plus court entre les nœuds n1 et n2
		Dist getDist(ID<Node> n1, ID<Node> n2) const;
/*		// Renvoie la longueur de l’arête b
		Dist getLength(ID<Edge> b) const;*/ // TODO We don’t really need it…

		// Complête le chemin existant de manière à ce qu’il arrive à n2
		// avec le plus court chemin
		void completePath(Path<Node>& path, ID<Node> n2) const;
		// Met le plus court chemin entre n1 et n2 dans path
		void getPath(Path<Node>& path, ID<Node> n1, ID<Node> n2) const;
		// Complète le graphe pour qu’il soit cyclique
		void makeCyclic(Path<Node>& path) const;
		// Met dans path le plus court chemin entre n1
		// et le plus proche nœud de [begin, end)
		template <typename Iterator>
		void getPathToCloserOf(Iterator begin, Iterator end,
				ID<Node> n1, Path<Node>& path) const;
		// Met dans path le plus court chemin entre n1 et
		// le plus proche nœud vérifiant p
		template <typename Pred>
		void getPathToCloserWith(ID<Node> n1, Path<Node>& path,
				Pred p) const;

		// Ajoute le nœud n dans le graphe et renvoie n
		ID<Node> addNode(ID<Node> n);
		// Enlève le nœud n, renvoie l’ID des branches qu’on a dû retirer
		std::set<ID<Edge> > removeNode(ID<Node> n);
		// Ajoute l’arête e de longueur d entre n1 et n2, et renvoie e
		// (il ne faut pas que e soit déjà dans le graphe)
		ID<Edge> addEdge(ID<Node> n1, ID<Node> n2, ID<Edge> e) = delete;
		ID<Edge> addEdge(ID<Node> n1, ID<Node> n2, ID<Edge> e, Dist d);
		// Enlève l’arête entre n1 et n2
		void removeEdge(ID<Node> n1, ID<Node> n2);
		// Enlève l’arête e
		void removeEdge(ID<Edge> e);
	
	private:
		// Renvoie mDistances[n1, n2]
		std::pair<Dist, ID<Node> > const& getDistance(ID<Node> n1, ID<Node> n2) const;

		// Recalcule la matrice des distances avec Floyd-Warshall
		void rebuildDistances();

		// La table assocative qui à toute paire (n1, n2) de ID<Node>
		// associe une paire contenant :
		// - la distance du chemin le plus court entre ces deux nœuds
		// - le premier nœud du chemin a->b
		// Il y a des redondances car les parcours se font dans les deux sens
		std::map<ID<Node>, std::map<ID<Node>, std::pair<Dist, ID<Node> > > > mDistances;
		// La table associative qui ne contient que les distances
		// entre les nœuds qui sont reliés par une arête
		// Il y a des redondances car les parcours se font dans les deux sens
		// TODO En a-t-on vraiment besoin ?
		std::map<ID<Node>, std::map<ID<Node>, Dist> > mBasicDistances;
};





// Définition des fonctions


// Graph

template <typename Node, typename Edge>
void Graph<Node, Edge>::clear()
{
	mNodesToEdge.clear();
	mEdgeToNodes.clear();
}


template <typename Node, typename Edge>
std::size_t Graph<Node, Edge>::getNodeNumber() const
{ return mNodesToEdge.size(); }

template <typename Node, typename Edge>
std::size_t Graph<Node, Edge>::getEdgeNumber() const
{ return mEdgeToNodes.size(); }


template <typename Node, typename Edge>
ID<Node> Graph<Node, Edge>::addNode(ID<Node> n)
{
	return mNodesToEdge.insert(mNodesToEdge.end(),
			std::make_pair(n, std::map<ID<Node>, ID<Edge> >()))->first;
}

template <typename Node, typename Edge>
std::set<ID<Edge> > Graph<Node, Edge>::removeNode(ID<Node> n)
{
	auto const& neighbours = getNeighboursMap(n);
	std::set<ID<Edge> > deletedEdges;
	// Pour voisin n2 de n :
	// On supprime l’entrée de n parmi les voisins de n2,
	// et on supprime aussi l’entrée de la branche qui relie n1 et n2.
	for (auto neighbour_edge : neighbours)
	{
		getNeighboursMap(neighbour_edge.first).erase(n);
		mEdgeToNodes.erase(neighbour_edge.second);
		deletedEdges.insert(neighbour_edge.second);
	}
	mNodesToEdge.erase(n);
	return deletedEdges;

}


/*
template <typename Node, typename Edge>
ID<Edge> Graph<Node, Edge>::addEdge(ID<Node> n1, ID<Node> n2)
{
	// On commence par trouver le dernier ID des arêtes utilisé
	auto it = mEdgeToNodes.rbegin();
	ID<Edge> id = (it == mEdgeToNodes.rend() ? ID<Edge>(0) : (++it)->first);
	id++;
	// On peut ensuite ajouter le nouvel ID dans le bazar
	return addEdge(n1, n2, e);
}
*/ // TODO Cette fonction est-elle vraiment utile ?…

template <typename Node, typename Edge>
ID<Edge> Graph<Node, Edge>::addEdge(ID<Node> n1, ID<Node> n2, ID<Edge> e)
{
	getNeighboursMap(n1).insert(std::make_pair(n2, e));
	getNeighboursMap(n2).insert(std::make_pair(n1, e));
	return mEdgeToNodes.insert(mEdgeToNodes.end(), std::make_pair(e, std::make_pair(n1, n2)))->first;
}

template <typename Node, typename Edge>
void Graph<Node, Edge>::removeEdge(ID<Node> n1, ID<Node> n2)
{
	// On trouve un exemplaire de l’arête entre n1 et n2,
	// en gardant les résulats intermédiaires pour ne pas les recalculer
	auto& n1Neighbours = getNeighboursMap(n1);
	auto it_n2_edge = n1Neighbours.find(n2);
	// Puis on supprime tout
	mEdgeToNodes.erase(it_n2_edge->second);
	n1Neighbours.erase(it_n2_edge);
	getNeighboursMap(n2).erase(n2);
}

template <typename Node, typename Edge>
void Graph<Node, Edge>::removeEdge(ID<Edge> e)
{
	// On trouve les deux nœuds n1 et n2 qui correspondent à l’arête e,
	// en gardant les résulats intermédiaires pour ne pas les recalculer
	auto it_e_nodes = mEdgeToNodes.find(e);
	auto twoNodes = it_e_nodes->second;
	// Puis on supprime tout
	mEdgeToNodes.erase(it_e_nodes);
	getNeighboursMap(twoNodes.first).erase(twoNodes.second);
	getNeighboursMap(twoNodes.second).erase(twoNodes.first);
}


template <typename Node, typename Edge>
std::set<ID<Node> > Graph<Node, Edge>::getNodes() const
{
	std::set<ID<Node> > nodesSet;
	for (auto& node_neighbours : mNodesToEdge)
		nodesSet.insert(nodesSet.end(), node_neighbours.first);
	return nodesSet;
}

template <typename Node, typename Edge>
std::set<ID<Node> > Graph<Node, Edge>::getNeighbours(ID<Node> n1) const
{
	std::set<ID<Node> > neighboursSet;
	for (auto& neighbour_edge : getNeighboursMap(n1))
		neighboursSet.insert(neighboursSet.end(), neighbour_edge.first);
	return neighboursSet;
}

template <typename Node, typename Edge>
std::map<ID<Node>, ID<Edge> > const& Graph<Node, Edge>::getNeighboursMap(ID<Node> n1) const
{ return mNodesToEdge.find(n1)->second; }
template <typename Node, typename Edge>
std::map<ID<Node>, ID<Edge> >& Graph<Node, Edge>::getNeighboursMap(ID<Node> n1)
{ return mNodesToEdge.find(n1)->second; }
template <typename Node, typename Edge>
std::map<ID<Node>, ID<Edge> > const& Graph<Node, Edge>::operator [] (ID<Node> n1) const
{ return getNeighboursMap(n1); }
template <typename Node, typename Edge>
std::map<ID<Node>, ID<Edge> >& Graph<Node, Edge>::operator [] (ID<Node> n1)
{ return getNeighboursMap(n1); }


template <typename Node, typename Edge>
ID<Edge> Graph<Node, Edge>::getEdge(ID<Node> n1, ID<Node> n2) const
{ return getNeighboursMap(n1).find(n2)->second; }

template <typename Node, typename Edge>
std::pair<ID<Node>, ID<Node>> Graph<Node, Edge>::getNodes(ID<Edge> e) const
{ return mEdgeToNodes.find(e)->second; }



// PonderateGraph


template <typename Node, typename Edge, typename Dist>
void PonderateGraph<Node, Edge, Dist>::clear()
{
	Graph<Node, Edge>::clear();
	mBasicDistances.clear();
	mDistances.clear();
}


template <typename Node, typename Edge, typename Dist>
std::pair<Dist, ID<Node> > const& PonderateGraph<Node, Edge, Dist>::getDistance(ID<Node> n1, ID<Node> n2) const
{ return mDistances.find(n1)->second.find(n2)->second; }

template <typename Node, typename Edge, typename Dist>
Dist PonderateGraph<Node, Edge, Dist>::getDist(ID<Node> n1, ID<Node>n2) const
{ return getDistance(n1, n2).first; }


template <typename Node, typename Edge, typename Dist>
void PonderateGraph<Node, Edge, Dist>::completePath(Path<Node>& path, ID<Node> n2) const
{
	ID<Node> newNode(path.getNodes().back());
	while (newNode != n2)
	{
		newNode = getDistance(newNode, n2).second;
		path.addNode(newNode);
	}
	path.addNode(n2);
}
	
template <typename Node, typename Edge, typename Dist>
void PonderateGraph<Node, Edge, Dist>::getPath(Path<Node>& path, ID<Node> n1, ID<Node> n2) const
{
	path.reset(n1);
	completePath(path, n2);
}

template <typename Node, typename Edge, typename Dist>
template <typename Iterator>
void PonderateGraph<Node, Edge, Dist>::getPathToCloserOf(Iterator begin,
		Iterator end, ID<Node> n1, Path<Node>& path) const
{
	auto& distancesToN1 = *mDistances.find(n1);
	Iterator itMin = end;
	Dist distMin = std::numeric_limits<Dist>::infinity();
	for (Iterator it = begin ; it != end ; it++)
	{
		auto& pair = distancesToN1.find(*it)->second;
		if (pair.first < distMin)
		{
			distMin = pair.first;
			itMin = it;
		}
	}

	getPath(path, n1, itMin->second.second);
}

template <typename Node, typename Edge, typename Dist>
template <typename Pred>
void PonderateGraph<Node, Edge, Dist>::getPathToCloserWith(ID<Node> n1,
		Path<Node>& path, Pred p) const
{
	auto& distancesToN1 = *mDistances.find(n1);
	auto itMin = distancesToN1.end();
	Dist distMin = std::numeric_limits<Dist>::infinity();
	for (auto it = distancesToN1.begin()
			; it != distancesToN1.end() ; it++)
	{
		if (p(it->first))
		{
			auto& dist_node = it->second;
			if (dist_node.first < distMin)
			{
				distMin = dist_node.first;
				itMin = it;
			}
		}
	}

	getPath(path, n1, itMin->first);
}

template <typename Node, typename Edge, typename Dist>
void PonderateGraph<Node, Edge, Dist>::makeCyclic(Path<Node>& path) const
{
	completePath(path, path.getFirstNode());
}


template <typename Node, typename Edge, typename Dist>
ID<Node> PonderateGraph<Node, Edge, Dist>::addNode(ID<Node> n)
{
	auto id = Graph<Node, Edge>::addNode(n);
	rebuildDistances(); // TODO Pas besoin d’être aussi brutal…
	return id;
}

template <typename Node, typename Edge, typename Dist>
std::set<ID<Edge> > PonderateGraph<Node, Edge, Dist>::removeNode(ID<Node> n)
{
	// On enlève toutes les distances à n
	auto distancesToN = mBasicDistances.find(n);
	for (auto n2_d : distancesToN->second)
		mBasicDistances.find(n2_d.first)->second.erase(n);
	mBasicDistances.erase(distancesToN);
	// Puis on laisse papa terminer le bouleau
	auto set = Graph<Node, Edge>::removeNode(n);

	rebuildDistances(); // TODO Besoin d’être aussi brutal ?
	return set;
}


template <typename Node, typename Edge, typename Dist>
ID<Edge> PonderateGraph<Node, Edge, Dist>::addEdge(ID<Node> n1, ID<Node> n2, ID<Edge> e, Dist d)
{
	auto id = Graph<Node, Edge>::addEdge(n1, n2, e);
	mBasicDistances[n1].insert(std::make_pair(n2, d));
	mBasicDistances[n2].insert(std::make_pair(n1, d));
	rebuildDistances(); // TODO Même remarque…
	return id;
}

template <typename Node, typename Edge, typename Dist>
void PonderateGraph<Node, Edge, Dist>::removeEdge(ID<Node> n1, ID<Node> n2)
{
	Graph<Node, Edge>::removeEdge(n1, n2);
	mBasicDistances.find(n1)->second.erase(n2);
	mBasicDistances.find(n2)->second.erase(n1);
	rebuildDistances(); // TODO Idem
}

template <typename Node, typename Edge, typename Dist>
void PonderateGraph<Node, Edge, Dist>::removeEdge(ID<Edge> e)
{
	auto pair = Graph<Node, Edge>::getNodes(e);
	removeEdge(pair.first, pair.second);
}


template <typename Node, typename Edge, typename Dist>
void PonderateGraph<Node, Edge, Dist>::rebuildDistances()
{
	auto nodes = Graph<Node, Edge>::getNodes();

	// Commençons par initialiser la matrice des distances
	//   On la vide
	mDistances.clear();
	//   On la remplit avec des infinis
	std::map<ID<Node>, std::pair<Dist, ID<Node> > > line;
	for (ID<Node> node : nodes)
		line.insert(line.end(), std::make_pair(node, std::make_pair(std::numeric_limits<Dist>::infinity(), noID)));
	for (ID<Node> node : nodes)
		mDistances.insert(mDistances.end(), std::make_pair(node, line));
	//   On ajoute les valeurs déjà présentes de mBasicDistances
	for (auto& n1_n2_d : mBasicDistances)
	{
		auto& n1_map = mDistances.find(n1_n2_d.first)->second;
		for (auto& n2_d : n1_n2_d.second)
			n1_map.find(n2_d.first)->second =
			std::make_pair(n2_d.second, n2_d.first);
	}

	// Maintenant, un petit coup de Floyd-Warshall
	// (code optimisé, pas facile à comprendre…)
	for (auto& nodeK_map : mDistances)
	{
		for (auto& nodeI_map : mDistances)
		{
			auto const& value_I_K = nodeI_map.second.find(nodeK_map.first)->second;
			for (auto& nodeJ_val : nodeI_map.second)
			{
				auto& currentValue_I_J = nodeJ_val.second;
				auto const& value_K_J = nodeK_map.second.find(nodeJ_val.first)->second;
				float d = value_I_K.first + value_K_J.first;
				if (currentValue_I_J.first > d)
					currentValue_I_J = std::make_pair(d, value_I_K.second);
			}
		}
	}

	// Et c’est fini !
}
