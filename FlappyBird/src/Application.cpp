#include "SceneManager.h"

int main()
{
	SceneManager* sceneMgr = new SceneManager();
	sceneMgr->Run();
	delete sceneMgr;
}