#ifndef COLLIDABLEOBJECT_H
#define COLLIDABLEOBJECT_H

#include "GameObject.h"

template <typename Derived>
class CollidableObject : public GameObject {
private:

	bool m_checkingCollision;

	bool doCollision(GameObject& other) { return false; }


public:

	CollidableObject(float x, float y, float width = 1, float height = 1) : 
		GameObject(x, y, width, height), m_checkingCollision(false) {}

	virtual bool checkCollision(GameObject& other)
	{
		if (!m_checkingCollision)  {
			m_checkingCollision = true;
			return other.acceptCollision(*(Derived *)this);
		} else  {
			m_checkingCollision = false;
			if (doCollision(other))  {
				onCollision(other);
				return true;
			}
			return false;
		}
	}

	virtual bool acceptCollision(GameObject& oth)  { return doCollision(oth); }


	virtual void onCollision(GameObject& other) { }

	virtual ~CollidableObject() {}
};

#endif
