#pragma once
#include <string>
#include <vector>
#include <SFML/System.hpp>

std::vector<std::string>stringSplit(std::string str,char c);
std::string concatenate(std::vector<std::string>elements,char c);

template<typename T>
int findIndex(std::vector<T> vector, T element) {
    int n = vector.size();
    for(int i = 0; i < n; i++)
    {
	if(vector[i] == element)
	    return i;
    }
    return -1;
}

template<typename T>
bool contains(std::vector<T> vect, T element)
{
    for(auto x : vect)
    {
	if(x == element)
	    return true;
    }
    return false;
}

inline float squareNorm(sf::Vector2f u)
{
	return u.x * u.x + u.y * u.y;
}

inline float norm(sf::Vector2f u)
{
	return std::sqrt(squareNorm(u));
}
