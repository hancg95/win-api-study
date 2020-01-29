#pragma once
#include "MyCharacter.h"
#include "MapObject.h"
#include "CatObject.h"
#include "DogObject.h"
#include "UIObject.h"
#include <list>

class Manager
{
protected:
	int round;
	int time;
	bool life;
	int score;
	int interval;
	bool start;

	
public:
	list<int> it;

	CMapObject    g_MapObj;
	CMyCharacter  g_Char;

	UIObject	  g_UI[4];
	DogObject	  g_Dog[4];
	CatObject g_Cat[2];
	Manager();
	~Manager();
	void Create();
	void ChkRect(int number);// �ѹ��� 10�� �ڸ��� ������Ʈ ���� 1�� �ڸ��� �ε�����
	void SetDogsAnimationChange(CHARMOTION ani);
	int DogCounting(int i);
	bool GetLife();
	bool GetStart();
	void SetStart(bool start);
	void ReStart();
};

