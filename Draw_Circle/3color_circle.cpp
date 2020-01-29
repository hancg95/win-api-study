#include <windows.h>
#include <TCHAR.H>
#include <stdlib.h>
#include <time.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	srand(time(NULL)); // 랜드를 랜덤으로 뿌리기 위한
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
#define BSIZEx 40
#define BSIZEy 20
double LengthPts(int x1, int y1, int x2, int y2)
{
	return(sqrt((float)((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))));
}

BOOL InRectangle(int x, int y, int mx, int my)
{
	if (LengthPts(x, y, mx, my) < BSIZEx) return TRUE;
	else return FALSE;
}
//
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x1, y1,x2,y2,x3,y3,ran1,ran2;
	static BOOL Selection1, Selection2, Selection3;
	int mx, my;
	HBRUSH hBrush,oldBrush;
	static RECT rectView;

	switch (iMsg)
	{
	case WM_CREATE:
		x1 = 100;  y1 = 50;
		x2 = 200;  y2 = 50;
		x3 = 300;  y3 = 50;
		Selection1 = Selection2 = Selection3 = FALSE;
		GetClientRect(hwnd, &rectView);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hBrush = CreateSolidBrush(RGB(255, 0, 0)); //빨간 사각형
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, x1 - BSIZEx, y1 - BSIZEy, x1 + BSIZEx, y1 + BSIZEy); 
		SelectObject(hdc, oldBrush);
		//DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(0, 0, 255)); //파란 사각형
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, x2 - BSIZEx, y2 - BSIZEy, x2 + BSIZEx, y2 + BSIZEy);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		Rectangle(hdc, x3 - BSIZEx, y3 - BSIZEy, x3 + BSIZEx, y3 + BSIZEy);//흰 사각형
		ran1 = rand() % rectView.right; //윈도우 렉트 크기 값으로 나머지 값을 구해서 공이 윈도우 창에 벗어나지 않게 함
		ran2 = rand() % rectView.bottom; //x의 끝값인 right와 y의 끝값인 bottom
		if (Selection1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, ran1 - BSIZEy, ran2 - BSIZEy, ran1 + BSIZEy, ran2 + BSIZEy); // 빨간 공 생성
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		else if (Selection2) {
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush); // 파란 공 생성
			Ellipse(hdc, ran1 - BSIZEy, ran2 - BSIZEy, ran1 + BSIZEy, ran2 + BSIZEy);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		else if(Selection3)
			Ellipse(hdc, ran1 - BSIZEy, ran2 - BSIZEy, ran1 + BSIZEy, ran2 + BSIZEy); // 흰 공 생성
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		hdc = BeginPaint(hwnd, &ps);
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (InRectangle(x1, y1, mx, my)) Selection1 = TRUE; // 빨간 칸 눌렀을 때
		else if (InRectangle(x2, y2, mx, my)) Selection2 = TRUE; //파란 칸 눌렀을 떄
		else if (InRectangle(x3, y3, mx, my)) Selection3 = TRUE; //흰 칸 눌렀을 때
		InvalidateRgn(hwnd, NULL, FALSE); // FALSE로 해서 수정한 부분만 새로고침함
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONUP:
		Selection1 = Selection2 = Selection3 =  FALSE;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}