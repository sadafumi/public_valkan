#include "Windows_API.h"

#ifdef _WIN32

bool Windows_API::end_flag;
void Windows_API::Create(Window_Data* in_data)
{
	int nScreenWidth, nScreenHiegth, WindowSizeWidth, WindowSizeHiegth;
	RECT wr = { 0 , 0 , in_data->Screen_Width_Size , in_data->Screen_Hiegth_Size }, dr;

	in_data->connect = GetModuleHandle(NULL);
	//*�E�B���h�E��o�^*//
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//�T�C�Y
		CS_VREDRAW | CS_HREDRAW,		//�X�^�C��
		this->WndProc,						//�v���V�[�W��
		0,								//����Ȃ�����O
		0,								//����Ȃ�����O
		in_data->connect,						//�C���X�^���X
		NULL,							//�A�C�R��
		LoadCursor(NULL,IDC_ARROW),	//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),	//�����w�i�F
		NULL,							//���j���[
		this->Class_Name,						//�N���X�̖��O
		NULL,							//�~�j�A�C�R��
	};
	RegisterClassEx(&wcex);

	GetWindowRect(GetDesktopWindow(), &dr);
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);
	nScreenWidth = wr.right - wr.left;
	nScreenHiegth = wr.bottom - wr.top;
	WindowSizeWidth = (dr.right - nScreenWidth) / 2;
	WindowSizeHiegth = (dr.bottom - nScreenHiegth) / 2;
	dr.right < WindowSizeWidth ? WindowSizeWidth = 0 : WindowSizeWidth;
	dr.bottom < WindowSizeHiegth ? WindowSizeHiegth = 0 : WindowSizeHiegth;


	//*�E�B���h�E��ݒ�*//
	in_data->wind = CreateWindowEx(
		0,
		this->Class_Name,
		this->Window_Name,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SYSMENU,
		WindowSizeWidth,
		WindowSizeHiegth,
		nScreenWidth,
		nScreenHiegth,
		NULL,
		NULL,
		in_data->connect,
		NULL
	);
	if (!in_data->wind) {
		// It didn't work, so try to give a useful error:
		FILE* fp;
		fp = fopen("Error_log.txt", "w+");
		fprintf(fp, "�E�B���h�E�̍쐬�Ɏ��s");
		fclose(fp);
		printf("Cannot create a window in which to draw!\n");
		fflush(stdout);
		exit(1);
	}
}

void Windows_API::Delete()
{
	PostQuitMessage(0);
}

bool Windows_API::Updata()
{
	return end_flag;
}

LRESULT Windows_API::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	LOWORD(lParam);
	HIWORD(lParam);
	switch (uMsg)
	{
	case WM_DESTROY:	//WM_CLOSE,WM_QUIT
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
	{
		KeyBoardDown(wParam, hWnd);
	}
	break;
	case WM_CLOSE://[X]�͏I���{�^��
		nID = MessageBox(hWnd, "�I�����܂����H", "�V���b�g�_�E�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
		if (nID == IDYES)
		{
			end_flag = true;
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Windows_API::KeyBoardDown(WPARAM in_wParam, HWND in_hWnd)
{
	int nID;
	if (in_wParam == VK_ESCAPE)
	{
		nID = MessageBox(in_hWnd, "�I�����܂����H", "�V���b�g�_�E�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);
		if (nID == IDYES)
		{
			end_flag = true;
			DestroyWindow(in_hWnd);
		}
	}
}
#endif 