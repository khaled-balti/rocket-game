#include "gamel.h"
int main()
{
	srand(static_cast<unsigned>(time(NULL)));
	Game game;
	game.run();
}
