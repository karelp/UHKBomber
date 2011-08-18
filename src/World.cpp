#include "World.h"

void World::initialize()
{
	// TODO remove (just for testing purposes)
	static sf::Image image = sf::Image();
	image.LoadFromFile("data/tempsprite.png");
	static sf::Sprite sprite = sf::Sprite(image);

	static Player player = Player(2 * LEVEL_TILE_WIDTH, 3 * LEVEL_TILE_HEIGHT, LEVEL_TILE_WIDTH, LEVEL_TILE_HEIGHT, &sprite);

	m_allObjects.push_back(&player);
}

void World::simulate(DeltaTime dt)
{
	m_level.simulate(dt);
	for (auto it = m_allObjects.begin(); it != m_allObjects.end(); ++it)
		(*it)->simulate(dt);
}

void World::render(sf::RenderTarget& target, DeltaTime dt)
{
	m_level.render(target, dt);
	for (auto it = m_allObjects.begin(); it != m_allObjects.end(); ++it)
	{
		(*it)->render(target, dt);
		std::cout << typeid(**it).name() << std::endl;
	}
}


