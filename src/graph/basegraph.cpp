#include "basegraph.hpp"

BaseGraph::BaseGraph(std::string name)
{
    mGraph.charge(name);
}

BaseGraph::BaseGraph()
{

}

Graph BaseGraph::makeGraph()
{
    
}


/***
 * pour ajouter un node à g, il faut que toutes les
 * dépendances de ce node soient satisfaitent
 * et que ce node ne soit pas deja dans g
 * 
 */
Node::ID BaseGraph::nextNode(Graph &g)
{
    std::vector<Node::ID>gNodes = g.getNodes();
    std::vector<Node::ID>nodesDependFree = mGraph.nodesDependFree(g);
    for(auto node : nodesDependFree)
    {
	if(!contains<Node::ID>(gNodes,node))
	{
	    return node;
	}
    }
    Node::ID node;
    node.type = Texture::ID::None;
    return node;
}