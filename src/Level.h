#ifndef LEVEL_H
#define LEVEL_H

#include <boost/multi_array.hpp>
#include "Tile.h"

/**
 * @brief
 * Container for whole level information.
 * 
 * Level contains information about its content, 
 * know how to draw it and simulate changes during time 
 * (through GameObject ancestor).
 * 
 * @see
 * GameObject
 */
class Level : public GameObject {
public:
	Level(int width, int height);
	
	~Level() {}

	int m_width, m_height;

private:
	Tile* levelData;
	
	typedef boost::multi_array<Tile*, 2> tile_array;
	typedef tile_array::index index;
	tile_array m_tileArray;
};

#endif