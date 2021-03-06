// mini3_S.cpp: 응용 프로그램의 진입점을 정의합니다.
//
#include "stdafx.h"
#include "mini3_S.h"

#define MAX_LOADSTRING 100
#define WM_ASYNC WM_USER+2

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
BOOL line,circle,rect, Draw;
POINT FM = { 50,50 }, OM{ 50,50 }, EM;
TCHAR figure[2] = {}, x[10] = {}, y[10] = {};

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MINI3S, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINI3S));

    MSG msg;

    // 기본 메시지 루프입니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINI3S));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MINI3S);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hButton;
	CHOOSECOLOR COLOR;
	static COLORREF tmp[16], color;
	HBRUSH hBrush, OldBrush;
	HPEN hPen, OldPen;
	int i;
	HDC hdc;
	PAINTSTRUCT ps;
	static WSADATA wsadata;
	static SOCKET s, cs;
	static TCHAR msg[200];
	static SOCKADDR_IN addr = { 0 }, c_addr;
	int size,msgLen;
	char buffer[100];
	char buffer_s[100] = {};
	char tmpx[10] = {}, tmpy[10] = {};

	TCHAR print[256] = { 0, };
    switch (message)
    {
	case WM_CREATE:
		hButton = CreateWindow(
			_T("button"),
			_T("전송"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			500, 450, //좌표
			100, 25, //크기
			hWnd,
			(HMENU)IDC_BUTTON,
			hInst,
			NULL
		);
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		s = socket(AF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		bind(s, (LPSOCKADDR)&addr, sizeof(addr));
		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_ACCEPT);
		if (listen(s, 5) == -1)
			return 0;
		break;
	case WM_ASYNC:
		switch (lParam)
		{
		case FD_ACCEPT:
			size = sizeof(c_addr);
			cs = accept(s, (LPSOCKADDR)&c_addr, &size);
			WSAAsyncSelect(cs, hWnd, WM_ASYNC, FD_READ);
			break;
		case FD_READ:
			msgLen = recv(cs, buffer, 100, 0);
			buffer[msgLen] = NULL;
#ifdef _UNICODE
			msgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
			MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), msg, msgLen);
			msg[msgLen] = NULL;
#else
			strcpy_s(msg, buffer); //주석 ㄱ
			

#endif
			TCHAR *tok;
			tok = _wcstok(msg, _T(","));
			_tcscpy(figure, tok);
			tok = _wcstok(NULL, _T(","));
			_tcscpy(x, tok);
			tok = _wcstok(NULL, _T(","));
			_tcscpy(y, tok);
			EM.x = _ttoi(x);
			EM.y = _ttoi(y);
			if (_ttoi(figure) == 1)
			{
				line = TRUE;
				circle = rect = FALSE;
			}
			else if (_ttoi(figure) == 2)
			{
				circle = TRUE;
				line = rect = FALSE;
			}
			else if (_ttoi(figure) == 3)
			{
				rect = TRUE;
				line = circle = FALSE;
			}
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		default:
			break;
		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
			case IDM_COLORDLG:
				for (i = 0; i < 16; i++)
					tmp[i] = RGB(rand() % 256, rand() % 256, rand() % 256);
				memset(&COLOR, 0, sizeof(CHOOSECOLOR));
				COLOR.lStructSize = sizeof(CHOOSECOLOR);
				COLOR.hwndOwner = hWnd;
				COLOR.lpCustColors = tmp;
				COLOR.Flags = CC_FULLOPEN;
				if (ChooseColor(&COLOR) != 0)
				{
					color = COLOR.rgbResult;
					InvalidateRgn(hWnd, NULL, TRUE);
				}
				break;
			case IDM_LINE:
				line = TRUE;
				circle = rect = FALSE;
				break;
			case IDM_CIRCLE:
				circle = TRUE;
				line = rect = FALSE;
				break;
			case IDM_RECT:
				rect = TRUE;
				line = circle = FALSE;
				break;
			case IDC_BUTTON:
				
				if (cs == INVALID_SOCKET)
					break;
				sprintf_s(tmpx,"%d", EM.x);
				sprintf_s(tmpy, "%d", EM.y);
				if (line)
					strcat_s(buffer_s, "1,");
				else if (circle)
					strcat_s(buffer_s, "2,");
				else if (rect)
					strcat_s(buffer_s, "3,");
				strcat_s(buffer_s, tmpx);
				strcat_s(buffer_s, ",");
				strcat_s(buffer_s, tmpy);
				send(cs, buffer_s, strlen(buffer_s), 0);
				break;
			case IDC_RED:
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
			hBrush = CreateSolidBrush(color);
			OldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			hPen = CreatePen(PS_SOLID, 1, color);
			OldPen = (HPEN)SelectObject(hdc, hPen);
			if (line)
			{
				MoveToEx(hdc, FM.x, FM.y,NULL);
				LineTo(hdc, EM.x, EM.y);
			}
			else if (circle)
			{
				Ellipse(hdc, FM.x, FM.y, EM.x, EM.y);
			}
			else if (rect)
			{
				Rectangle(hdc, FM.x, FM.y, EM.x, EM.y);
			}
			SelectObject(hdc, OldBrush);
			SelectObject(hdc, OldPen);
			DeleteObject(hBrush);
			DeleteObject(hPen);
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN:
		Draw = TRUE;
		break;
	case WM_LBUTTONUP:
		Draw = FALSE;
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		if (Draw)
		{
			EM.x = LOWORD(lParam);
			EM.y = HIWORD(lParam);
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;
    case WM_DESTROY:
		closesocket(s);
		WSACleanup();
		PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
