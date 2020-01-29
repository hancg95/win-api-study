#include "MapSubObject.h"


CMapSubObject::CMapSubObject()
{
}


CMapSubObject::~CMapSubObject()
{
}

void CMapSubObject::SetObectRect(int left, int top,
	int right, int bottom)
{
	m_rcImg.left = left; m_rcImg.top = top;
	m_rcImg.right = right; m_rcImg.bottom = bottom;
}

void CMapSubObject::SetPosition(float x, float y)
{
	m_Position.x = x; m_Position.y = y;
}

void CMapSubObject::Draw(dsTexture * pTexture)
{
	pTexture->Draw(m_Position.x, m_Position.y, m_rcImg.left, m_rcImg.top,
		m_rcImg.right, m_rcImg.bottom, 0);
}

