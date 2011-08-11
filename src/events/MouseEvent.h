#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <SFML/Window.hpp>
#include "SystemEvent.h"

class MouseEvent : public SystemEvent  {
public:
	explicit MouseEvent(sf::Event& e) : SystemEvent(e) {}

	virtual sf::Mouse::Button button() const
	{
		return m_event.MouseButton.Button;
	}

	virtual int x() const
	{
		return m_event.MouseButton.X;
	}

	virtual int y() const
	{
		return m_event.MouseButton.Y;
	}
};

class MouseDownEvent : public MouseEvent  {
public:
	explicit MouseDownEvent(sf::Event& ev) : MouseEvent(ev) {}
};

class MouseUpEvent : public MouseEvent  {
public:
	explicit MouseUpEvent(sf::Event& ev) : MouseEvent(ev) {}
};

class MouseDblClickEvent : public MouseEvent  {
public:
	explicit MouseDblClickEvent(sf::Event& ev) : MouseEvent(ev) {}
};

class MouseWheelEvent : public MouseEvent {
public:
	explicit MouseWheelEvent(sf::Event& ev) : MouseEvent(ev) {}

	int delta() const { return m_event.MouseWheel.Delta; }
};

#endif
