#include "Tile.h"

void Tile::render(sf::RenderTarget& target, DeltaTime dt) 
{
	target.Draw(sprite);
}