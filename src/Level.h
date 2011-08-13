#ifndef LEVEL_H
#define LEVEL_H

#include <boost/multi_array.hpp>
#include "Tile.h"

/**
 * @brief
 * Width of level tile in pixels
 */
static const int LEVEL_TILE_WIDTH = 40;
/**
 * @brief
 * Height of level tile in pixels
 */
static const int LEVEL_TILE_HEIGHT = 40;

/**
 * @brief
 * Container for whole level information.
 * 
 * Level contains information about its content, 
 * know how to draw it and simulate changes during time
 * 
 * @see
 * GameObject
 */
class Level : public Renderable, public Simulable {
public:
	Level(int width, int height);
	~Level() {}

	void render(sf::RenderTarget& target, DeltaTime dt);
	void simulate(DeltaTime dt);

	int m_Tilewidth, m_Tileheight;

private:
	Tile* levelData;
	
	// multidimensional array for level tiles (by boost)
	typedef boost::multi_array<Tile*, 2> tile_array;
	typedef tile_array::index index;
	tile_array m_tileArray;
};

#endif