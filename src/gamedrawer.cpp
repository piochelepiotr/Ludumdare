#include "gamedrawer.hpp"
#include "gameworld.hpp"
#include "rosetree/branch.hpp"
#include "insect/insect.inl"
#include "gameworld.inl"

void GameDrawer::setSprite(sf::Sprite& sprite,
		sf::Texture const& texture,
		sf::IntRect textureRect,
		sf::Vector2f origin,
		sf::Vector2f scale,
		sf::Vector2f position,
		float rotation)
{
	sprite.setTexture(texture);
	if (textureRect != Rect())
		sprite.setTextureRect(textureRect);
	sprite.setOrigin(origin);
	sprite.setScale(scale);
	sprite.setPosition(position);
	sprite.setRotation(rotation);
}

sf::Transform GameDrawer::getTransform(Insect* insect)
{
	sf::Transform transform;
	transform.translate(insect->getPosition());
	transform.rotate(insect->getAngle() * 180.0f / 3.14159265f + 90.0f);
	return transform;
}


void GameDrawer::draw(sf::RenderTarget& target)
{
	// On commence par le fond d’écran si on est en jeu
	target.draw(mBackGround);


	// Puis on dessine le rosier

	// Les branches
	mBranchRenderer.draw(target);

	// Les fleurs
	for (auto& id_flower : mGameWorld.getFlowers())
	{
		auto& flower = id_flower.second;
		sf::Transform transform;
		transform.translate(flower.getPosition());
		target.draw(mFlowers[flower.getType()], transform);
	}

		
	// Ensuite viennent les insectes

	// Les coccinelles
	for (auto ldb : mGameWorld.getLadybugs())
		target.draw(mLadybugs[ldb->getType()], getTransform(ldb));

	// Les pucerons
	for (auto aphid : mGameWorld.getAphids())
		target.draw(mAphids, getTransform(aphid));


	// Puis enfin, on dessine l’interface

	// la barre de capacité
		auto total = mGameWorld.getTotalCapacity();
		auto current = mGameWorld.getRemainingCapacity();

		sf::RectangleShape ext(sf::Vector2f(24.f, total * 10.f + 4));
		ext.setPosition(8.f, 8.f);
		ext.setFillColor(sf::Color::Green);
		target.draw(ext, sf::RenderStates::Default);

		sf::RectangleShape used(sf::Vector2f(20.f, (total - current) * 10.f));
		used.setPosition(10.f, 10.f + current *10.f);
		used.setFillColor(sf::Color::Black);
		target.draw(used, sf::RenderStates::Default);
}

