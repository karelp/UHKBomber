#ifndef SYSTEM_H
#define SYSTEM_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

/**
 * @brief
 * This class encapsulates the raw system facilities such as graphics or audio contexts.
 * 
 * @remarks
 * Used as a singleton, accessible via Game::system()
 * 
 * @see
 * Game::system
 */
class System  {
private:
	friend class Game;

	/**
	 * @brief
	 * Write brief comment for m_appWindow here.
	 * 
	 * Write detailed description for m_appWindow here.
	 * 
	 * @remarks
	 * Write remarks for m_appWindow here.
	 * 
	 * @see
	 * Separate items with the '|' character.
	 */
	sf::RenderWindow *m_appWindow;


	/**
	 * @brief
	 * Initialize the system.
	 * 
	 * @returns
	 * True if everything goes OK, false otherwise.
	 * 
	 * Initializes SFML graphics and audio.
	 * 
	 * @remarks
	 * Used only by Game class at game startup.
	 * 
	 * @see
	 * Game::initialize
	 */
	bool initialize();


	/**
	 * @brief
	 * Shuts down the system. No resources are valid after this call.
	 * 
	 * @remarks
	 * Used only by Game class when shutting down the game.
	 * 
	 * @see
	 * Game::shutdown
	 */
	void shutdown();

	System() : m_appWindow(NULL) {}

	~System();
};

#endif