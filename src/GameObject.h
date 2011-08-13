#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Renderable.h"
#include "Simulable.h"

/**
 * @brief
 * Game asset which knows how to draw itself and manage time changes
 * 
 * Renderable and simulable object of game, part of the game level
 * 
 * @see
 * Renderable | Simulable
 */
class GameObject : public Renderable, public Simulable {
	// TODO default collision detection
}

#endif