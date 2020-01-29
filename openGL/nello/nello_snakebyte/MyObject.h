#pragma once

#include "dsTexture.h"

struct Vector2
{
	float x;
	float y;
};

enum CHARMOTION
{
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3,
	WIN = 4,
	HIT = 5,
	ROPE = 4,
	TAKE = 5
};

class CMyObject
{
protected:
	dsTexture		*m_pSprite;

public:
	CMyObject();
	virtual ~CMyObject();

	virtual bool Create(char *filename) = 0;
	virtual void OnDraw(int x, int y) = 0;
	//virtual void OnUpdate(DWORD tick);
	//virtual int OnUpdate(DWORD tick);
	
};

