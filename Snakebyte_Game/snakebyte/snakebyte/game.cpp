#include<windows.h>
#include<ctime>
#include<cstdlib>
#include<TCHAR.H>
#include<cmath>


const int BSIZE = 20; // �� �Ÿ�

typedef struct Snake// �� ����ü
{
	int count = 2; // ���� ��, �⺻�� 2;
	int x[100] = {}; 
	int y[100] = {};
}Snake;

typedef struct Ball // �� ����ü
{
	bool on[100] = {}; // �� on off ����ġ
	int x[100] = {};
	int y[100] = {};
}Ball;

void rectwall(HWND hwnd, HDC hdc, RECT rectView); // ȭ�鳡 �� ����
BOOL InCircle(int x, int y, int mx, int my);// ��ǥ �Ÿ� ��
double LengthPts(int x1, int y1, int x2, int y2); 
void ballcreate(Ball &ball, RECT &rectView, RECT &wall1, RECT &wall2, int level, RECT &wall3_1, RECT &wall3_2, RECT &wall3_3); //�� ����

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT	ps;
	static Snake snake; // �� ����ü
	static Ball ball; // �� ����ü
	HBRUSH hBrush, oldBrush; 
	static RECT rectView, wall1,wall2,wall3_1, wall3_2, wall3_3; //������ âũ�� �� ������ ��ֹ�
	static bool start, up, down, left, right; // ���� ���� ����ġ, Ű�Է� ����ġ
	static int level; // ���� �������� ����
	TCHAR text[100] = {}; // ������ �޽��� ��¿�
	switch (iMsg)
	{
	case WM_CREATE:

		GetClientRect(hwnd, &rectView); // ������ â ũ�� �޾ƿ���
		SetTimer(hwnd, 1, 100, NULL); // Ÿ�̸� ����
		start = up = down = left =  false; // �� ����ġ�� �ʱ�ȭ
		right = true; // �����ϸ� �ٷ� ���������� �� �� �ֵ���
		level = 1; // 1 ����
		snake.x[1] = 50; // �Ӹ� �ʱ�ȭ
		snake.y[1] = 30;
		snake.x[2] = 30; // ���� �ʱ�ȭ
		snake.y[2] = 30;
		wall1 = { (rectView.right / 2) - 150, (rectView.bottom / 2) - 10, (rectView.right / 2) + 150, (rectView.bottom / 2) + 10 }; // ù��° ��ֹ� ��ǥ ����
		wall2 = { (rectView.right / 2) - 10, (rectView.bottom / 2) - 150, (rectView.right / 2) + 10, (rectView.bottom / 2) + 150 }; // �ι�° ��ֹ� ��ǥ ����
		wall3_1 = { (rectView.right / 2) - 150, (rectView.bottom / 2) - 150, (rectView.right / 2) + -130, (rectView.bottom / 2) + 150 }; // ����° ��ֹ� ��ǥ ����
		wall3_2 = { (rectView.right / 2) - 150, (rectView.bottom / 2) - 150, (rectView.right / 2) + 150, (rectView.bottom / 2) - 130 };
		wall3_3 = { (rectView.right / 2) - 150, (rectView.bottom / 2) + 130, (rectView.right / 2) + 150, (rectView.bottom / 2) + 150 };
		wsprintf(text, TEXT("�ز����� �ε����� �ʰ� ��� ���� ��������!\n\n\'Enter\' �� ������ �����մϴ�."));
		MessageBox(GetFocus(), text, _T("Game Start"), MB_OK); // ���� ���� �޽���
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		wall1 = { (rectView.right / 2) - 150, (rectView.bottom / 2) - 10, (rectView.right / 2) + 150, (rectView.bottom / 2) + 10 }; // ù��° ��ֹ� ��ǥ ����
		wall2 = { (rectView.right / 2) - 10, (rectView.bottom / 2) - 150, (rectView.right / 2) + 10, (rectView.bottom / 2) + 150 }; // �ι�° ��ֹ� ��ǥ ����
		wall3_1 = { (rectView.right / 2) - 150, (rectView.bottom / 2) - 150, (rectView.right / 2) + -130, (rectView.bottom / 2) + 150 }; // ����° ��ֹ� ��ǥ ����
		wall3_2 = { (rectView.right / 2) - 150, (rectView.bottom / 2) - 150, (rectView.right / 2) + 150, (rectView.bottom / 2) - 130 };
		wall3_3 = { (rectView.right / 2) - 150, (rectView.bottom / 2) + 130, (rectView.right / 2) + 150, (rectView.bottom / 2) + 150 };
		
		for (int i = 2; i < snake.count; i++) // ���� ��ü ����
		{
			Ellipse(hdc, snake.x[i] - 10, snake.y[i] - 10, snake.x[i] + 10, snake.y[i] + 10);
		}

		hBrush = CreateSolidBrush(RGB(0, 0, 255)); //�Ķ� ���� ����
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, snake.x[snake.count] - 10, snake.y[snake.count] - 10, snake.x[snake.count] + 10, snake.y[snake.count] + 10);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(255, 0, 0)); //���� �Ӹ� ����
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, snake.x[1] - 10, snake.y[1] - 10, snake.x[1] + 10, snake.y[1] + 10);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);

		rectwall(hwnd, hdc, rectView); // ȭ�鳡

		Rectangle(hdc, wall1.left, wall1.top, wall1.right, wall1.bottom); // 1�ܰ� ��ֹ�
		switch (level)
		{
		case 2: // 2�ܰ� ��ֹ�
			Rectangle(hdc, wall2.left, wall2.top, wall2.right, wall2.bottom); 
			break;
		case 3: // 3�ܰ� ��ֹ�
			Rectangle(hdc, wall3_1.left, wall3_1.top, wall3_1.right, wall3_1.bottom);
			Rectangle(hdc, wall3_2.left, wall3_2.top, wall3_2.right, wall3_2.bottom);
			Rectangle(hdc, wall3_3.left, wall3_3.top, wall3_3.right, wall3_3.bottom);
			break;
		}
		
		hBrush = CreateSolidBrush(RGB(0, 255, 0)); // ���� �� �׸���
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		for (int i = 0; i < 10; i++) 
		{
			if(ball.on[i])
				Ellipse(hdc, ball.x[i] - 10, ball.y[i] - 10, ball.x[i] + 10, ball.y[i] + 10);
		}
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		EndPaint(hwnd, &ps);
		break;
	case WM_TIMER:
		if (start == false);
		else if (right)
		{
			for (int i = snake.count; 2 <= i; i--)//�ڷ� ���󰡴� ��ü
			{
				snake.x[i] = snake.x[i - 1];
				snake.y[i] = snake.y[i - 1];
			}
			snake.x[1] += 20;
			if (snake.x[1] + 10 > rectView.right - 20) snake.x[1] -= 20;
			else if (wall1.top <= snake.y[1] && snake.y[1] <= wall1.bottom && wall1.left <= snake.x[1] && snake.x[1] <= wall1.right) snake.x[1] -= 20; // ù���� ��ֹ� �̵� ���°�
			else if (wall2.top <= snake.y[1] && snake.y[1] <= wall2.bottom && wall2.left <= snake.x[1] && snake.x[1] <= wall2.right && level == 2) snake.x[1] -= 20; // �ι�° ��ֹ�
			else if (wall3_1.top <= snake.y[1] && snake.y[1] <= wall3_1.bottom && wall3_1.left <= snake.x[1] && snake.x[1] <= wall3_1.right && level == 3) snake.x[1] -= 20; // ����° ��ֹ�
			else if (wall3_2.top <= snake.y[1] && snake.y[1] <= wall3_2.bottom && wall3_2.left <= snake.x[1] && snake.x[1] <= wall3_2.right && level == 3) snake.x[1] -= 20;
			else if (wall3_3.top <= snake.y[1] && snake.y[1] <= wall3_3.bottom && wall3_3.left <= snake.x[1] && snake.x[1] <= wall3_3.right && level == 3) snake.x[1] -= 20;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (left)
		{
			for (int i = snake.count; 2 <= i; i--)//�ڷ� ���󰡴� ��ü
			{
				snake.x[i] = snake.x[i - 1];
				snake.y[i] = snake.y[i - 1];
			}
			snake.x[1] -= 20;
			if (snake.x[1] - 10 < rectView.left + 20) snake.x[1] += 20;
			else if (wall1.top <= snake.y[1] && snake.y[1] <= wall1.bottom && wall1.left <= snake.x[1] && snake.x[1] <= wall1.right) snake.x[1] += 20;
			else if (wall2.top <= snake.y[1] && snake.y[1] <= wall2.bottom && wall2.left <= snake.x[1] && snake.x[1] <= wall2.right && level == 2) snake.x[1] += 20;
			else if (wall3_1.top <= snake.y[1] && snake.y[1] <= wall3_1.bottom && wall3_1.left <= snake.x[1] && snake.x[1] <= wall3_1.right && level == 3) snake.x[1] += 20;
			else if (wall3_2.top <= snake.y[1] && snake.y[1] <= wall3_2.bottom && wall3_2.left <= snake.x[1] && snake.x[1] <= wall3_2.right && level == 3) snake.x[1] += 20;
			else if (wall3_3.top <= snake.y[1] && snake.y[1] <= wall3_3.bottom && wall3_3.left <= snake.x[1] && snake.x[1] <= wall3_3.right && level == 3) snake.x[1] += 20;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (down)
		{
			for (int i = snake.count; 2 <= i; i--)//�ڷ� ���󰡴� ��
			{
				snake.x[i] = snake.x[i - 1];
				snake.y[i] = snake.y[i - 1];
			}
			snake.y[1] += 20;
			if (snake.y[1] + 10 > rectView.bottom - 20) snake.y[1] -= 20;
			else if (wall1.left <= snake.x[1] && snake.x[1] <= wall1.right && wall1.top <= snake.y[1] && snake.y[1] <= wall1.bottom ) snake.y[1] -= 20;
			else if (wall2.left <= snake.x[1] && snake.x[1] <= wall2.right && wall2.top <= snake.y[1] && snake.y[1] <= wall2.bottom && level == 2) snake.y[1] -= 20;
			else if (wall3_1.left <= snake.x[1] && snake.x[1] <= wall3_1.right && wall3_1.top <= snake.y[1] && snake.y[1] <= wall3_1.bottom && level == 3) snake.y[1] -= 20;
			else if (wall3_2.left <= snake.x[1] && snake.x[1] <= wall3_2.right && wall3_2.top <= snake.y[1] && snake.y[1] <= wall3_2.bottom && level == 3) snake.y[1] -= 20;
			else if (wall3_3.left <= snake.x[1] && snake.x[1] <= wall3_3.right && wall3_3.top <= snake.y[1] && snake.y[1] <= wall3_3.bottom && level == 3) snake.y[1] -= 20;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (up)
		{
			for (int i = snake.count; 2 <= i; i--)//�ڷ� ���󰡴� ��
			{
				snake.x[i] = snake.x[i - 1];
				snake.y[i] = snake.y[i - 1];
			}
			snake.y[1] -= 20;
			if (snake.y[1] - 10 < rectView.top + 20) snake.y[1] += 20;
			else if (wall1.left <= snake.x[1] && snake.x[1] <= wall1.right && wall1.top <= snake.y[1] && snake.y[1] <= wall1.bottom && level) snake.y[1] += 20;
			else if (wall2.left <= snake.x[1] && snake.x[1] <= wall2.right && wall2.top <= snake.y[1] && snake.y[1] <= wall2.bottom && level == 2) snake.y[1] += 20;
			else if (wall3_1.left <= snake.x[1] && snake.x[1] <= wall3_1.right && wall3_1.top <= snake.y[1] && snake.y[1] <= wall3_1.bottom && level == 3) snake.y[1] += 20;
			else if (wall3_2.left <= snake.x[1] && snake.x[1] <= wall3_2.right && wall3_2.top <= snake.y[1] && snake.y[1] <= wall3_2.bottom && level == 3) snake.y[1] += 20;
			else if (wall3_3.left <= snake.x[1] && snake.x[1] <= wall3_3.right && wall3_3.top <= snake.y[1] && snake.y[1] <= wall3_3.bottom && level == 3) snake.y[1] += 20;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (InCircle(snake.x[1], snake.y[1], snake.x[snake.count], snake.y[snake.count]) && start) // ������ �ε��� �� - Ȧ��
		{
			start = !start;
			wsprintf(text, TEXT("������ �ε������ϴ�."));
			MessageBox(GetFocus(), text, _T("Game Over"), MB_OK); // ���� ���� �޽���
			exit(1);
		}
		else if (snake.count % 2 == 0 && snake.count != 2 && InCircle(snake.x[1], snake.y[1], snake.x[snake.count - 1], snake.y[snake.count - 1]) && start) // ������ �ε��� �� - ¦��
		{
			start = !start;
			wsprintf(text, TEXT("������ �ε������ϴ�."));
			MessageBox(GetFocus(), text, _T("Game Over"), MB_OK); // ���� ���� �޽���
			exit(1);
		}
		for (int i = 0; i < 10; i++) // �� �ε����� �Ա�
		{
			if (InCircle(ball.x[i], ball.y[i], snake.x[1], snake.y[1])&& ball.on[i])
			{
				ball.on[i] = false;
				snake.count++;
			}
			if (snake.count >= 12 && level<3) //���� ��
			{
				snake.count = 2; // ���� �ڷ�� �ʱ�ȭ
				level++;
				start = up = down = left = false;
				right = true;
				snake.x[1] = 50;
				snake.y[1] = 30;
				snake.x[2] = 30;
				snake.y[2] = 30;
				for (int i = 3; i <= 10; i++)
				{
					snake.x[i] = snake.y[i] = NULL;
				}
				ballcreate(ball, rectView, wall1, wall2, level, wall3_1, wall3_2, wall3_3);
				wsprintf(text, TEXT("%d �ܰ�"), level);
				MessageBox(GetFocus(), text, _T("Level Up!"), MB_OK);
				InvalidateRect(hwnd, NULL, TRUE);
			}
			else if (level >= 3 && snake.count >= 12 && start) // ���� Ŭ����
			{
				start = !start;
				wsprintf(text, TEXT("��� ���������� Ŭ���� �ϼ̽��ϴ�!"));
				MessageBox(GetFocus(), text, _T("Victory"), MB_OK); // ���� �������� Ŭ���� �޽���
				exit(1);
			}
		}
		
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RIGHT) // Ű���� ������ �� ���� ����ġ�� true�� �ϰ� �ٸ� ���� false�� �ٲ�
		{
			right = true;
			left = down = up = false;
		}
		else if (wParam == VK_LEFT)
		{
			left = true;
			right = down = up = false;
		}
		else if (wParam == VK_DOWN)
		{
			down = true;
			left = right = up = false;
		}
		else if (wParam == VK_UP)
		{
			up = true;
			left = down = right = false;
		}

		if (wParam == VK_RETURN) // �Ͻ� ���� �� ���� ����
		{
			start = (!start);
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_SIZE: //  â ũ�� �ٲܶ�
		GetClientRect(hwnd, &rectView);
		ballcreate(ball, rectView, wall1, wall2, level, wall3_1, wall3_2, wall3_3); // ���� �� ����
		break;
	case WM_DESTROY:
		HideCaret(hwnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ballcreate(Ball &ball, RECT &rectView, RECT &wall1, RECT &wall2, int level, RECT &wall3_1, RECT &wall3_2, RECT &wall3_3)
{
	for (int i = 0; i < 10; i++)
	{
		ball.on[i] = true; // �� ����ġ ��
		ball.x[i] = 30 + (rand() * 20) % (rectView.right - 60);
		ball.y[i] = 30 + (rand() * 20) % (rectView.bottom - 60);
		if (ball.x[i] < wall1.right + 10 && wall1.left - 10 < ball.x[i] && ball.y[i] > wall1.top - 10 && ball.y[i] < wall1.bottom + 10) i--;  // ��ֹ� ���ؼ� ����
		if ((ball.x[i] < wall2.right + 10 && wall2.left - 10 < ball.x[i] && ball.y[i] > wall2.top - 10 && ball.y[i] < wall2.bottom + 10) && level == 2) i--;
		if (((ball.x[i] < wall3_1.right + 10 && wall3_1.left - 10 < ball.x[i] && ball.y[i] > wall3_1.top - 10 && ball.y[i] < wall3_1.bottom + 10) ||
			(ball.x[i] < wall3_2.right + 10 && wall3_2.left - 10 < ball.x[i] && ball.y[i] > wall3_2.top - 10 && ball.y[i] < wall3_2.bottom + 10) ||
			(ball.x[i] < wall3_3.right + 10 && wall3_3.left - 10 < ball.x[i] && ball.y[i] > wall3_3.top - 10 && ball.y[i] < wall3_3.bottom + 10)) && level == 3) i--;
	}
}

double LengthPts(int x1, int y1, int x2, int y2)
{
	return(sqrt((float)((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))));
}

BOOL InCircle(int x, int y, int mx, int my)
{
	if (LengthPts(x, y, mx, my) < BSIZE) return TRUE;
	else return FALSE;
}

void rectwall(HWND hwnd, HDC hdc,RECT rectView) // ���ڶ� ��
{
	int over;
	GetClientRect(hwnd, &rectView); // ���� â ũ�� �޾Ƽ� ���� �� ����
	over = 0;
	while (over <= rectView.right)
	{
		Rectangle(hdc, over, 0, over + 20, 20);
		over += 20;
	}
	over = 0;
	while (over <= rectView.right)
	{
		Rectangle(hdc, over, rectView.bottom - 20, over + 20, rectView.bottom);
		over += 20;
	}
	over = 0;
	while (over <= rectView.bottom)
	{
		Rectangle(hdc, 0, over, 20, over + 20);
		over += 20;
	}
	over = 0;
	while (over <= rectView.bottom)
	{
		Rectangle(hdc, rectView.right - 20, over, rectView.right, over + 20);
		over += 20;
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	srand((unsigned)time(NULL));
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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("Snake Game"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		600,
		600,
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
