#include "Manager.h"

// TODO: fix the deltatime piling up when the window is dragged around
// TODO: do smth so that we can pause the game

int main()
{
	Manager* sceneMgr = new Manager();
	sceneMgr->Run();
	delete sceneMgr;
}