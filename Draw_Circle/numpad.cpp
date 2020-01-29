#include <windows.h>
#include <TCHAR.H>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND 	 hwnd;
	MSG 	 msg;
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
		_T("Window Title Name"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
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

#include <math.h>
#define BSIZE 30
double LengthPts(int x1, int y1, int x2, int y2)
{
	return(sqrt((float)((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))));
}

BOOL InCircle(int x, int y, int mx, int my)
{
	if (LengthPts(x, y, mx, my) < BSIZE) return TRUE;
	else return FALSE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	static BOOL Selection[10] = {};
	int mx, my;
	HBRUSH hBrush[10], oldBrush;

	switch (iMsg)
	{
	case WM_CREATE:
		for (int i = 0; i < 10; i++)Selection[i] = FALSE;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hBrush[7] = CreateSolidBrush(RGB(255, 0, 0)); 
		if (Selection[7])
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[7]);
		Ellipse(hdc, 50 - BSIZE, 50 - BSIZE, 50 + BSIZE, 50 + BSIZE);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush[7]);
		hBrush[8] = CreateSolidBrush(RGB(255, 0, 0));
		if (Selection[8])
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[8]);
		Ellipse(hdc, 150 - BSIZE, 50 - BSIZE, 150 + BSIZE, 50 + BSIZE);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush[8]);
		hBrush[9] = CreateSolidBrush(RGB(255, 0, 0));
		if (Selection[9])
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[9]);
		Ellipse(hdc, 250 - BSIZE, 50 - BSIZE, 250 + BSIZE, 50 + BSIZE);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush[9]);
		hBrush[4] = CreateSolidBrush(RGB(255, 0, 0));
		if (Selection[4])
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[4]);
		Ellipse(hdc, 50 - BSIZE, 150 - BSIZE, 50 + BSIZE, 150 + BSIZE);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush[4]);
		hBrush[5] = CreateSolidBrush(RGB(255, 0, 0));
		if (Selection[5])
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[5]);
		Ellipse(hdc, 150 - BSIZE, 150 - BSIZE, 150 + BSIZE, 150 + BSIZE);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush[5]);
		hBrush[6] = CreateSolidBrush(RGB(255, 0, 0));
		if (Selection[6])
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[6]);
		Ellipse(hdc, 250 - BSIZE, 150 - BSIZE, 250 + BSIZE, 150 + BSIZE);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush[6]);
		hBrush[1] = CreateSolidBrush(RGB(255, 0, 0));
		if (Selection[1])
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[1]);
		Ellipse(hdc, 50 - BSIZE, 250 - BSIZE, 50 + BSIZE, 250 + BSIZE);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush[1]);
		hBrush[2] = CreateSolidBrush(RGB(255, 0, 0));
		if (Selection[2])
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[2]);
		Ellipse(hdc, 150 - BSIZE, 250 - BSIZE, 150 + BSIZE, 250 + BSIZE);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush[2]);
		hBrush[3] = CreateSolidBrush(RGB(255, 0, 0));
		if (Selection[3])
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[3]);
		Ellipse(hdc, 250 - BSIZE, 250 - BSIZE, 250 + BSIZE, 250 + BSIZE);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush[3]);

		TextOut(hdc, 50, 50, _T("7"), 1);
		TextOut(hdc, 150, 50, _T("8"), 1);
		TextOut(hdc, 250, 50, _T("9"), 1);
		TextOut(hdc, 50, 150, _T("4"), 1);
		TextOut(hdc, 150, 150, _T("5"), 1);
		TextOut(hdc, 250, 150, _T("6"), 1);
		TextOut(hdc, 50, 250, _T("1"), 1);
		TextOut(hdc, 150, 250, _T("2"), 1);
		TextOut(hdc, 250, 250, _T("3"), 1);
		
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_NUMPAD1:
			Selection[1] = TRUE;
			break;
		case VK_NUMPAD2:
			Selection[2] = TRUE;
			break;
		case VK_NUMPAD3:
			Selection[3] = TRUE;
			break;
		case VK_NUMPAD4:
			Selection[4] = TRUE;
			break;
		case VK_NUMPAD5:
			Selection[5] = TRUE;
			break;
		case VK_NUMPAD6:
			Selection[6] = TRUE;
			break;
		case VK_NUMPAD7:
			Selection[7] = TRUE;
			break;
		case VK_NUMPAD8:
			Selection[8] = TRUE;
			break;
		case VK_NUMPAD9:
			Selection[9] = TRUE;
			break;
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_KEYUP:
		for (int i = 0; i <= 9; i++) Selection[i] = FALSE;
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}