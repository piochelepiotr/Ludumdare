#include "behaviour.hpp"
#include "graph/graph.hpp"
#include <iostream>

AphidBehaviour::AphidBehaviour(AphidBehaviour::ID id, Node::ID spawningNode, Graph const& graph)
: mPath()
, mID(id)
, mObjective(0.f,0.f)
{
    if (id == AphidBehaviour::Offensive)
    {
        float minLength = 100000000;
        for (auto& stuff : graph)
        {
            Node::ID node = stuff.first;
			Node const& graph_node = graph[node];
            if (graph_node.getType() == Texture::ID::Flower || graph_node.getType() == Texture::ID::LadyBugFlower)
            {
                Path path = graph.getPath(spawningNode, node);
                float length = path.length(graph);
                if (length < minLength)
                {
                    mPath = path;
                    mObjective = node;
                    minLength = length;
                }
            }
        }
    }
    else
    {
        Branch::ID spawningBranch = graph.getNeighbours(spawningNode).begin()->second; // FIXME s’il n’y a pas de voisins, c’est pas très bon…
        Branch graph_spawningBranch = graph[spawningBranch];
        mPath.addBranch(spawningNode, spawningBranch);
        Node::ID newNode(0.f, 0.f);
        if (!(graph_spawningBranch.getFirstNode() == spawningNode))
            newNode = graph_spawningBranch.getFirstNode();
        else
            newNode = graph_spawningBranch.getSecondNode();

		Node::ID previousNode = spawningNode;

        int j = 0;
        while (graph[newNode].getType() == Texture::ID::RegularNode && j<5)
        {
            Branch::ID newBranch = choice(id, newNode, previousNode, graph);
            mPath.addBranch(newNode, newBranch); // FIXME assurer l'identifiant, WARNING copie de branche // TODO C’est réglé, non ?
            previousNode = newNode;
            if (!(graph[newBranch].getFirstNode() == newNode))
			{
                newNode = graph[newBranch].getFirstNode();
			}
            else
			{
                newNode = graph[newBranch].getSecondNode();
			}
			j++;
        }
    }
}


Branch::ID AphidBehaviour::choice(AphidBehaviour::ID id, Node::ID actualNode, Node::ID previousNode, Graph const& graph)
{
    if (id == AphidBehaviour::Coward)
    {
        auto neighbours = graph.getNeighbours(actualNode);
        Branch::ID branchChosen = neighbours.begin()->second;
        Branch const* graph_branchChosen = graph.getBranch(branchChosen);
        for (auto& stuff: neighbours)
        {
            Branch::ID branch = stuff.second;
            Branch const* graph_branch = graph.getBranch(branch);
            if (!graph.isCulDeSac(branch) && graph_branch->getFirstNode() != previousNode && graph_branch->getSecondNode() != previousNode)
            {
				if (graph_branch->getNbLadyBug() < graph_branchChosen->getNbLadyBug())
					branchChosen = branch;
				if (graph_branch->getNbLadyBug() == graph_branchChosen->getNbLadyBug() && graph_branch->getLength() < graph_branchChosen->getLength())
				{
                    branchChosen = branch;
					graph_branchChosen = graph_branch;
				}
            }
        }
        return branchChosen;
    }
    else
    {
        auto neighbours = graph.getNeighbours(actualNode);
        Branch::ID branchChosen = neighbours.begin()->second;
        Branch const* graph_branchChosen = graph.getBranch(branchChosen);
        for (auto& stuff: neighbours)
        {
            Branch::ID branch = stuff.second;
            Branch const* graph_branch = graph.getBranch(branch);
            if (!graph.isCulDeSac(branch) && graph_branch->getFirstNode() != previousNode && graph_branch->getSecondNode()!=previousNode)
            {
                if (graph_branch->getLength() < graph_branchChosen->getLength())
				{
                    branchChosen = branch;
					graph_branchChosen = graph_branch;
				}
            }
        }
        return branchChosen;
    }
}
