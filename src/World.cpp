#include "World.h"

void World::initialize()
{

}

void World::simulate(DeltaTime dt)
{
	for (auto it = m_allObjects.begin(); it != m_allObjects.end(); ++it)
		(*it)->simulate(dt);
}

void World::render(sf::RenderTarget& target, DeltaTime dt)
{
	for (auto it = m_allObjects.begin(); it != m_allObjects.end(); ++it)
		(*it)->render(target, dt);
}


