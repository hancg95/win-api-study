// OpenGL_Templete.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "global.h"
#include "dsTexture.h"
#include <time.h>
#include "dsOpenALSoundManager.h"
#include "MyCharacter.h"
#include "MapObject.h"
#include "CatObject.h"
#include "DogObject.h"
#include "Manager.h"

CFrameOpenGL  g_OpenGL;
HDC           g_hDC;

Manager		  g_Mgr;

//CMapObject    g_MapObj;
//CMyCharacter  g_Char;
//
//DogObject g_Dog[4];
//CatObject g_Cat[2];

DWORD         g_tick;


void OnIdle();
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS   wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = NULL;
	wndclass.hCursor = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "OpenGL_Templete";

	if (RegisterClass(&wndclass) == 0)
	{
		return 0;
	}

	RECT WindowRect;                            // 사각형의 좌상단과 / 우하단 값을 저장함
	WindowRect.left = (long)0;                    // 왼쪽 값을 0으로 지정
	WindowRect.right = (long)715;               // 오른쪽 값을 요청된 너비로 지정
	WindowRect.top = (long)0;                     // 위쪽 값을 0으로 지정
	WindowRect.bottom = (long)780;             // 아래쪽 값을 요청된 높이로 지정

	DWORD        dwExStyle;                        // 윈도우 확장 스타일
	DWORD        dwStyle;                          // 윈도우 스타일

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // 윈도우 확장 스타일
	dwStyle = WS_OVERLAPPEDWINDOW;                    // 윈도우즈 스타일

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);        // 실제 요청된 크기로 윈도우 크기를 조정한다

	HWND hwnd = CreateWindowEx(dwExStyle,                // 본 윈도우용 확장스타일
		"OpenGL_Templete",							    // 클래스 이름
		"DSGame",									   // 윈도우 타이틀
		WS_CLIPSIBLINGS |							    // 필수 윈도우 스타일
		WS_CLIPCHILDREN |						        // 필수 윈도우 스타일
		dwStyle,								    // 선택된 윈도우 스타일
		0, 0,									       // 창 위치
		WindowRect.right - WindowRect.left,			  // 조정된 창 너비를 계산함
		WindowRect.bottom - WindowRect.top,			   // 조정된 창 높이를 계산함
		NULL,												     // 부모 윈도우 없음
		NULL,									     // 메뉴 없음
		hInstance,										// 인스턴스
		NULL);										 // WM_CREATE에 아무것도 전달하지 않음


	if (hwnd == NULL)
	{
		return 0;
	}
	

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);


	g_Mgr.Create();
	/*g_Char.Create("nello.png");
	g_MapObj.Create("map.png");
	g_Dog[0].Create("dog_lala.png");
	g_Dog[1].Create("dog_mir.png");
	g_Dog[2].Create("dog_queen.png");
	g_Dog[3].Create("dog_sulhe.png");
	g_Cat[0].Create("cat_blue.png");
	g_Cat[1].Create("cat_red.png");*/



	dsOpenALSoundManager *pSoundManger = GetOpenALSoundManager();
	dsSound *pSound = pSoundManger->LoadSound("back.wav", true);
	if (pSound)
	{
		pSound->Play();
	}	

	g_tick = GetTickCount();

	MSG msg;
	while (1)
	{
		//윈도우 메세지가 있을경우 메세지를 처리한다.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else //메세지가 없을 경우 게임 루프를 실행한다.
		{
			OnIdle();
		}
	}

	ReleaseDC(hwnd, g_hDC);
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_LEFT: 
			g_Mgr.g_Char.SetAnimationChange(CHARMOTION::LEFT);
			break;
		case VK_RIGHT:
			g_Mgr.g_Char.SetAnimationChange(CHARMOTION::RIGHT);
			break;
		case VK_UP:
			g_Mgr.g_Char.SetAnimationChange(CHARMOTION::UP);
			break;
		case VK_DOWN:
			g_Mgr.g_Char.SetAnimationChange(CHARMOTION::DOWN);
			break;
		case VK_ESCAPE:
			g_Mgr.ReStart();
		case VK_RETURN:
			g_Mgr.SetStart(true);
			break;
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{
	}
	break;
	case WM_CREATE:
	{
		g_hDC = GetDC(hWnd);

		g_OpenGL.Create(g_hDC);
	}
	break;
	case WM_SIZE:
	{
		int width = LOWORD(lParam);
		int height = HIWORD(lParam);

		g_OpenGL.SetSize(width, height);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}


	return DefWindowProc(hWnd, msg, wParam, lParam);
}


void OnIdle()
{
	DWORD	tickCount = GetTickCount();

	TCHAR tChar[100] = { '\0', };
	wsprintf(tChar, "좌표 : %d %d %d %d", (int)g_Mgr.g_Char.GetPosition().x, (int)g_Mgr.g_Char.GetPosition().y,(int)g_Mgr.g_Char.count, (int)g_Mgr.GetLife()); 
	TextOut(g_hDC, 0, 0, TEXT(tChar), lstrlen(tChar));
	g_OpenGL.BeginRender();	

	g_Mgr.g_MapObj.OnDrawBackground(0, 0);



	g_Mgr.g_Cat[0].OnDraw();
	g_Mgr.g_Dog[0].OnDraw();
	g_Mgr.g_Dog[1].OnDraw();
	g_Mgr.g_Dog[2].OnDraw();
	g_Mgr.g_Dog[3].OnDraw();



	g_Mgr.g_Char.OnDraw(300, 300);

	g_Mgr.g_MapObj.OnDraw(300, 300);
	
	if (g_Mgr.GetStart())
	{
		if (!g_Mgr.GetLife())
		{
			g_Mgr.g_UI[0].OnDraw(120, 215);
		}
		else
		{

			g_Mgr.ChkRect(
				g_Mgr.g_Char.OnUpdate(tickCount - g_tick)
			);
			g_Mgr.g_Dog[0].OnUpdate(tickCount - g_tick, &g_Mgr.g_Char, g_Mgr.DogCounting(0));
			g_Mgr.g_Dog[1].OnUpdate(tickCount - g_tick, &g_Mgr.g_Char, g_Mgr.DogCounting(1));
			g_Mgr.g_Dog[2].OnUpdate(tickCount - g_tick, &g_Mgr.g_Char, g_Mgr.DogCounting(2));
			g_Mgr.g_Dog[3].OnUpdate(tickCount - g_tick, &g_Mgr.g_Char, g_Mgr.DogCounting(3));

			g_Mgr.g_Cat[0].OnUpdate(tickCount - g_tick);
		}
	}
	else
	{
		g_Mgr.g_UI[1].OnDraw(0, 0);
	}


	g_OpenGL.EndRender(g_hDC);

	g_tick = tickCount;
}

