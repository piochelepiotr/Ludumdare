#include "rosetree/rosetree.hpp"
#include "rosetree/branch.hpp"
#include "rosetree/flower.hpp"

// Flowers

void RoseTree::removeFlower(ID<Flower> f)
{
	mFlowers.removeObj(f);
	auto branchs = mGraph.removeNode(f);
	for (ID<Branch> b : branchs)
		removeBranch(b);
}

// TODO These four should be inlined
Flower const& RoseTree::getFlower(ID<Flower> f) const
{ return mFlowers[f]; }
Flower const& RoseTree::operator [] (ID<Flower> f) const
{ return mFlowers[f]; }
Flower& RoseTree::getFlower(ID<Flower> f)
{ return mFlowers[f]; }
Flower& RoseTree::operator [] (ID<Flower> f)
{ return mFlowers[f]; }

// TODO These two should be inlined
/* // TODO not very good, I think
std::set<ID<Flower> > const RoseTree::getFlowers() const
{ return mGraph.getNodes(); }
*/
IDstaticmap<Flower> const& RoseTree::getFlowers() const
{
	return mFlowers;
}

std::set<ID<Flower> > const RoseTree::getNeighbours(ID<Flower> f) const
{ return mGraph.getNeighbours(f); }


// Branchs

ID<Branch> RoseTree::addBranch(ID<Flower> f1, ID<Flower> f2)
{
	auto id_branch = mBranchs.addObj(*this, f1, f2);
	return mGraph.addEdge(f1, f2, id_branch->first, id_branch->second.getLength());
}

void RoseTree::removeBranch(ID<Branch> b)
{
	mBranchs.removeObj(b);
	mGraph.removeEdge(b);
}

// TODO May be inlined
void RoseTree::removeBranch(ID<Flower> f1, ID<Flower> f2)
{ removeBranch(mGraph.getEdge(f1, f2)); }

// TODO To be inlined (maybe some of them)
Branch const& RoseTree::getBranch(ID<Branch> b) const
{ return mBranchs[b]; }
Branch const& RoseTree::getBranch(ID<Flower> f1, ID<Flower> f2) const
{ return mBranchs[getBranchID(f1, f2)]; }
Branch const& RoseTree::getBranch(std::pair<ID<Flower>, ID<Flower> > pair) const
{ return mBranchs[getBranchID(pair)]; }
Branch& RoseTree::getBranch(ID<Branch> b)
{ return mBranchs[b]; }
Branch& RoseTree::getBranch(ID<Flower> f1, ID<Flower> f2)
{ return mBranchs[getBranchID(f1, f2)]; }
Branch& RoseTree::getBranch(std::pair<ID<Flower>, ID<Flower> > pair)
{ return mBranchs[getBranchID(pair)]; }

// TODO Inline it
ID<Branch> RoseTree::getBranchID(ID<Flower> f1, ID<Flower> f2) const
{ return mGraph.getEdge(f1, f2); }
ID<Branch> RoseTree::getBranchID(std::pair<ID<Flower>, ID<Flower> > pair) const
{ return mGraph.getEdge(pair.first, pair.second); }


// Paths FIXME TODO

float RoseTree::getDist(ID<Flower> f1, ID<Flower> f2) const
{ return mGraph.getDist(f1, f2); }
void RoseTree::getPath(ID<Flower> f1, ID<Flower> f2, Path<Flower>& path) const
{ mGraph.getPath(path, f1, f2); }
void RoseTree::makeCyclic(Path<Flower>& path) const
{ mGraph.makeCyclic(path); }


// File interaction

void RoseTree::load(std::istream& is)
{
	// Avant tout, on vide ce qu’on a déjà
	mGraph.clear();
	mFlowers.clear();
	mBranchs.clear();

	std::string str;
	std::map<unsigned int, ID<Flower> > temporaryIDs;
	unsigned int currentID = 0;

	// On commence par ajouter les fleurs
	is >> str;
	if (str != "flowers")
		is.setstate(is.failbit);
	while (is && (is >> str, str != "branchs"))
	{
		sf::Vector2f v;
		std::string type;

		v.x = stof(str);
		is >> v.y >> type;
		temporaryIDs.insert(std::make_pair(currentID,
					addFlower(v, Flower::typeFromString(type))));
		currentID++;
	}
	std::cout << "In RoseTree::load(istream&): currentID = " << currentID << std::endl;

	// Puis on ajoute les branches
	if (str != "branchs")
		is.setstate(is.failbit);
	std::cout << "In RoseTree::load(istream&): Here i am" << std::endl;
	while (is)
	{
		unsigned int f1, f2;
		is >> f1 >> f2;
		addBranch(temporaryIDs.find(f1)->second, temporaryIDs.find(f2)->second);
	}
	std::cout << "In RoseTree::load(istream&): There i am" << std::endl;
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
		os << '\t' << id_flower.second.getPosition().x;
		os << id_flower.second.getPosition().y << '\n';
	}

	os << "branchs\n";
	for (auto& id_branch : mBranchs)
	{
		os << '\t' << temporaryIDs[id_branch.second.getFirstFlower()];
		os << temporaryIDs[id_branch.second.getSecondFlower()] << '\n';
	}
}
