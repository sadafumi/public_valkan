#pragma once
#include "Utility.h"
#include "Window_Data.h"
#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
class Windows_API
{
public:
	void Create(Window_Data*);
	void Delete();
	bool Updata();
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //ウィンドウプロシージャ
	static void KeyBoardDown(WPARAM, HWND);

	static bool end_flag;
	const char* Class_Name = "  ";
	const char* Window_Name = "  ";
};
#endif 
