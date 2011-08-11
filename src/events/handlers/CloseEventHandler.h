#ifndef CLOSEEVENTHANDLER_H
#define CLOSEEVENTHANDLER_H

#include "EventLoop.h"

class CloseEvent;
class Game;

class CloseEventHandler : public EventHandlerBase<CloseEvent>  {
private:
	Game& m_game;

public:
	explicit CloseEventHandler(Game& game) : m_game(game) {}

	void handleEvent(const CloseEvent& evt) override;
};


#endif
