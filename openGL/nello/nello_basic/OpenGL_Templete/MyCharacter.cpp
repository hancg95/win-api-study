#include "MyCharacter.h"

#define MOVE_SPEED 200.0f



CMyCharacter::CMyCharacter()
{	
	m_aniType = CHARMOTION::DOWN;

	SetRect(&m_rcFrame[CHARMOTION::LEFT][0], 303, 5, 100, 119);
	SetRect(&m_rcFrame[CHARMOTION::LEFT][1], 403, 5, 100, 119);
	SetRect(&m_rcFrame[CHARMOTION::LEFT][2], 5, 126, 100, 119);

	SetRect(&m_rcFrame[CHARMOTION::RIGHT][0], 5, 369, 100, 119);
	SetRect(&m_rcFrame[CHARMOTION::RIGHT][1], 104, 369, 100, 119);
	SetRect(&m_rcFrame[CHARMOTION::RIGHT][2], 203, 369, 100, 119);
	
	SetRect(&m_rcFrame[CHARMOTION::UP][0], 104, 126, 100, 119);
	SetRect(&m_rcFrame[CHARMOTION::UP][1], 203, 126, 100, 119);
	SetRect(&m_rcFrame[CHARMOTION::UP][2], 303, 126, 100, 119);

	SetRect(&m_rcFrame[CHARMOTION::DOWN][0], 5, 5, 100, 119);
	SetRect(&m_rcFrame[CHARMOTION::DOWN][1], 104, 5, 100, 119);
	SetRect(&m_rcFrame[CHARMOTION::DOWN][2], 203, 5, 100, 119);

	SetRect(&m_rcFrame[CHARMOTION::HIT][0], 403, 126, 100, 119);
	SetRect(&m_rcFrame[CHARMOTION::HIT][1], 5, 249, 100, 119);
	SetRect(&m_rcFrame[CHARMOTION::HIT][2], 104, 249, 100, 119);
	SetRect(&m_rcFrame[CHARMOTION::HIT][3], 203, 249, 100, 119);
	SetRect(&m_rcFrame[CHARMOTION::HIT][4], 303, 249, 100, 119);
	SetRect(&m_rcFrame[CHARMOTION::HIT][5], 403, 249, 100, 119);
	
	SetRect(&m_rcFrame[CHARMOTION::WIN][0], 303, 369, 100, 119);
	SetRect(&m_rcFrame[CHARMOTION::WIN][1], 403, 369, 100, 119);


	m_aniIndex = 0;
	m_interval = 0;

	m_vecDirection = { 0.0f, 0.0f };
	m_vecPosition = { 300.0f, 300.0f };
}




CMyCharacter::~CMyCharacter()
{
	
}
//
//bool CMyCharacter::Create(char *filename)
//{
//	if (m_pSprite != NULL)
//		delete m_pSprite;
//
//	m_pSprite = new dsTexture(filename);
//	return m_pSprite->LoadFromFilename(filename);
//}

//void CMyCharacter::OnDraw(int x, int y)
//{
//	m_vecPosition.x = x;
//	m_vecPosition.y = y;
//	m_pSprite->Draw(m_vecPosition.x, m_vecPosition.y,
//		m_rcFrame[m_aniType][m_aniIndex].left,
//		m_rcFrame[m_aniType][m_aniIndex].top,
//		m_rcFrame[m_aniType][m_aniIndex].right,
//		m_rcFrame[m_aniType][m_aniIndex].bottom, 0);
//}

void CMyCharacter::OnDraw()
{
	m_pSprite->Draw(m_vecPosition.x, m_vecPosition.y,
		m_rcFrame[m_aniType][m_aniIndex].left,
		m_rcFrame[m_aniType][m_aniIndex].top,
		m_rcFrame[m_aniType][m_aniIndex].right,
		m_rcFrame[m_aniType][m_aniIndex].bottom, 0);
}

void CMyCharacter::OnUpdate(DWORD tick)
{
	m_interval += tick;

	if (m_interval > 100)
	{
		m_interval = 0;
		m_aniIndex++;
		if (m_aniIndex > 2)
			m_aniIndex = 0;
	}

	m_vecPosition.x += (m_vecDirection.x * MOVE_SPEED * tick/1000.0f);
	m_vecPosition.y += (m_vecDirection.y * MOVE_SPEED * tick/1000.0f);

}

void CMyCharacter::SetAnimationChange(CHARMOTION ani)
{
	if (m_aniType == ani)
		return;

	m_aniType = ani;

	switch (m_aniType)
	{
	case CHARMOTION::LEFT: m_vecDirection = { -1.0f, 0.0f };
		break;
	case CHARMOTION::RIGHT: m_vecDirection = { 1.0f, 0.0f };
		break;
	case CHARMOTION::UP: m_vecDirection = { 0.0f, -1.0f };
		break;
	case CHARMOTION::DOWN: m_vecDirection = { 0.0f, 1.0f };
		break;
	default: m_vecDirection = { 0.0f, 0.0f };
	}
}