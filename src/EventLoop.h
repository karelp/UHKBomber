#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <list>
#include <SFML/System.hpp>
#include <boost/shared_ptr.hpp>
#include "System.h"

/**
 * @brief
 * Base class for all events.
 */
class Event  {
public:
	virtual ~Event() {}
};

/**
 * @brief
 * Interface for all event handlers.
 * 
 * Defines a specification of an event handler. An event handler
 * is a class that processes all events of specific kind. For example
 * MouseClickEventHandler handles all mouse clicks, KeyboardEventHandler
 * handles all keypresses.
 * 
 * @remarks
 * Do not inherit from this interface directly, use EventHandlerBase<>
 * instead as it already has canHandleEvent implementation.
 * 
 * @see
 * EventHandlerBase
 */
class EventHandler  {
public:
	/**
	 * @brief
	 * Returns true if this handler can handle the given event.
	 * 
	 * @param ev
	 * The event that is about to be handled.
	 * 
	 * @returns
	 * True if this handler can handle this event type, false otherwise.
	 * 
	 * @see
	 * EventHandlerBase::canHandleEvent
	 */
	virtual bool canHandleEvent(const Event& ev) const = 0;


	/**
	 * @brief
	 * Handle the given event. The event is guaranteed to be of a type this
	 * handler can handle.
	 * 
	 * @param ev
	 * Event to be handled.
	 * 
	 * This is the place where the events should be processed.
	 */
	virtual void handleEvent(const Event& ev) = 0;

	virtual ~EventHandler() {}
};

/**
 * @brief
 * Base for all common event handlers.
 * 
 * @param EventType
 * The event this handler can handle. For example MouseEvent or KeyboardEvent.
 * 
 * This class is to be used as a base for all event handlers. It automatically
 * implements canHandleEvent based on the template parameter.
 */
template <typename EventType>
class EventHandlerBase : public EventHandler {
public:
	/**
	 * @brief
	 * Checks if the given event matches this handler.
	 * 
	 * @param ev
	 * Event to check.
	 * 
	 * @returns
	 * True if this handler can handle the event.
	 * 
	 * Checks that the event type matches the template parameter using RTTI.
	 * 
	 * @remarks
	 * Requires RTTI to be enabled.
	 */
	bool canHandleEvent(const Event& ev) const override
	{
		const EventType *e = dynamic_cast<const EventType *>(&ev);
		return e != NULL;
	}

	/**
	 * @brief
	 * Implementation of the interface member class. Converts the
	 * event and passes it to the typed method.
	 * 
	 * @param ev
	 * The event to handle.
	 */
	void handleEvent(const Event& ev) override
	{
		const EventType *e = dynamic_cast<const EventType *>(&ev);
		if (e)
			handleEvent(*e);
	}

	/**
	 * @brief
	 * Abstract method that should be implemented in the concrete handler.
	 * 
	 * @param ev
	 * Event converted to the correct type.
	 * 
	 * This method is overriden in the specialized classes that handle concrete
	 * events.
	 * 
	 * @remarks
	 * Write remarks for handleEvent here.
	 * 
	 * @see
	 * Separate items with the '|' character.
	 */
	virtual void handleEvent(const EventType& ev) = 0;
};

typedef boost::shared_ptr<Event> EventPtr;

/**
 * @brief
 * Implementation of the game event loop.
 * 
 * The event loop handles all the events coming to the application from
 * system, user defined events etc.
 * 
 * @remarks
 * This is a singleton class.
 */
class EventLoop  {
private:
	mutable sf::Mutex m_eventMutex, m_handlerMutex;

	System& m_system;

	/**
	 * @brief
	 * Queue of the events. Popped from the beginning.
	 */
	std::list<EventPtr> m_events;


	/**
	 * @brief
	 * List of registered event handlers.
	 */
	std::list<EventHandler *> m_handlers;

private:

	/**
	 * @brief
	 * Processes system events such as keyboard or mouse. Called by process().
	 */
	void processSystemEvents();


	/**
	 * @brief
	 * Handles a wrapped event.
	 */
	void handleEvent(const Event& ev);


	/**
	 * @brief
	 * Initializes all system event handlers (CloseEventsHandler, MouseEventHandler, etc.)
	 */
	void initializeSystemHandlers();

public:
	EventLoop(System& sys) : m_system(sys) 
	{
		initializeSystemHandlers();	
	}

	/**
	 * @brief
	 * Adds a new event handler.
	 * 
	 * @param handler
	 * The event handler to register.
	 * 
	 * Adds a new event handler to the queue. The event handler will receive
	 * the events from now on. The event handler is freed by the event loop,
	 * pass a pointer on the heap.
	 * 
	 * @see
	 * EventHandler | EventHandlerBase
	 */
	void addHandler(EventHandler *handler);

	/**
	 * @brief
	 * Pushes a custom event to the queue.
	 * 
	 * @param evt
	 * The event to push to the queue.
	 * 
	 * Adds the event to the queue for processing in the process() method.
	 * If there is no event handler to handle the event, the event is discarded.
	 * You can also use this method to insert fake system events.
	 * 
	 * @remarks
	 * Threadsafe.
	 * 
	 * @see
	 * EventLoop::process
	 */
	void pushEvent(EventPtr& evt);

	/**
	 * @brief
	 * Reads system events and processes all events in the queue.
	 * 
	 * This method first processes any system events (key, mouse, paint etc.) and
	 * then the user events. If an event doesn't have a corresponding event handler, 
	 * it is discarded.
	 * 
	 * @see
	 * EventLoop::pushEvent
	 */
	void process();

	/**
	 * @brief
	 * Shuts the loop down and deletes all handlers.
	 */
	~EventLoop();
};


#endif