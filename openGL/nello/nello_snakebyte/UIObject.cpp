#include "UIObject.h"



UIObject::UIObject()
{
}


UIObject::~UIObject()
{
}

bool UIObject::Create(char *filename)
{
	m_interval = 0;
	speed = 50.0f;
	twice = 0;

	m_vecDirection = { 0.0f, 0.0f };
	m_vecPosition = { 0.0f, 0.0f };

	if (m_pSprite != NULL)
		delete m_pSprite;

	m_pSprite = new dsTexture(filename);
	if (m_pSprite->LoadFromFilename(filename) == false)
	{
		return false;
	}

	SetRect(&m_rcFrame, 58, 605, 455, 263);
}

void UIObject::OnDraw(int x, int y)
{
	m_pSprite->Draw(x, y,
		m_rcFrame.left,
		m_rcFrame.top,
		m_rcFrame.right,
		m_rcFrame.bottom, 0);

}

void UIObject::OnDraw()
{
	m_pSprite->Draw(m_vecPosition.x, m_vecPosition.y,
		m_rcFrame.left,
		m_rcFrame.top,
		m_rcFrame.right,
		m_rcFrame.bottom, 0);

}

void UIObject::OnUpdate(DWORD tick)
{
	m_interval += tick;

	if (m_interval > 100)
	{
		
	}
	m_vecPosition.x += (m_vecDirection.x * 200.0f * tick / 1000.0f);
	m_vecPosition.y += (m_vecDirection.y * 200.0f * tick / 1000.0f);
}

void UIObject::SetPosition(float x, float y)
{
	this->m_vecPosition.x = x;
	this->m_vecPosition.y = y;
}

void UIObject::SetRected()
{
	m_rcFrame = { 0,0,715,780 };
}
