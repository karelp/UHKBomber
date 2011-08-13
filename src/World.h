#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "GameObject.h"

/**
 * @brief
 * Contains and simulates the whole game world.
 * 
 * Contains level, players and all other simulable objects.
 * 
 * @remarks
 * Write remarks for World here.
 * 
 * @see
 * Separate items with the '|' character.
 */
class World : public GameObject  {
private:
	std::vector<GameObject *> m_allObjects;

public:
	void initialize();

	void simulate(DeltaTime dt);
	void render(sf::RenderTarget& target, DeltaTime dt);
};

#endif
