#include "stdafx.h"
#include "GameProcedure.h"


INT APIENTRY _tWinMain(HINSTANCE hInstance,
				HINSTANCE hPrevInstance,
				LPTSTR    lpCmdLine,
				INT       nCmdShow)
{
	//±£´æÈ«¾Ö¾ä±ú
	g_hInstance = hInstance;
	CGameProcedure::InitStaticMemeber();
	CGameProcedure::MainLoop();
	CGameProcedure::ReleaseStaticMember();
	return 0;
}