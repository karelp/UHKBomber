#ifndef SIMULABLE_H
#define SIMULABLE_H

#include "FPS.h"

/**
 * @brief
 * Interface for any object that can be updated in the game.
 * 
 * If an object can move or interact in the game and needs to
 * be updated every frame, it must implement this interface.
 */
class Simulable  {
public:
	/**
	 * @brief
	 * The method that performs the actual simulation (movement, ...)
	 * 
	 * @param dt
	 * Delta time since last simulation.
	 * 
	 * The object performs all the simulation here, including movement, collision
	 * checks etc.
	 */
	virtual void simulate(DeltaTime dt) = 0;
};

#endif
