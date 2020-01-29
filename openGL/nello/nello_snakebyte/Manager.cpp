#include "Manager.h"



Manager::Manager()
{
}


Manager::~Manager()
{
}

void Manager::Create()
{
	round = 0;
	time = 30;
	life = true;
	score = 0;
	interval = 0;
	start = false;

	g_Char.Create("nello.png");
	g_MapObj.Create("map.png");
	g_Dog[0].Create("dog_lala.png");
	g_Dog[1].Create("dog_mir.png");
	g_Dog[2].Create("dog_queen.png");
	g_Dog[3].Create("dog_sulhe.png");
	g_Cat[0].Create("cat_blue.png");
	g_Cat[1].Create("cat_red.png");
	g_UI[0].Create("ui1.png");
	g_UI[1].Create("main.png");
	
	
	
	g_UI[1].SetRected();

	FILE *fp = fopen("setdata.txt", "rt");

	int round;
	int b[10];
	int d[10];
	int c[10];
	

	fscanf(fp, "%d", &round);
	fscanf(fp, "%d %d %d %d %d %d", &b[0], &b[1], &b[2], &b[3], &b[4], &b[5]);
	fscanf(fp, "%d %d %d %d %d %d %d %d", &d[0], &d[1], &d[2], &d[3], &d[4], &d[5], &d[6], &d[7]);
	fscanf(fp, "%d %d", &c[0], &c[1]);
	
	for (int i = 0; i < 4; i++)
	{
		// 맵 위치 세팅
	}
	for (int i = 0, j = 0; i < 4; i++,j+=2)
	{
		g_Dog[i].SetPosition(d[j], d[j + 1]);

	}
	g_Cat[0].SetPosition(c[0], c[1]);
	
	fclose(fp);
}

void Manager::ChkRect(int number)
{
	if (number != -1)
	{
		
		if (0 <= number && number < 5) // 개 충돌
		{
			int n = number;
			if (g_Dog[n].GetOnOff())
			{
				g_Dog[n].SetAniType(CHARMOTION::TAKE);
				g_Dog[n].SetOnOff(false);
				this->it.push_back(n);
				score++;
			}
		}
		if (10 <= number && number < 20) // 고양이 충돌
		{
			this->life = false;
		}
	}
}



void Manager::SetDogsAnimationChange(CHARMOTION ani)
{
	for (int i = 0; i < 4; i++)
	{
		if(!g_Dog[i].GetOnOff())
			g_Dog[i].SetAnimationChange(ani);
	}
	
}

int Manager::DogCounting(int i)
{
	int result = -1;
	list<int>::iterator iter = it.begin();
	for (int j = 1; iter != it.end(); iter++,j++)
	{
		if (i == *iter) result = j;
	}
	return result;
}

bool Manager::GetLife()
{
	return life;
}

bool Manager::GetStart()
{
	return start;
}
void Manager::SetStart(bool start)
{
	this->start = start;
}

void Manager::ReStart()
{
	life = true;
	start = false;
	g_Char.SetPosition(0.0f, 0.0f);
	g_Char.SetDirection(0.0f, 0.0f);
	it.clear();
	for (int i = 0; i < 4; i++)
	{
		g_Dog[i].SetOnOff(true);
	}
	FILE *fp = fopen("setdata.txt", "rt");

	int round;
	int b[10];
	int d[10];
	int c[10];


	fscanf(fp, "%d", &round);
	fscanf(fp, "%d %d %d %d %d %d", &b[0], &b[1], &b[2], &b[3], &b[4], &b[5]);
	fscanf(fp, "%d %d %d %d %d %d %d %d", &d[0], &d[1], &d[2], &d[3], &d[4], &d[5], &d[6], &d[7]);
	fscanf(fp, "%d %d", &c[0], &c[1]);

	for (int i = 0; i < 4; i++)
	{
		// 맵 위치 세팅
	}
	for (int i = 0, j = 0; i < 4; i++, j += 2)
	{
		g_Dog[i].SetPosition(d[j], d[j + 1]);

	}

	fclose(fp);
}