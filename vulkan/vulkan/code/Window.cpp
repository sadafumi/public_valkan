#include "Window.h"
#include <Windows.h>
#include "Graphics.h"

Window::Window()
{
}
Window::~Window()
{
}

void Window::Init()
{
	wind.Create(&this->data);
	Test.Init(this->data);
}

void Window::Uninit()
{
	Test.Uninit();
	wind.Delete();
}

bool Window::Update()
{
	Test.Updata();
	if (wind.Updata())
	{
		return true;
	}
	return false;
}
void Window::Draw()
{
	Test.Draw();
}

Utility::Int_Vec2 Window_Data::Get_Windows_Size()
{
	return Utility::Int_Vec2(this->Screen_Width_Size, this->Screen_Hiegth_Size);
}
