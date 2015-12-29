#include "utils.hpp"

/*
std::vector< std::string > stringSplit(std::string str, char c)
{
    std::vector<std::string>elements;
    std::string oneElement;
    int l = str.size();
    for(int i = 0; i < l; i++)
    {
	if(str[i] == c)
	{
	    elements.push_back(oneElement);
	    oneElement.clear();
	}
	else
	{
	    oneElement.push_back(str[i]);
	}
    }
    if(!oneElement.empty())
	elements.push_back(oneElement);
    return elements;
}

std::string concatenate(std::vector<std::string>elements ,char c)
{
    std::string str;
    int l = elements.size();
    for(int i = 0; i < l; i++)
    {
	str += elements[i];
	str += c;
    }
    return str;
}
*/
