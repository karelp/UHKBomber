#include "CloseEventHandler.h"
#include "events/CloseEvent.h"
#include "Game.h"

void CloseEventHandler::handleEvent(const CloseEvent& ev)
{
	m_game.close();
}
