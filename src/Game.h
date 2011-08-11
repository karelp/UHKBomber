#ifndef GAME_H
#define GAME_H

#include <list>
#include <string>

#include "Options.h"
#include "System.h"
#include "EventLoop.h"

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


	/**
	 * @brief
	 * Event and user callback handling.
	 */
	EventLoop m_loop;

private:
	Game() :
		m_initialized(false),
		m_running(false),
		m_loop(m_system)
		{}
		

	/**
	 * @brief
	 * Parses command line arguments.
	 * 
	 * @param parameters
	 * List of the command line arguments, including the zeroth parameter containing binary path.
	 * 
	 * Parses and processes the command line arguments. These arguments override any settings specified
	 * in options.
	 * 
	 * @remarks
	 * Must be called after options have been loaded.
	 * 
	 * @see
	 * Options::loadFromFile
	 */
	void parseCommandLine(const std::list<std::string>& parameters);

	/**
	 * @brief
	 * Shuts the game down.
	 * 
	 * Frees all resources and graphics context and then exits the program.
	 */
	void shutdown();

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
	 * Ends the game loop.
	 * 
	 * Sets the running flag to false. This terminates the game loop,
	 * and finally quits the game.
	 */
	void close();

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

public:
	// Constants
	static const char *name;
};

#endif
