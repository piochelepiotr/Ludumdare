#pragma once
#include "ressourceholder.hpp"
#include <SFML/Graphics.hpp>

namespace Texture
{
    enum ID {
	Branch
	, OffensiveLadybug
	, DefensiveLadybug
	, NormalLadybug
	, Aphid
	, Background
	, RegularFlower
	, AphidFlower
	, LadybugFlower
	, NodeFlower
	, None
    };
}

class TextureHolder: public ResourceHolder<sf::Texture, Texture::ID>
{
    public:
        TextureHolder() {};
};
