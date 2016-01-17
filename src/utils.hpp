#pragma once
#include <cmath>
#include <SFML/System/Vector2.hpp>

// Sf::Vector2f operations (most of them inlined…)

inline float squareNorm(sf::Vector2f u)
{
	return u.x * u.x + u.y * u.y;
}

inline float norm(sf::Vector2f u)
{
	return std::sqrt(squareNorm(u));
}

// /!\ It does not handle errors
inline sf::Vector2f normalize(sf::Vector2f u)
{
	return u / norm(u);
}
