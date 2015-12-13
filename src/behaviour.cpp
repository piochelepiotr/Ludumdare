#include "behaviour.hpp"

Behaviour::Behaviour(Behaviour::ID id, Node spawningNode, Graph* graph)
: mPath()
, mID(id)
{
    if (id == Behaviour::Offensive)
    {
        minLength = 100000000;
        for (auto stuff : graph)
        {
            Node::ID node = stuff.fs;
            if (node.getType() == Texture::ID::Flower && node.getType() == Texture::ID::LadyBugFlower)
            {
                Path path = graph->getPath(actualNode, node);
                float length = path.length();
                if (length < minLength)
                {
                    mPath = path;
                }
            }
        }
    }
    else
    {
        Branch::ID spawningBranch = graph->find(Node).get(0);
        mPath.addBranch(spawningNode, spawningBranch);

        Node newNode;

        if (spawningBranch.getFirstNode() =! spawningNode)
            Node newNode = spawningBranch.getFirstNode();
        else
            Node newNode = spawningBranch.getSecondNode();

        Node previousNode = spawningNode;

        while (newNode.getType() == Texture::ID::RegularNode)
        {
            Branch::ID newBranch = choice(id, newNode, previousNode, graph);
            mPath.addBranch(newNode,newBranch); // FIXME assurer l'identifiant, WARNING copie de branche
            previousNode = newNode;
            if (newBranch.getFirstNode() =! newNode)
                newNode =newBranch.getFirstNode();
            else
                newNode = newBranch.getSecondNode();
        }
    }
}


Branch::ID Behaviour::Choice(Behaviour::ID id, Node* actualNode, Node* previousNode, Graph* graph)
{
    if (id == Behaviour::Coward)
    {
        auto neighbours = graph->find(*actualNode);
        Branch::ID branchChosen = neighbours.get(0);
        for (Branch::ID branch: neighbours)
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
        Branch::ID branchChosen = neighbours.get(0);
        for (Branch::ID branch: neighbours)
        {
            if (!graph->isCulDeSac(branch) && branch->getFirstNode()!=previousNode && branch->getSecondNode()!=previousNode)
            {
                if (branch->getLength() < branchChosen->getLength())
                    branchChosen = branch;
            }
        }
        return branchChosen;
    }
}
