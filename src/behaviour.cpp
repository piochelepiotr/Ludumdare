#include "behaviour.hpp"

Behaviour::Behaviour(Behaviour::ID id, Node spawningNode, Graph* graph)
: mPath()
, mID(id)
{
    Branch spawningBranch = graph->find(Node).get(0);
    mPath.push_back((spawningNode, spawningBranch));

    if (spawningBranch.getFirtsNode() =! spawningNode)
        Node newNode = spwaningBranch.getFirstNode();
    else
        Node newNode = spwaningBranch.getSecondNode();
    Node previousNode = spwaningNode;

    while (newNode.getID = Texture::ID::RegularNode)
    {
        newBranch = choice(id, newNode, previousNode, graph);
        mPath.push_back((newNode,newBranch));
        previousNode = newNode;
        if (newBranch.getFirtsNode() =! newNode)
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
            if (!branch->IsCulDeSac() && branch->getFirstNode()!=previousNode && branch->getSecondNode()!=previousNode)
            {
                if (branch->getNumberLadyBug() < branchChosen->getLadyBug())
                    branchChosen = branch;
                if (branch->getNumberLadyBug() = branchChosen->getLadyBug() && graph->getLength(branch) < graph->getLength(branchChosen))
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
            if (!branch->IsCulDeSac() && branch->getFirstNode()!=previousNode && branch->getSecondNode()!=previousNode)
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
