#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "GameObject.h"
#include "Simulable.h"
#include "Renderable.h"
#include "Level.h"
#include "Player.h"

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
class World : public Simulable, public Renderable  {
private:
	std::vector<GameObject *> m_allObjects;

	Level m_level;

public:
	World() : m_level(42, 42) {} // TODO: just temporary

	void initialize();

	void simulate(DeltaTime dt);
	void render(sf::RenderTarget& target, DeltaTime dt);
};

#endif
