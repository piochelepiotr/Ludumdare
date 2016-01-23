#include "rosetree/rosetree.inl"
#include <istream>

// Flowers

void RoseTree::removeFlower(ID<Flower> f)
{
	//std::cout << "RoseTree::removeFlower" << std::endl;
	mFlowers.removeObj(f);
	auto branchsToRemove = mGraph.removeNode(f);
	for (ID<Branch> b : branchsToRemove)
		softRemoveBranch(b);
}

// Branchs

std::pair<ID<Branch>, float> RoseTree::softAddBranch(ID<Flower> f1, ID<Flower> f2)
{
	auto id_branch = mBranchs.addObj(f1, f2, Branch::RegularBranch, *this);
	return std::make_pair(id_branch->first, id_branch->second.getLength());
}

ID<Branch> RoseTree::addBranch(ID<Flower> f1, ID<Flower> f2)
{
	if (mGraph.getEdge(f1, f2)) // Elle existe déjà
		return noID;
	else
	{
		auto id_dist = softAddBranch(f1, f2);
		return mGraph.addEdge(f1, f2, id_dist.first, id_dist.second);
	}
}

void RoseTree::removeBranch(ID<Branch> b)
{
	mBranchs.removeObj(b);
	mGraph.removeEdge(b);
}


// File interaction

void RoseTree::load(std::istream& is)
{
	// Avant tout, on vide ce qu’on a déjà
	mGraph.clear();
	mFlowers.clear();
	mBranchs.clear();

	std::string str;
	std::vector<ID<Flower> > temporaryIDs;
	std::vector<std::pair<std::pair<ID<Flower>, ID<Flower>>, std::pair<ID<Branch>, float>>> allBranchs; // Ceci va nous permettre d’ajouter tout au graphe à la fin

	// On commence par ajouter les fleurs
	is >> str;
	if (str != "flowers")
		is.setstate(is.failbit);
	while (is && (is >> str, str != "branchs"))
	{
		sf::Vector2f v;
		Flower::Type type;

		v.x = stof(str);
		is >> v.y >> type;
		temporaryIDs.push_back(softAddFlower(v, type));
	}

	// Puis on ajoute les branches
	if (str != "branchs")
		is.setstate(is.failbit);
	while (is >> str && is)
	{
		unsigned int f1, f2;
		f1 = stoul(str);
		is >> f2;
		auto id_weight = softAddBranch(temporaryIDs[f1], temporaryIDs[f2]);
		allBranchs.push_back(std::make_pair(std::make_pair(temporaryIDs[f1], temporaryIDs[f2]), id_weight));
	}

	// Enfin, on ajoute tout ça au graphe
	mGraph.addNodesEdges(temporaryIDs.begin(), temporaryIDs.end(),
		allBranchs.begin(), allBranchs.end());
}

void RoseTree::save(std::ostream& os) const
{
	std::map<ID<Flower>, unsigned int> temporaryIDs;
	unsigned int currentID = 0;

	os << "flowers\n";
	for (auto& id_flower : mFlowers)
	{
		temporaryIDs.insert(temporaryIDs.end(),
				std::make_pair(id_flower.first, currentID));
		currentID++;
		os << '\t' << id_flower.second.getPosition().x << ' ';
		os << id_flower.second.getPosition().y << ' ';
		os << id_flower.second.getType() << std::endl;
	}

	os << "branchs\n";
	for (auto& id_branch : mBranchs)
	{
		os << '\t' << temporaryIDs[id_branch.second.getFirstFlower()] << ' ';
		os << temporaryIDs[id_branch.second.getSecondFlower()] << '\n';
	}
}
