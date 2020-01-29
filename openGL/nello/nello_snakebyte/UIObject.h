#pragma once
#include "MyObject.h"
class UIObject :
	public CMyObject
{
protected:
	RECT			 m_rcFrame;
	float			 speed;
	int				 twice;
	DWORD			 m_interval;

	Vector2			 m_vecDirection;
	Vector2          m_vecPosition;
public:
	UIObject();
	~UIObject();

	bool Create(char *filename);
	void OnDraw(int x, int y);
	void OnDraw();
	void OnUpdate(DWORD tick);
	void SetPosition(float x, float y);
	void SetRected();
	
};

