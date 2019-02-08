#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vulkan/vulkan.h>
#include <Windows.h> //ウィンドウズAPI
#include <stdio.h>
#pragma comment(lib, "winmm.lib")
#include "Window.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window wind; //ウィンド関数
	MSG msg; //メッセージ変数
	HWND hWnd = NULL;
	hInstance = hInstance;
	hPrevInstance = hPrevInstance;
	lpCmdLine = lpCmdLine;
	nCmdShow = nCmdShow;

	AllocConsole();

	// 標準入出力に割り当てる
	FILE* fp = NULL;
	// 現在のコード
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);

	wind.Create(hWnd, hInstance, nCmdShow);

	wind.Init();
	DWORD nNowTime = 0, nOldTime = 0;
	timeBeginPeriod(1);

	for (;;)
	{
		//*メッセージループ*//
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//メッセージ処理
			if (msg.message == WM_QUIT)
			{
				wind.Uninit();//終了位置
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//ゲーム処理
			nNowTime = timeGetTime();//今の時間
			if ((nNowTime - nOldTime) * 60 >= 1000)
			{
				//更新
				wind.Update();
				//描画
				wind.Draw();
				//前フレームの時間を保存
				nOldTime = nNowTime;
			}
			//break;
		}
	}
	timeEndPeriod(1);

	wind.Delete();

	::FreeConsole();

	return (int)msg.wParam;
}
