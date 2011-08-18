#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics/Sprite.hpp>
#include "CollidableObject.h"

/**
 * @brief
 * Tile is standard GameObject with Sprite instance (some image)
 * 
 * Tile contains information about image which should be draw on some surface.
 * 
 * @see
 * CollidableObject
 */
class Tile : public CollidableObject<Tile> {
public:
	Tile(float x, float y, sf::Sprite &sprite);
	
	virtual void render(sf::RenderTarget& target, DeltaTime dt);
	
	sf::Sprite& getSprite();

private:
	sf::Sprite sprite;
};

#endif