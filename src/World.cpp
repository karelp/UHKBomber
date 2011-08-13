#include "World.h"

void World::initialize()
{

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
		(*it)->render(target, dt);
}


