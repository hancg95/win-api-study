// OpenGL_Templete.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
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

	RECT WindowRect;                            // �簢���� �»�ܰ� / ���ϴ� ���� ������
	WindowRect.left = (long)0;                    // ���� ���� 0���� ����
	WindowRect.right = (long)715;               // ������ ���� ��û�� �ʺ�� ����
	WindowRect.top = (long)0;                     // ���� ���� 0���� ����
	WindowRect.bottom = (long)780;             // �Ʒ��� ���� ��û�� ���̷� ����

	DWORD        dwExStyle;                        // ������ Ȯ�� ��Ÿ��
	DWORD        dwStyle;                          // ������ ��Ÿ��

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // ������ Ȯ�� ��Ÿ��
	dwStyle = WS_OVERLAPPEDWINDOW;                    // �������� ��Ÿ��

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);        // ���� ��û�� ũ��� ������ ũ�⸦ �����Ѵ�

	HWND hwnd = CreateWindowEx(dwExStyle,                // �� ������� Ȯ�彺Ÿ��
		"OpenGL_Templete",							    // Ŭ���� �̸�
		"DSGame",									   // ������ Ÿ��Ʋ
		WS_CLIPSIBLINGS |							    // �ʼ� ������ ��Ÿ��
		WS_CLIPCHILDREN |						        // �ʼ� ������ ��Ÿ��
		dwStyle,								    // ���õ� ������ ��Ÿ��
		0, 0,									       // â ��ġ
		WindowRect.right - WindowRect.left,			  // ������ â �ʺ� �����
		WindowRect.bottom - WindowRect.top,			   // ������ â ���̸� �����
		NULL,												     // �θ� ������ ����
		NULL,									     // �޴� ����
		hInstance,										// �ν��Ͻ�
		NULL);										 // WM_CREATE�� �ƹ��͵� �������� ����


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
		//������ �޼����� ������� �޼����� ó���Ѵ�.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else //�޼����� ���� ��� ���� ������ �����Ѵ�.
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
	wsprintf(tChar, "��ǥ : %d %d %d %d", (int)g_Mgr.g_Char.GetPosition().x, (int)g_Mgr.g_Char.GetPosition().y,(int)g_Mgr.g_Char.count, (int)g_Mgr.GetLife()); 
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

