#pragma once
#include "ressourceholder.hpp"
//#include <SFML/Graphics.hpp>

namespace sf {
	class Font;
}

namespace Font
{
    enum ID {
		Text,
		Standard
	};
}

class FontHolder: public ResourceHolder<sf::Font, Font::ID>
{
    public:
        FontHolder() {};
};
