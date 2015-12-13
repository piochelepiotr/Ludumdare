#pragma once
#include "ressourceholder.hpp"
#include <SFML/Graphics.hpp>

namespace Texture
{
    enum ID {
	Branch
	, LeafBranch
	, AphidBranch
	, OffensiveLadyBug
	, DefensiveLadyBug
	, NormalLadyBug
	, Aphid
	, BackGround
	, RegularNode
	, Flower
	, LadyBugFlower
	, SemperFlower
    };
}

class TextureHolder: public ResourceHolder<sf::Texture, Texture::ID>
{
    public:
        TextureHolder();
};
