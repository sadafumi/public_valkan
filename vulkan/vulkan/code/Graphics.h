//========================================================================
//	maked by sadafumi 
//	2019/2/7
//========================================================================
#pragma once
#include <Windows.h>
#include <stdio.h>
#include "Test_Draw_2D_noTexture.h"
#include "Test_Draw_2D_Texture.h"
#include "Test_Draw_3D_noTexture.h"
#include "Test_Draw_3D_Texture.h"

class Graphics
{
public:
	Graphics();
	~Graphics();
	void Init(Utility::Int_Vec2,HWND hWnd, HINSTANCE hInstance);
	void Uninit();
	void Updata();
	void Draw();
private:
	Test_Draw_3D_noTexture test;
	//Test_Draw_3D_Texture test;
};


