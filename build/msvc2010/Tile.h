#ifndef TILE_H
#define TILE_H

#include <SFML\Graphics\Sprite.hpp>

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
	sf::Sprite getSprite();

private:
	sf::Sprite sprite;

}

#endif