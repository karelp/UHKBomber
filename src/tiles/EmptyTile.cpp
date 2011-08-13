#include "EmptyTile.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Color.hpp>

void EmptyTile::render(sf::RenderTarget& target, DeltaTime dt) 
{
	sf::Shape rect = sf::Shape::Rectangle(m_x, m_y, m_width, m_height, sf::Color::Green);
	target.Draw(rect);
}

void EmptyTile::simulate(DeltaTime dt)
{
	// no necessary stuff here to do
}