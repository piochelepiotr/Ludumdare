#pragma once
#include "ressourceholder.hpp"
#include <SFML/Graphics.hpp>

namespace Texture
{
    enum ID {Sol, Mur, Stone, HalfFloor0, HalfFloor1, HalfFloor2, HalfFloor3, GravityBloc0, GravityBloc1, GravityBloc2, GravityBloc3};
}

class TextureHolder: public ResourceHolder<sf::Texture, Texture::ID>
{
    public:
        TextureHolder();
};
