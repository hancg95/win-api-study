#pragma once

#include "MyObject.h"

class CMyCharacter : public CMyObject
{
protected:	
	RECT			 m_rcFrame[6][6];
	DWORD			 m_interval;

	

	Vector2			 m_vecDirection;
	Vector2          m_vecPosition;

public:
	CMyCharacter();
	~CMyCharacter();

	//bool Create(char *filename);
	//void OnDraw(int x, int y);
	void OnDraw();
	void OnUpdate(DWORD tick);

	void SetAnimationChange(CHARMOTION ani);
};

