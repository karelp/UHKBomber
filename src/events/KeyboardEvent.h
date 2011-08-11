#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include <SFML/Window.hpp>
#include "SystemEvent.h"

class KeyboardEvent : public SystemEvent {
public:
	explicit KeyboardEvent(sf::Event& e) : SystemEvent(e) {}

	virtual sf::Key::Code keyCode() const
	{
		return m_event.Key.Code;
	}

	virtual sf::Uint32 unicode() const
	{
		return m_event.Key.Code;
	}
};

class KeyDownEvent : public KeyboardEvent  {
public:
	explicit KeyDownEvent(sf::Event& ev) : KeyboardEvent(ev) {}
};

class KeyUpEvent : public KeyboardEvent  {
public:
	explicit KeyUpEvent(sf::Event& ev) : KeyboardEvent(ev) {}
};

#endif
