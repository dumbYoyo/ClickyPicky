#include "Manager.h"

// TODO: art
// TODO: do smth so that we can pause the game

int main()
{
	Manager* sceneMgr = new Manager();
	sceneMgr->Run();
	delete sceneMgr;
}