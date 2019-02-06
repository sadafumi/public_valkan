#pragma once
#include "vulkan.h"
class Draw_2D_Texture
{
public:
	Draw_2D_Texture();
	~Draw_2D_Texture();
	void Init(Utility::Int_Vec2, HWND hWnd, HINSTANCE hInstance);
	void Uninit();
	void Updata();
	void Draw();
private:
};

