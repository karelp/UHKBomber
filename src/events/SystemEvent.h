#ifndef SYSTEMEVENT_H
#define SYSTEMEVENT_H

#include "EventLoop.h"

/**
 * @brief
 * Base class for all system events.
 * 
 * This serves as a base class for all kinds of system events.
 */
class SystemEvent : public Event {
protected:
	sf::Event m_event;

public:
	explicit SystemEvent(sf::Event& ev) : m_event(ev) {}

	virtual ~SystemEvent() {}

	// Properties
	sf::Event& event() { return m_event; }
	const sf::Event& event() const { return m_event; }
};


#endif

