#pragma once
#include "MyObject.h"
#include "MyCharacter.h"
class DogObject :
	public CMyObject
{
protected:
	bool			 onoff;
	int				 twice;
	RECT			 m_rcFrame[6][3]; //도그 만드는중
	CHARMOTION       m_aniType;

	unsigned char    m_aniIndex;
	DWORD			 m_interval;

	Vector2			 m_vecDirection;
	Vector2          m_vecPosition;
	Vector2			 vecTmp;
public:
	int				 count;
	DogObject();
	~DogObject();

	bool Create(char *filename);
	void OnDraw(int x, int y);
	void OnDraw();
	void OnUpdate(DWORD tick,CMyCharacter *g_Char, int num);
	
	void SetPosition(float x, float y);
	void SetOnOff(bool onOff);
	void SetAnimationChange(CHARMOTION ani);
	void SetAniType(CHARMOTION ani);

	RECT GetRect();
	bool GetOnOff();
	Vector2 GetPosition();
	int GetTwice();
};

