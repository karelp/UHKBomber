#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics/Sprite.hpp>
#include "GameObject.h"

/**
 * @brief
 * Tile is standard GameObject with Sprite instance (some image)
 * 
 * Tile contains information about image which should be draw on some surface.
 * 
 * @see
 * GameObject
 */
class Tile : public GameObject {
public:
	Tile(float x, float y, sf::Sprite &sprite) : GameObject(x, y, sprite.GetSize().x, sprite.GetSize().y), sprite(sprite) {};
	
	virtual void render(sf::RenderTarget& target, DeltaTime dt);
	
	sf::Sprite& getSprite();

private:
	sf::Sprite sprite;

};

#endif