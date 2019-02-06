#include "Graphics.h"
#include "Utility.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

void Graphics::Init(Utility::Int_Vec2 in_win, HWND hWnd, HINSTANCE hInstance)
{
	test.Init(in_win, hWnd, hInstance);
}

void Graphics::Uninit()
{
	test.Uninit();
}

void Graphics::Updata()
{
	test.Updata();
}

void Graphics::Draw()
{
	test.Draw();
}
