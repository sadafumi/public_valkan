#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vulkan/vulkan.h>
#include <Windows.h> //�E�B���h�E�YAPI
#include <stdio.h>
#pragma comment(lib, "winmm.lib")
#include "Window.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window wind; //�E�B���h�֐�
	MSG msg; //���b�Z�[�W�ϐ�
	HWND hWnd = NULL;
	hInstance = hInstance;
	hPrevInstance = hPrevInstance;
	lpCmdLine = lpCmdLine;
	nCmdShow = nCmdShow;

	AllocConsole();

	// �W�����o�͂Ɋ��蓖�Ă�
	FILE* fp = NULL;
	// ���݂̃R�[�h
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);

	wind.Create(hWnd, hInstance, nCmdShow);

	wind.Init();
	DWORD nNowTime = 0, nOldTime = 0;
	timeBeginPeriod(1);

	for (;;)
	{
		//*���b�Z�[�W���[�v*//
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//���b�Z�[�W����
			if (msg.message == WM_QUIT)
			{
				wind.Uninit();//�I���ʒu
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
			//�Q�[������
			nNowTime = timeGetTime();//���̎���
			if ((nNowTime - nOldTime) * 60 >= 1000)
			{
				//�X�V
				wind.Update();
				//�`��
				wind.Draw();
				//�O�t���[���̎��Ԃ�ۑ�
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
