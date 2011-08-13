#include "Level.h"

Level::Level(int width, int height) : m_width(width), m_height(height) 
{
	m_tileArray.resize(boost::extents[m_width][m_height]);
}