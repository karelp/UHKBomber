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
public:
	GameObject(float x, float y, float width = 1, float height = 1) : 
	  m_x(x), m_y(y), m_width(width), m_height(height) 
	  {}

	virtual bool checkCollision(GameObject& other) = 0;
	virtual bool acceptCollision(GameObject& oth) = 0;

protected:
	float m_x, m_y, m_width, m_height;

};

#endif