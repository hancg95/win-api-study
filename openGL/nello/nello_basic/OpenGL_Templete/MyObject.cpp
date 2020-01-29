
#include "MyObject.h"


CMyObject::CMyObject()
{
	m_pSprite = NULL;
	m_aniIndex = 0;
	m_aniType = CHARMOTION::DOWN;
}


CMyObject::~CMyObject()
{
	delete m_pSprite;
	m_pSprite = NULL;
}

bool CMyObject::Create(char *filename)
{
	if (m_pSprite != NULL)
		delete m_pSprite;

	m_pSprite = new dsTexture(filename);
	return m_pSprite->LoadFromFilename(filename);
}

void CMyObject::OnDraw(int x, int y) {};

void CMyObject::OnUpdate(DWORD tick) {};

void CMyObject::SetAnimationChange(CHARMOTION ani) {};