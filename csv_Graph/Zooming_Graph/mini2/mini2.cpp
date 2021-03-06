// mini2.cpp: 응용 프로그램의 진입점을 정의합니다.
//
#include "stdafx.h"
#include "mini2.h"

const int MAX_LENGTH = 2000;
const int DATA_LENGTH = 100;

struct Record
{
	char item[MAX_LENGTH];
	char Xvalues[MAX_LENGTH];
	char Yvalues[MAX_LENGTH];
} records[15000];

void textchart(HWND hWnd, PAINTSTRUCT ps, HDC hdc, BOOL wheel);
BOOL check(POINT point, Record records);

#define MAX_LOADSTRING 100

// 전역 변수:
RECT mouse;
POINT logm,point; 
BOOL onoff = FALSE;
BOOL wheel = TRUE;
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

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
    LoadStringW(hInstance, IDC_MINI2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINI2));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINI2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MINI2);
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
      CW_USEDEFAULT, 0,700, 600, nullptr, nullptr, hInstance, nullptr);

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
	mouse = { logm.x + 5,logm.y - 5,logm.x + 155,logm.y + 20 };
	//mouse = { logm.x - 30,logm.y - 30,logm.x + 30,logm.y + 30 };
	PAINTSTRUCT ps;
	HDC hdc;
	//static COLORREF logColor; // 타이머 좌표 rgb
    switch (message)
    {
	case WM_CREATE:
		SetTimer(hWnd, 1, 500, NULL); // 0.5초 마다
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
			int index = 0;
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
			case IDM_OPEN:
				FILE * fp;
				char line[MAX_LENGTH];
				//  struct Record records[15000];
				fopen_s(&fp,"item.csv", "rt"); //csv파일 열기
				
				while (NULL != (fgets(line, MAX_LENGTH, fp)))
				{
					int len = strlen(line);
					line[len - 1] = '\0';
					char* p = line;
					char* q = p;
					while (',' != (*q)) q++;
					*q = '\0';
					strcpy_s(records[index].item, p);

					q++;
					p = q;
					while (',' != (*q)) q++;
					*q = '\0';
					strcpy_s(records[index].Xvalues, p);

					q++;
					p = q;
					while ('\0' != (*q)) q++;
					strcpy_s(records[index].Yvalues, p);

					index++;
				}
				fclose(fp);
				onoff = TRUE;
				InvalidateRect(hWnd, NULL, TRUE);
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
			HBRUSH hBrush, oldBrush;
			HPEN hPen, oldPen;
            hdc = BeginPaint(hWnd, &ps);
			textchart(hWnd, ps, hdc,wheel); // 차트 글자
			Rectangle(hdc, 55, 0, 555, 510);
			TextOut(hdc, 575, 30, _T("방향키 ↑↓"), 6);
			TextOut(hdc, 575, 50, _T("누르면 변환"), 6);
			TextOut(hdc, 577, 490, _T("20141825"), 8);
			TextOut(hdc, 582, 510, _T("한창기"), 3);
			if (onoff)
			{
				for (int i = 0; i <= DATA_LENGTH; i++)
				{
					double x = atof(records[i].Xvalues);
					double y = atof(records[i].Yvalues);
					if ((x<-2.0||x>2.0) && y > 0.95)
					{
						hBrush = CreateSolidBrush(RGB(255, 0, 0));
						oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
						hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
					}
					else
					{
						hBrush = CreateSolidBrush(RGB(0, 0, 0));
						oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
						hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
						oldPen = (HPEN)SelectObject(hdc, hPen);
					}
					if (wheel)
						if (y <= 0.95)
							y = 500 - (y * 110.52); //115..
						else if (y <= 0.9625)
							y = 395 - (y * 129.87);
						else if (y <= 0.975)
							y = 270 - (y * 128.2);
						else
							y = 145 - (y * 135);
					else
						y = 500 - (y * 488.07); //y좌표
					if (x < 0)
						x = 285 + (x * 45); //음수일때 x좌표
					else if (x >= 0)
						x = 285+ (x * 53); //양수일때 x좌표
					Ellipse(hdc, x - 2, y - 2, x + 2, y + 2);
					SelectObject(hdc, oldBrush);
					SelectObject(hdc, oldPen);
					DeleteObject(hBrush);
					DeleteObject(hPen);

				}
			}
			if (GetPixel(hdc, point.x, point.y) == RGB(0, 0, 0) || GetPixel(hdc, point.x, point.y) == RGB(255, 0, 0))
			{
				//TextOut(hdc, point.x, point.y, _T("test"), 4);
				
				for (int i = 0; i <= DATA_LENGTH; i++)
				{
					if (check(point, records[i]))
					{
						TCHAR print[256] = { 0, };
						MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, records[i].item, strlen(records[i].item), print, 256);
						TCHAR tmp1[256] = { 0, };
						MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, records[i].Xvalues, strlen(records[i].Xvalues), tmp1, 256);
						TCHAR tmp2[256] = { 0, };
						MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, records[i].Yvalues, strlen(records[i].Yvalues), tmp2, 256);
						_tcscat_s(print, _T("("));
						_tcscat_s(print, tmp1);
						_tcscat_s(print, _T(", "));
						_tcscat_s(print, tmp2);
						_tcscat_s(print, _T(")"));
						Rectangle(hdc, mouse.left,mouse.top,mouse.right,mouse.bottom);
						TextOut(hdc, point.x+15, point.y, print, _tcslen(print));//item(45,76)
						
					}
				}
			}
			EndPaint(hWnd, &ps);
        }
        break;
	case WM_TIMER:
		logm = point;
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		InvalidateRect(hWnd, &mouse, FALSE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			wheel = TRUE;
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		case VK_DOWN:
			wheel = FALSE;
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		break;
    case WM_DESTROY:
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

void textchart(HWND hWnd, PAINTSTRUCT ps, HDC hdc,BOOL wheel)
{
	if (wheel)
	{
		TextOut(hdc, 10, 10, _T(" 1"), 2);//세로
		TextOut(hdc, 10, 135, _T("0.975"), 5);
		TextOut(hdc, 10, 260, _T("0.9625"), 6);
		TextOut(hdc, 10, 385, _T("0.95"), 4);
		TextOut(hdc, 10, 510, _T(" 0  ,   -5"), 10);//가로
		TextOut(hdc, 85, 510, _T("-4"), 2);
		TextOut(hdc, 135, 510, _T("-3"), 2);
		TextOut(hdc, 185, 510, _T("-2"), 2);
		TextOut(hdc, 235, 510, _T("-1"), 2);
		TextOut(hdc, 285, 510, _T(" 0"), 2);
		TextOut(hdc, 335, 510, _T(" 1"), 2);
		TextOut(hdc, 385, 510, _T(" 2"), 2);
		TextOut(hdc, 435, 510, _T(" 3"), 2);
		TextOut(hdc, 485, 510, _T(" 4"), 2);
		TextOut(hdc, 535, 510, _T(" 5"), 2);
	}
	else
	{
		TextOut(hdc, 10, 10, _T(" 1"), 2);//세로
		TextOut(hdc, 10, 60, _T("0.9"), 3);
		TextOut(hdc, 10, 110, _T("0.8"), 3);
		TextOut(hdc, 10, 160, _T("0.7"), 3);
		TextOut(hdc, 10, 210, _T("0.6"), 3);
		TextOut(hdc, 10, 260, _T("0.5"), 3);
		TextOut(hdc, 10, 310, _T("0.4"), 3);
		TextOut(hdc, 10, 360, _T("0.3"), 3);
		TextOut(hdc, 10, 410, _T("0.2"), 3);
		TextOut(hdc, 10, 460, _T("0.1"), 3);
		TextOut(hdc, 10, 510, _T(" 0  ,   -5"), 10);//가로
		TextOut(hdc, 85, 510, _T("-4"), 2);
		TextOut(hdc, 135, 510, _T("-3"), 2);
		TextOut(hdc, 185, 510, _T("-2"), 2);
		TextOut(hdc, 235, 510, _T("-1"), 2);
		TextOut(hdc, 285, 510, _T(" 0"), 2);
		TextOut(hdc, 335, 510, _T(" 1"), 2);
		TextOut(hdc, 385, 510, _T(" 2"), 2);
		TextOut(hdc, 435, 510, _T(" 3"), 2);
		TextOut(hdc, 485, 510, _T(" 4"), 2);
		TextOut(hdc, 535, 510, _T(" 5"), 2);
	}
}
double LengthPts(int x1, int y1, int x2, int y2)
{
	return(sqrt((float)((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))));
}

BOOL InCircle(int x, int y, int mx, int my)
{
	if (LengthPts(x, y, mx, my) < 3) return TRUE;
	else return FALSE;
}
BOOL check(POINT point, Record records)
{
	double x = atof(records.Xvalues);
	double y = atof(records.Yvalues);
	if (wheel)
		if (y <= 0.95)
			y = 500 - (y * 110.52); //115..
		else if (y <= 0.9625)
			y = 395 - (y * 129.87);
		else if (y <= 0.975)
			y = 270 - (y * 128.2);
		else
			y = 145 - (y * 135);
	else
		y = 500 - (y * 488.07); //y좌표
	if (x < 0)
		x = 285 + (x * 45); //음수일때 x좌표
	else if (x >= 0)
		x = 285 + (x * 53); //양수일때 x좌표
	return InCircle(x, y, point.x, point.y);
}
