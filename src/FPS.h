#ifndef FPS_H
#define FPS_H

#include <SFML/Graphics.hpp>

/**
 * @brief
 * Used as a type for time delays between frames.
 */
typedef float DeltaTime;

/**
 * @brief
 * Calculates and limits FPS.
 * 
 * Write detailed description for Fps here.
 * 
 * @remarks
 * Write remarks for Fps here.
 * 
 * @see
 * Separate items with the '|' character.
 */
class Fps  {
private:
	int m_frames;
	int m_currentFps;
	float m_secondCounter;
	DeltaTime m_currentDt;
	sf::RenderWindow& m_win;
	sf::Clock m_clock;

public:
	Fps(sf::RenderWindow& win);

	/**
	 * @brief
	 * Updates the FPS counters.
	 * 
	 * Updates the FPS counters. Should be called exactly once per frame.
	 * Also limits the FPS to the value set in options.
	 */
	void onFrame();

	/**
	 * @brief
	 * Get time difference between this and last frame.
	 * 
	 * @returns
	 * Delta time between this and last frame.
	 */
	DeltaTime getDelta() const { return m_currentDt; }

	/**
	 * @brief
	 * FPS for the last elapsed second.
	 * 
	 * @returns
	 * Current game FPS.
	 */
	int getFPS() const { return m_currentFps; }
};


#endif
