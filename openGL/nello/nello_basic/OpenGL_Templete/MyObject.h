#pragma once

#include "dsTexture.h"

enum CHARMOTION
{
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3,
	HIT = 4,
	WIN = 5
};

struct Vector2
{
	float x;
	float y;
};

class CMyObject
{
protected:
	dsTexture		*m_pSprite;
	CHARMOTION       m_aniType;
	unsigned char    m_aniIndex;

public:
	CMyObject();
	virtual ~CMyObject();
	virtual bool Create(char *filename);
	virtual void OnDraw(int x, int y);
	virtual void OnUpdate(DWORD tick);
	virtual void SetAnimationChange(CHARMOTION ani);
};

