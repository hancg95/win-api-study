#define _Height 340-55
#define _Width 810
#include <windows.h>
#include <TCHAR.H>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND     hwnd;
	MSG		 msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("윈도우프로그래밍_과제_20141825_한창기-3"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		_Width,
		_Height+55,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt = { 0,0,300,300 };
	static TCHAR str[20][100];
	static int count = 0, ycount = 0;
	switch (iMsg)
	{
	case WM_CHAR:
		hdc = GetDC(hwnd);
		if (wParam == VK_RETURN) // 엔터 입력되면 개행
		{
			if (ycount < 19) // 엔터, 20행 넘어가는거 방지
			{
				count = 0;
				ycount++;
			}
		}
		else if (wParam == VK_BACK) // 단어 및 줄 삭제
		{
			if (count > 0)
			{
				count--;
			}
			else if (count <= 0 && ycount > 0)
			{
				count = _tcslen(str[--ycount]);
				count--;
			}
		}
		else if (count >= 99) // 99글자 입력되면 개행
		{
			if (count >= 99 && ycount < 19)// 에러 방지
			{
				count = 0;
				ycount++;
				str[ycount][count++] = wParam;
			}
		}
		else str[ycount][count++] = wParam;
		str[ycount][count] = NULL;
		InvalidateRgn(hwnd, NULL, TRUE);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (int i = 0; i <= ycount; i++)
		{
			TextOut(hdc, 0, _Height - (i * 15), str[i], _tcslen(str[i]));
		}
		EndPaint(hwnd, &ps);
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}