#pragma once
#include <Windows.h>
#include <stdio.h>
#include "Utility.h"
#include "Graphics.h"

class Window
{
public:
	Window();
	~Window();
	HWND Create(HWND hWnd, HINSTANCE hInstance, int nCmdShow);
	void Delete();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	bool ChangeDisplay(HINSTANCE hInstance, HWND hWnd);
	Utility::Int_Vec2 Get_Windows_Size();
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //ウィンドウプロシージャ
	static void KeyBoardDown(WPARAM, HWND);
	bool ChangeDevice(HINSTANCE hInstance, HWND hWnd, bool NewScreen);

	static bool DisplayMode;
	static bool Press;
	static bool Blur;

	const char* Class_Name = "  ";
	const char* Window_Name = "  ";
	const int Screen_Width_Size = 1280;
	const int Screen_Hiegth_Size = 720;

	//ここから下はProjectごとに変えるのもでないと俺が困る
	Graphics Test;
};

