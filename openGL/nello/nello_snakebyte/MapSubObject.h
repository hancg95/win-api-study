#pragma once
#include <Windows.h>
#include "MyObject.h"

class CMapSubObject
{
protected:
	RECT	m_rcImg;
	Vector2 m_Position;

public:
	CMapSubObject();
	~CMapSubObject();

	void SetPosition(float x, float y);
	void SetObectRect(int left, int top, int right, int bottom);
	void Draw(dsTexture * pTexture);
	
};

