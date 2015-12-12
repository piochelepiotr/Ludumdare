#pragma once
#include "ressourceholder.hpp"
#include <SFML/Graphics.hpp>

namespace Font
{
    enum ID {Text};
}

class FontHolder: public ResourceHolder<sf::Font, Font::ID>
{
    public:
        FontHolder();
};
