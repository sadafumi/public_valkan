#pragma once
#include "vulkan.h"
class Draw_3D_Texture
{
public:
	Draw_3D_Texture();
	~Draw_3D_Texture();
	void Init(Utility::Int_Vec2, HWND hWnd, HINSTANCE hInstance);
	void Uninit();
	void Updata();
	void Draw();
private:
};

