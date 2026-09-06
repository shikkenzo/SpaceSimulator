#include "Core.h"
#include "Game.h"

int main(int argc, char** argv)
{
	Core core;
	GameApp game;	

	core.Init();
	core.Run(game);
	core.Shutdown();
}
