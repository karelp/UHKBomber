#ifndef GAME_H
#define GAME_H

#include <list>
#include <string>

#include "Options.h"
#include "System.h"

/**
 * @brief
 * Container of the game application.
 * 
 * Takes care for game startup, game loop and proper shutdown.
 * 
 * @remarks
 * Should be used as a singleton.
 */
class Game  {
private:
	/**
	 * @brief
	 * True when initialize() finished correctly.
	 *
	 * @see
	 * initialize
	 */
	bool m_initialized;

	/**
	 * @brief
	 * True while in the gameloop. When this variable gets false, the game shuts down.
	 */
	bool m_running;

	/**
	 * @brief
	 * Contains the game options, publicly accessible using options().
	 */
	Options m_options;

	/**
	 * @brief
	 * Contains the core system - audio, input and video driver wrappers.
	 */
	System m_system;

private:
	Game() :
		m_initialized(false),
		m_running(false) 
		{}
		

public:
	/**
	 * @brief
	 * Initializes the game, sets up drawing.
	 * 
	 * @returns
	 * False if initialization fails.
	 * 
	 * Initializes the game, window, graphics context, audio and menu system.
	 */
	bool initialize(const std::list<std::string>& parameters);


	/**
	 * @brief
	 * Processes the game loop.
	 * 
	 * Runs the entire game logic and performs rendering.
	 */
	void run();


	/**
	 * @brief
	 * Shuts the game down.
	 * 
	 * Frees all resources and graphics context and then exits the program.
	 */
	void shutdown();


	/**
	 * @brief
	 * Returns the Game singleton
	 */
	static Game& get();

public:
	// Properties

	Options& options() { return m_options; }
	const Options& options() const { return m_options; }

	System& system() { return m_system; }
	const System& system() const { return m_system; }
};

#endif
