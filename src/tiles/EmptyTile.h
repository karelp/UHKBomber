#ifndef EMPTYTILE_H
#define EMPTYTILE_H

#include "Tile.h"

class EmptyTile : public Tile {
public:
	EmptyTile(float x, float y, sf::Sprite &sprite) : Tile(x, y, sprite) {}

	void render(sf::RenderTarget& target, DeltaTime dt);
	void simulate(DeltaTime dt);
};

#endif