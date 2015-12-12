#include "behaviour.hpp"

Behaviour::Behaviour(Behaviour::ID id, Node spawningNode, Graph* graph)
: mPath()
, mID(id)
{
    Branch& spawningBranch = graph->find(Node).get(0);
    mPath.push_back((spawningNode, spawningBranch));

	Node newNode;
	
    if (spawningBranch.getFirstNode() =! spawningNode)
        Node newNode = spawningBranch.getFirstNode();
    else
        Node newNode = spawningBranch.getSecondNode();
    Node previousNode = spawningNode;

    while (newNode.getType() == Texture::ID::RegularNode)
    {
        Branch& newBranch = choice(id, newNode, previousNode, graph);
        mPath.push_back((newNode,newBranch)); // FIXME assurer l'identifiant, WARNING copie de branche
        previousNode = newNode;
        if (newBranch.getFirstNode() =! newNode)
            newNode =newBranch.getFirstNode();
        else
            newNode = newBranch.getSecondNode();
    }
}


Branch Behaviour::Choice(Behaviour::ID id, Node* actualNode, Node* previousNode, Graph* graph)
{
    if (id == Behaviour::Coward)
    {
        auto neighbours = graph->find(*actualNode);
        Branch branchChosen = neighbours.get(0);
        for (Branch* branch: neighbours)
        {
            if (!graph->isCulDeSac(branch) && branch->getFirstNode()!=previousNode && branch->getSecondNode()!=previousNode)
            {
                if (branch->getNbLadyBug() < branchChosen->getLadyBug())
                    branchChosen = branch;
                if (branch->getNbLadyBug() == branchChosen->getLadyBug() && branch->getLength() < branchChosen.getLength())
                    branchChosen = branch;
            }
        }
        return branchChosen;
    }

    if (id == Behaviour::Dumb)
    {
        auto neighbours = graph->find(*actualNode);
        Branch branchChosen = neighbours.get(0);
        for (Branch* branch: neighbours)
        {
            if (!graph->isCulDeSac(branch) && branch->getFirstNode()!=previousNode && branch->getSecondNode()!=previousNode)
            {
                if (branch->getLength() < branchChosen->getLength())
                    branchChosen = branch;
            }
        }
        return branchChosen;
    }

    if (id == Behaviour::Offensive)
    {

    }
}
