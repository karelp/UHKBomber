#include <SFML/System.hpp>
#include "EventLoop.h"
#include "Game.h"
#include "events/CloseEvent.h"
#include "events/KeyboardEvent.h"
#include "events/MouseEvent.h"
#include "events/handlers/CloseEventHandler.h"

void EventLoop::addHandler(EventHandler *handler)
{
	sf::Lock l(m_handlerMutex);
	m_handlers.push_back(handler);
}

void EventLoop::pushEvent(EventPtr& evt)
{
	sf::Lock l(m_eventMutex);
	m_events.push_back(evt);
}

void EventLoop::process()
{
	processSystemEvents();

	sf::Lock l(m_eventMutex);

	while (!m_events.empty())  {
		EventPtr& e = m_events.front();
		handleEvent(*e);
		m_events.pop_front();
	}
}

void EventLoop::handleEvent(const Event& e)
{
	sf::Lock l(m_handlerMutex);
	for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it)  {
		if ((*it)->canHandleEvent(e))
			(*it)->handleEvent(e);
	}
}

void EventLoop::processSystemEvents()
{
	sf::Event ev;
	EventPtr evtWrapper;
	while (m_system.m_appWindow.GetEvent(ev))  {
		switch (ev.Type)  {
		case sf::Event::Closed:
			handleEvent(CloseEvent(ev));
		break;
		case sf::Event::MouseButtonPressed:
			handleEvent(MouseDownEvent(ev));
		break;
		case sf::Event::MouseButtonReleased:
			handleEvent(MouseUpEvent(ev));
		break;
		case sf::Event::MouseWheelMoved:
			handleEvent(MouseWheelEvent(ev));
		break;
		case sf::Event::KeyPressed:
			handleEvent(KeyDownEvent(ev));
		break;
		case sf::Event::KeyReleased:
			handleEvent(KeyUpEvent(ev));
		break;
		}
	}
}

void EventLoop::initializeSystemHandlers()
{
	sf::Lock l(m_handlerMutex);
	m_handlers.push_back(new CloseEventHandler(Game::get()));
	
}

EventLoop::~EventLoop()
{
	sf::Lock l(m_handlerMutex);
	for (auto it = m_handlers.begin(); it != m_handlers.end(); ++it)
		delete (*it);
}

