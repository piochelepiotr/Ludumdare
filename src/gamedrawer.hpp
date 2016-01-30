#pragma once

#include "insect/insect.hpp"
#include "rosetree/flower.hpp"
#include "splinerenderer.hpp"

class GameWorld;

/** @class GameDrawer
 * @brief Dessine le gameworld auquel il est rattaché
 */
class GameDrawer
{
	using Texture = sf::Texture;
	using Vect = sf::Vector2f;
	using Rect = sf::IntRect;

	public:
	inline GameDrawer(GameWorld& gameWorld) :
		mGameWorld(gameWorld), mBranchRenderer(gameWorld) {};
	void draw(sf::RenderTarget& target);

	// Si textureRect n’est pas précisé, alors celui-ci s’adapte à la taille
	// de la texture.
	inline void setBackGround(Texture const& texture,
			Vect origin = Vect(), Vect scale = Vect(1, 1), Vect pos = Vect(),
			float rot = 0, Rect textureRect = Rect());
	inline void setFlower(Flower::Type type, Texture const& texture,
			Vect origin = Vect(), Vect scale = Vect(1, 1), Vect pos = Vect(),
			float rot = 0, Rect textureRect = Rect());
	inline void setLadybug(Ladybug::Type type, Texture const& texture,
			Vect origin = Vect(), Vect scale = Vect(1, 1), Vect pos = Vect(),
			float rot = 0, Rect textureRect = Rect());
	inline void setAphid(Texture const& texture,
			Vect origin = Vect(), Vect scale = Vect(1, 1), Vect pos = Vect(),
			float rot = 0, Rect textureRect = Rect());

	private:
	static void setSprite(sf::Sprite& sprite,
			Texture const& texture,
			Rect textureRect,
			Vect origin,
			Vect scale,
			Vect position,
			float rotation);

	static sf::Transform getTransform(Insect*);

	GameWorld const& mGameWorld;
	sf::Sprite mBackGround;
	sf::Sprite mFlowers[Flower::TypeNumber];
	sf::Sprite mLadybugs[Ladybug::TypeNumber];
	sf::Sprite mAphids;
	SplineRenderer mBranchRenderer;
};


void GameDrawer::setBackGround(Texture const& texture,
		Vect origin, Vect scale, Vect pos, float rot, Rect textureRect)
{ setSprite(mBackGround, texture, textureRect, origin, scale, pos, rot); }

void GameDrawer::setFlower(Flower::Type type, Texture const& texture,
		Vect origin, Vect scale, Vect pos, float rot, Rect textureRect)
{ setSprite(mFlowers[type], texture, textureRect, origin, scale, pos, rot); }

void GameDrawer::setLadybug(Ladybug::Type type, Texture const& texture,
		Vect origin, Vect scale, Vect pos, float rot, Rect textureRect)
{ setSprite(mLadybugs[type], texture, textureRect, origin, scale, pos, rot); }

void GameDrawer::setAphid(Texture const& texture,
		Vect origin, Vect scale, Vect pos, float rot, Rect textureRect)
{ setSprite(mAphids, texture, textureRect, origin, scale, pos, rot); }
