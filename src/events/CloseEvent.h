#ifndef CLOSEEVENT_H
#define CLOSEEVENT_H

#include "SystemEvent.h"

class CloseEvent : public SystemEvent  {
public:
	explicit CloseEvent(sf::Event& ev) : SystemEvent(ev)  {}
};

#endif
