#ifndef LEVEL_H
#define LEVEL_H

/**
 * @brief
 * Container for whole level information.
 * 
 * Level conitans information about its content, 
 * know how to draw it and simulate changes during time 
 * (throught GameObject ancestor).
 * 
 * @see
 * GameObject
 */
class Level : public GameObject {
	~Level() {}
};

#endif