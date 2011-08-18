#include "Level.h"
#include "tiles/EmptyTile.h"

static sf::Sprite tempSprite = sf::Sprite();

Level::Level(int width, int height) : m_Tilewidth(width), m_Tileheight(height) 
{
	tempSprite.Resize(LEVEL_TILE_WIDTH, LEVEL_TILE_HEIGHT);
	m_tileArray.resize(boost::extents[m_Tilewidth][m_Tileheight]);
	for(index i = 0; i < m_Tilewidth; ++i)
	{
		for(index j = 0; j < m_Tileheight; ++j)
		{
			m_tileArray[i][j] = new EmptyTile((float) (i * LEVEL_TILE_WIDTH), (float) (j * LEVEL_TILE_HEIGHT), tempSprite);
		}
	}
}

void Level::render(sf::RenderTarget& target, DeltaTime dt)
{
	for(index i = 0; i < m_Tilewidth; ++i)
	{
		for(index j = 0; j < m_Tileheight; ++j)
		{
			if(m_tileArray[i][j] != NULL)
				m_tileArray[i][j]->render(target, dt);
		}
	}
}
	
void Level::simulate(DeltaTime dt) 
{
	for(index i = 0; i < m_Tilewidth; ++i)
	{
		for(index j = 0; j < m_Tileheight; ++j)
		{
			if(m_tileArray[i][j] != NULL)
				m_tileArray[i][j]->simulate(dt);
		}
	}
}