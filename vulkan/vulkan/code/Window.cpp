#include "Window.h"
#include <Windows.h>
#include "Graphics.h"

bool Window::DisplayMode = true;
bool Window::Press = false;
bool Window::Blur = false;

Window::Window()
{
}
Window::~Window()
{
}
HWND Window::Create(HWND in_hWnd, HINSTANCE hInstance, int nCmdShow)
{
	int nScreenWidth, nScreenHiegth, WindowSizeWidth, WindowSizeHiegth;
	RECT wr = { 0 , 0 , Screen_Width_Size , Screen_Hiegth_Size }, dr;

	//*ウィンドウを登録*//
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//サイズ
		CS_VREDRAW | CS_HREDRAW,		//スタイル
		this->WndProc,						//プロシージャ
		0,								//いらないから０
		0,								//いらないから０
		hInstance,						//インスタンス
		NULL,							//アイコン
		LoadCursor(NULL,IDC_ARROW),	//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),	//初期背景色
		NULL,							//メニュー
		this->Class_Name,						//クラスの名前
		NULL,							//ミニアイコン
	};
	RegisterClassEx(&wcex);

	GetWindowRect(GetDesktopWindow(), &dr);
	AdjustWindowRect(&wr, (WS_OVERLAPPEDWINDOW &~(WS_THICKFRAME | WS_MAXIMIZEBOX)), false);
	nScreenWidth = wr.right - wr.left;
	nScreenHiegth = wr.bottom - wr.top;
	WindowSizeWidth = (dr.right - nScreenWidth) / 2;
	WindowSizeHiegth = (dr.bottom - nScreenHiegth) / 2;
	dr.right < WindowSizeWidth ? WindowSizeWidth = 0 : WindowSizeWidth;
	dr.bottom < WindowSizeHiegth ? WindowSizeHiegth = 0 : WindowSizeHiegth;


	//*ウィンドウを設定*//
	in_hWnd = CreateWindowEx(
		0,
		this->Class_Name,
		this->Window_Name,
		WS_OVERLAPPEDWINDOW,
		WindowSizeWidth,
		WindowSizeHiegth,
		nScreenWidth,
		nScreenHiegth,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(in_hWnd, nCmdShow);		//ウィンドウ呼び出し
	UpdateWindow(in_hWnd);				//ウィンドウの更新

	Test.Init(this->Get_Windows_Size(),in_hWnd, hInstance);
	return in_hWnd;
}
void Window::Delete()
{
	PostQuitMessage(0);
}

void Window::Init()
{

}

void Window::Uninit()
{
	Test.Uninit();
}

void Window::Update()
{
	Test.Updata();
}
void Window::Draw()
{
	Test.Draw();
}


void Window::KeyBoardDown(WPARAM in_wParam, HWND in_hWnd)
{
	int nID;
	Press = false;
	if (in_wParam == VK_ESCAPE)
	{
		nID = MessageBox(in_hWnd, "終了しますか？", "シャットダウンメッセージ", MB_YESNO | MB_DEFBUTTON2);
		if (nID == IDYES)
		{
			DestroyWindow(in_hWnd);
		}
	}
}
bool Window::ChangeDevice(HINSTANCE hInstance, HWND hWnd, bool NewScreen)
{
	hInstance = hInstance;
	NewScreen = NewScreen;
	hWnd = hWnd;
	return false;
}
bool Window::ChangeDisplay(HINSTANCE hInstance, HWND hWnd)
{
	if (Press)
	{
		if (this->ChangeDevice(hInstance, hWnd, DisplayMode))
		{
			return true;
		}
	}
	return false;
}
Utility::Int_Vec2 Window::Get_Windows_Size()
{
	return Utility::Int_Vec2(this->Screen_Width_Size,this->Screen_Hiegth_Size);
}
LRESULT Window::WndProc(HWND in_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		KeyBoardDown(wParam, in_hWnd);
	}
	break;
	case WM_CLOSE://[X]は終了ボタン
		nID = MessageBox(in_hWnd, "終了しますか？", "シャットダウンメッセージ", MB_YESNO | MB_DEFBUTTON2);
		if (nID == IDYES)
		{
			DestroyWindow(in_hWnd);
		}
		else
		{
			return 0;
		}
		break;
	default:
		break;
	}
	return DefWindowProc(in_hWnd, uMsg, wParam, lParam);
}
