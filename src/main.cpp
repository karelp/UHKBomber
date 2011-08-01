
#include "Game.h"


/**
 * @brief
 * Converts commandline parameters to C++ types.
 * 
 * @param argc
 * Argument count.
 * 
 * @param argv
 * Array of strings with the actual arguments.
 * 
 * @returns
 * Standard list with arguments converted to std::string.
 */
std::list<std::string> convertParams(int argc, const char *argv[])
{
	std::list<std::string> result;
	for (int i = 0; i < argc; i++)
		result.push_back(argv[i]);
	return result;
}

int main(int argc, const char *argv[])
{
	Game::get().initialize(convertParams(argc, argv));
	Game::get().run();
	Game::get().shutdown();
}