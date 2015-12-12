#include "behaviour.hpp"

Behaviour::Behaviour(Behaviour::ID id, Node* spawningNode, Graph* graph)
: mPath()
, mID(id)
{
    Branch *spawningBranch = graph->find(*Node).get(0);
    mPath.push_back(spawningNode);

    if (spawningBranch->getFirtsNode() =! spawningNode)
        Node newNode = spwaningBranch.getFirstNode();
    else
        Node newNode = spwaningBranch.getSecondNode();
    Node* previousNode = spwaningNode;

    while (newNode.getID = Texture::ID::RegularNode)
    {
        mPath.push_back(newNode);
        newNode = choice(id, newNode, spwaningNode, graph);
    }
}


Node Behaviour::Choice(Behaviour::ID id, Node* actualNode, Node* previousNode, Graph* graph)
{
    if (id == Behaviour::Coward)
    {
        auto neighbours = graph->find(*actualNode);
        Branch* branchChosen = neighbours.get(0);
        for (Branch* branch: neighbours)
        {
            if (!branch->IsCulDeSac() && branch->getFirstNode()!=previousNode && branch->getSecondNode()!=previousNode)
            {
                if (branch->getNumberLadyBug() < branchChosen->getLadyBug())
                    branchChosen = branch;
                if (branch->getNumberLadyBug() = branchChosen->getLadyBug() && branch->getLength() < branchChosen->getLength())
                    branchChosen = branch;
            }
        }
    }

    if (id == Behaviour::Dumb)
    {
        auto neighbours = graph->find(*actualNode);
        Branch* branchChosen = neighbours.get(0);
        for (Branch* branch: neighbours)
        {
            if (!branch->IsCulDeSac() && branch->getFirstNode()!=previousNode && branch->getSecondNode()!=previousNode)
            {
                if (branch->getLength() < branchChosen->getLength())
                    branchChosen = branch;
            }
        }
    }

    if (id == Behaviour::Offensive)
    {

    }
}
