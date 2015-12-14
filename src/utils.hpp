#pragma once
#include <iostream>
#include <vector>

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