#pragma once
#include "ressourceholder.hpp"
#include <SFML/Graphics.hpp>

namespace Texture
{
    enum class ID {
	Branch
	, LeafBranch
	, AphidBranch
	, OffensiveLadyBug
	, DefensiveLadyBug
	, NormalLadyBug
	, Aphid
	, BackGround
	, RegularFlower
	, AphidFlower
	, LadybugFlower
	, None
    };
}

class TextureHolder: public ResourceHolder<sf::Texture, Texture::ID>
{
    public:
        TextureHolder() {};
};
