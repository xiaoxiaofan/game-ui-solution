#include "stdafx.h"
#include "GameProcedure.h"


INT APIENTRY _tWinMain(HINSTANCE hInstance,
				HINSTANCE hPrevInstance,
				LPTSTR    lpCmdLine,
				INT       nCmdShow)
{
	//����ȫ�־��
	g_hInstance = hInstance;
	CGameProcedure::InitStaticMemeber();
	return 0;
}