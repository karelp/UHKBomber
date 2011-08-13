#include "Game.h"

const char *Game::name = "UHKBomber";

void Game::parseCommandLine(const std::list<std::string>& parameters)
{
	for (auto it = parameters.begin(); it != parameters.end(); ++it)  {
		if (*it == "-window")  {
			m_options.video.fullscreen = false;
		} else if (*it == "-fullscreen")  {
			m_options.video.fullscreen = true;
		} else {
			// TODO: log unrecognized switch
		}
	}
}

bool Game::initialize(const std::list<std::string>& parameters)
{
	if (m_initialized)
		return true;

	if (!m_options.loadFromFile(Options::optionsFileName))  {
		// TODO: logging system
		// Not fatal, we have defaults, move on
	}

	// Command line overrides options
	parseCommandLine(parameters);

	if (!m_system.initialize())  {
		return false;
	}

	m_initialized = true;
	m_running = false;
	return true;
}

void Game::shutdown()
{
	if (!m_initialized)
		return;

	m_running = false;
	m_system.shutdown();
	m_options.saveToFile(Options::optionsFileName);

	m_initialized = false;
}

void Game::run()
{
	m_running = true;

	// Just a dummy loop for now, will be replaced later with a more sophisticated implementation
	while (m_running)  {
		m_fps.onFrame();
		m_loop.process();
	}

	shutdown();
}

void Game::close()
{
	m_running = false;
}

Game& Game::get()
{
	static Game instance;
	return instance;
}
