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
	 * Application window pointer.
	 * 
	 * Points to main application window. The window is closed when the system
	 * gets deinitialized.
	 */
	sf::RenderWindow m_appWindow;

	/**
	 * @brief
	 * A flag holding the initialization state of the system.
	 * 
	 * It gets true after the complete system is initialized and
	 * false when it is completely shut down.
	 * 
	 * @see
	 * System::initialize | System::shutdown
	 */
	bool m_initialized;


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
	 * Used only by Game class at game startup. Options must be
	 * loaded when this method is called.
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

	System() : m_initialized(false) {}

public:
	// Properties

	bool isInitialized() const { return m_initialized; }

	~System() { }

public:
	// Constants

	static const unsigned int BitsPerPixel = 32;
	static const unsigned int BytesPerPixel = BitsPerPixel / 8;
};

#endif