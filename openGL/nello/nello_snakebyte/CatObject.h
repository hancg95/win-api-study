#pragma once
#include "MyObject.h"
class CatObject :
	public CMyObject
{
protected:
	RECT			 m_rcFrame[4][3];
	CHARMOTION       m_aniType;
	float			 speed;
	int				 twice;

	unsigned char    m_aniIndex;
	DWORD			 m_interval;

	Vector2			 m_vecDirection;
	Vector2          m_vecPosition;
public:
	CatObject();
	~CatObject();

	bool Create(char *filename);
	void OnDraw(int x, int y);
	void OnDraw();
	void OnUpdate(DWORD tick);
	void SetPosition(float x, float y);
	RECT GetRect();
};

