#pragma once
#include "rosetree/rosetree.hpp"
#include "rosetree/branch.hpp"
#include "rosetree/flower.hpp"

// Inline functions for rosetree/rostree.hpp

// Flowers

template <typename... Args>
ID<Flower> RoseTree::addFlower(Args&&... args)
{ return mGraph.addNode(softAddFlower(args...)); }
template <typename...Args>
ID<Flower> RoseTree::softAddFlower(Args&&... args)
{ return mFlowers.addObj(args...)->first; }

Flower const& RoseTree::getFlower(ID<Flower> f) const
{ return mFlowers[f]; }
Flower const& RoseTree::operator [] (ID<Flower> f) const
{ return mFlowers[f]; }
Flower& RoseTree::getFlower(ID<Flower> f)
{ return mFlowers[f]; }
Flower& RoseTree::operator [] (ID<Flower> f)
{ return mFlowers[f]; }

IDstaticmap<Flower> const& RoseTree::getFlowers() const
{ return mFlowers; }
IDstaticmap<Flower>& RoseTree::getFlowers()
{ return mFlowers; }
std::set<ID<Flower> > const RoseTree::getNeighbours(ID<Flower> f) const
{ return mGraph.getNeighbours(f); }


// Branchs

void RoseTree::removeBranch(ID<Flower> f1, ID<Flower> f2)
{ removeBranch(mGraph.getEdge(f1, f2)); }
void RoseTree::softRemoveBranch(ID<Branch> b)
{ mBranchs.removeObj(b); }

Branch const& RoseTree::getBranch(ID<Branch> b) const
{ return mBranchs[b]; }
Branch const& RoseTree::getBranch(ID<Flower> f1, ID<Flower> f2) const
{ return mBranchs[getBranchID(f1, f2)]; }
Branch const& RoseTree::getBranch(std::pair<ID<Flower>, ID<Flower> > pair) const
{ return getBranch(pair.first, pair.second); }
Branch& RoseTree::getBranch(ID<Branch> b)
{ return mBranchs[b]; }
Branch& RoseTree::getBranch(ID<Flower> f1, ID<Flower> f2)
{ return mBranchs[getBranchID(f1, f2)]; }
Branch& RoseTree::getBranch(std::pair<ID<Flower>, ID<Flower> > pair)
{ return getBranch(pair.first, pair.second); }

ID<Branch> RoseTree::getBranchID(ID<Flower> f1, ID<Flower> f2) const
{ return mGraph.getEdge(f1, f2); }
ID<Branch> RoseTree::getBranchID(std::pair<ID<Flower>, ID<Flower> > pair) const
{ return mGraph.getEdge(pair.first, pair.second); }

IDstaticmap<Branch> const& RoseTree::getBranchs() const
{ return mBranchs; }


// Path

float RoseTree::getDist(ID<Flower> f1, ID<Flower> f2) const
{ return mGraph.getDist(f1, f2); }
void RoseTree::getPath(ID<Flower> f1, ID<Flower> f2, Path<Flower>& path) const
{ mGraph.getPath(path, f1, f2); }

template <typename Iterator>
void RoseTree::getPathToCloserOf(Iterator begin, Iterator end, ID<Flower> f1, Path<Flower>& path) const
{ mGraph.getPathToCloserOf(begin, end, f1, path); }
template <typename Pred>
void RoseTree::getPathToCloserWith(ID<Flower> f1, Path<Flower>& path, Pred p) const
{ mGraph.getPathToCloserWith(f1, path, p); }

void RoseTree::makeCyclic(Path<Flower>& path) const
{ mGraph.makeCyclic(path); }
