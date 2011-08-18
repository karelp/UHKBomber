#include "Tile.h"
#include "Level.h"

Tile::Tile(float x, float y, sf::Sprite &sprite) : CollidableObject<Tile>(x, y, sprite.GetSize().x, sprite.GetSize().y) 
{
	sprite.SetPosition(x * LEVEL_TILE_WIDTH, y * LEVEL_TILE_HEIGHT);
}

void Tile::render(sf::RenderTarget& target, DeltaTime dt) 
{
	target.Draw(sprite);
}