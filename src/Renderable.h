#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "FPS.h"
#include <SFML/Graphics.hpp>

/**
 * @brief
 * Interface representing anything that can be rendered in the game.
 * 
 * Any game object that paints something on the game screen implements this.
 */
class Renderable  {
public:
	/**
	 * @brief
	 * Renders the game object in the given render target.
	 * 
	 * @param target
	 * The render target for the object to be rendered to.
	 * 
	 * @param dt
	 * Delta time of last frame.
	 * 
	 * Performs rendering of the object at the given surface.
	 * The surface can be a window, buffer or anything that implements
	 * sf::RenderTarget.
	 */
	virtual void render(sf::RenderTarget& target, DeltaTime dt) = 0;
};

#endif
