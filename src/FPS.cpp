#include <SFML/Window.hpp>
#include "FPS.h"
#include "Game.h"

Fps::Fps(sf::RenderWindow& win) : m_frames(0), m_currentFps(0), m_secondCounter(0), m_currentDt(0), m_win(win)
{
		m_clock.Reset();
}

void Fps::onFrame()
{
	m_win.SetFramerateLimit(Game::get().options().video.fpsLimit);

	++m_frames;
	m_win.IsOpened();
	m_currentDt = m_clock.GetElapsedTime();
	m_clock.Reset();
	m_secondCounter += m_currentDt;
	if (m_secondCounter >= 1.0f)  {
		m_secondCounter = 0;
		m_currentFps = m_frames;
		m_frames = 0;
	}
}