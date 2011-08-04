#include "Game.h"
#include "System.h"

bool System::initialize()
{
	if (m_initialized)
		return true;

	const Options::Video& options = Game::get().options().video;
	sf::VideoMode mode(options.screenWidth, options.screenHeight, BitsPerPixel);

	m_appWindow.Create(mode, Game::name);

	m_initialized = true;

	return true;
}

void System::shutdown()
{
	if (!m_initialized)
		return;

	m_appWindow.Close();

	m_initialized = false;
}
