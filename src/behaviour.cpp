#include "behaviour.hpp"

Behaviour::Behaviour(Behaviour::ID id, Node spawningNode, Graph* graph)
: mPath()
, mID(id)
{
    if (id == Behaviour::Offensive)
    {
        float minLength = 100000000;
        for (auto stuff : *graph)
        {
            Node::ID node = stuff.first;
            if (node.type == Texture::ID::Flower && node.type == Texture::ID::LadyBugFlower)
            {
                Path path = graph->getPath(spawningNode, node);
                float length = path.length(graph);
                if (length < minLength)
                {
                    mPath = path;
                }
            }
        }
    }
    else
    {
        Branch::ID spawningBranch = graph->getNeighbour(spawningNode).begin()->second;
        mPath.addBranch(spawningNode, spawningBranch);
        Branch* realSpawningBranch = graph->getBranch(spawningBranch);
        Node::ID newNode(0.f, 0.f);
        if (!(realSpawningBranch->getFirstNode() == spawningNode))
            newNode = realSpawningBranch->getFirstNode();
        else
            newNode = realSpawningBranch->getSecondNode();

        Node previousNode = spawningNode;

        while (newNode.type == Texture::ID::RegularNode)
        {
            Branch::ID newBranch = choice(id, newNode, previousNode, graph);
            mPath.addBranch(newNode,newBranch); // FIXME assurer l'identifiant, WARNING copie de branche
            previousNode = newNode;
            Branch* realNewBranch = graph->getBranch(newBranch);
            if (!(realNewBranch->getFirstNode() == newNode))
                newNode =realNewBranch->getFirstNode();
            else
                newNode = realNewBranch->getSecondNode();
        }
    }
}

Path Behaviour::getPath() {
  return mPath;
}


Branch::ID Behaviour::choice(Behaviour::ID id, Node::ID actualNode, Node::ID previousNode, Graph* graph)
{
    if (id == Behaviour::Coward)
    {
        auto neighbours = graph->getNeighbour(actualNode);
        Branch::ID branchChosen = neighbours.begin()->second;
        Branch* realBranchChosen = (*graph)[branchChosen];
        for (auto stuff: neighbours)
        {
            Branch::ID branch = stuff.second;
            Branch* realBranch = graph->getBranch(branch);
            if (!graph->isCulDeSac(branch) && !(realBranch->getFirstNode()==previousNode) && !(realBranch->getSecondNode()==previousNode))
            {
                if (realBranch->getNbLadyBug() < realBranchChosen->getNbLadyBug())
                    branchChosen = branch;
            if (realBranch->getNbLadyBug() == realBranchChosen->getNbLadyBug() && realBranch->getLength() < realBranchChosen->getLength())
                    branchChosen = branch;
            }
        }
        return branchChosen;
    }
    else
    {
        auto neighbours = graph->getNeighbour(actualNode);
        Branch::ID branchChosen = neighbours.begin()->second;
        Branch* realBranchChosen = (*graph)[branchChosen];
        for (auto stuff: neighbours)
        {
            Branch::ID branch = stuff.second;
            Branch* realBranch = (*graph)[branch];
            if (!graph->isCulDeSac(branch) && !(realBranch->getFirstNode()==previousNode) && !(realBranch->getSecondNode()==previousNode))
            {
                if (realBranch->getLength() < realBranchChosen->getLength())
                    branchChosen = branch;
            }
        }
        return branchChosen;
    }
}
