#pragma once

#include "MyObject.h"


class CMyCharacter : public CMyObject
{
protected:	
	RECT			 m_rcFrame[6][6];
	unsigned char    m_aniIndex;
	DWORD			 m_interval;
	float			 speed;

	CHARMOTION       m_aniType;

	Vector2			 m_vecDirection;
	Vector2          m_vecPosition;
	Vector2			 m_tmp[1000];
	CHARMOTION		 m_tmp2[1000];
	

	float			 m_mapPosition;
	int				 setData[5][3][10];

public:
	int				 count;

	CMyCharacter();
	~CMyCharacter();

	bool Create(char *filename);
	void OnDraw(int x, int y);
	int OnUpdate(DWORD tick);
	
	void SetAnimationChange(CHARMOTION ani);
	void SetPosition(float x, float y);


	bool ChkBreak();
	bool ChkMapMove();
	int RectChk();


	Vector2 GetPosition();
	Vector2 GetTmp(int count);
	CHARMOTION GetTmp2(int count);
	RECT GetRect();
	Vector2 GetDirection();
	CHARMOTION GetAniType();
	int GetCount();
	void SetDirection(float x, float y);
};

