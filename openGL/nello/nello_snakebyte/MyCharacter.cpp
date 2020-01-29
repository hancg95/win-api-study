#include "MyCharacter.h"
#include <windows.h>

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
	count = 0;
	m_mapPosition = 0.0f;
	speed = 200.0f;

	m_vecDirection = { 0.0f, 0.0f };
	m_vecPosition = { 0.0f, 0.0f };
	for (int i = 0; i < 100; i++)
	{
		m_tmp[i] = { 0.0f, 0.0f };
		m_tmp2[i] = CHARMOTION::LEFT;
	}
}


CMyCharacter::~CMyCharacter()
{
	
}

bool CMyCharacter::Create(char *filename)
{
	if (m_pSprite != NULL)
		delete m_pSprite;

	m_pSprite = new dsTexture(filename);

	//int				 setData[5][3][10];
	FILE *fp = fopen("setdata.txt", "rt");

	int round;
	int b[10];
	int d[10];
	int c[10];
	

	fscanf(fp, "%d", &round);
	fscanf(fp, "%d %d %d %d %d %d", &b[0], &b[1], &b[2], &b[3], &b[4], &b[5]);
	fscanf(fp, "%d %d %d %d %d %d %d %d", &d[0], &d[1], &d[2], &d[3], &d[4], &d[5], &d[6], &d[7]);
	fscanf(fp, "%d %d", &c[0], &c[1]);
	
	for (int i = 0; i < 6; i++)
	{
		setData[round][0][i] = b[i];
	}
	for (int i = 0; i < 8; i++)
	{
		setData[round][1][i] = d[i];
	}
	for (int i = 0; i < 4; i++)
	{
		setData[round][2][i] = c[i];
	}
	
	fclose(fp);

	return m_pSprite->LoadFromFilename(filename);
}

void CMyCharacter::OnDraw(int x, int y)
{	
	m_pSprite->Draw(m_vecPosition.x, m_vecPosition.y,
		m_rcFrame[m_aniType][m_aniIndex].left,
		m_rcFrame[m_aniType][m_aniIndex].top,
		m_rcFrame[m_aniType][m_aniIndex].right,
		m_rcFrame[m_aniType][m_aniIndex].bottom, 0);
}

int CMyCharacter::OnUpdate(DWORD tick)
{
	m_interval += tick;

	if (m_interval > 100)
	{
		m_interval = 0;
		m_aniIndex++;
		if (m_aniIndex > 2)
		{
			m_aniIndex = 0;
		}
	}

	if (count > 999) count = 0;

	if (ChkBreak()) 
	{
		m_tmp[count] = m_vecPosition;;
		count++;
	}
	//else if (ChkMapMove())
	//{
	//	m_vecPosition.x += (m_vecDirection.x * 200.0f * tick / 1000.0f);
	//	m_mapPosition -= (m_vecDirection.y * 200.0f * tick / 1000.0f);
	
	//}
	else
	{
		m_vecPosition.x += (m_vecDirection.x * speed * tick / 1000.0f);
		m_vecPosition.y += (m_vecDirection.y * speed * tick / 1000.0f);
		m_tmp[count] = m_vecPosition;
		m_tmp2[count] = m_aniType;
		count++;
		int chk = RectChk();
		if (chk!=-1)
		{
			return chk;
		}
	}
	return -1;
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


bool CMyCharacter::ChkBreak()
{
	switch (m_aniType)
	{
	case CHARMOTION::LEFT:
		if (m_vecPosition.x < 0.0f)return true; // 왼쪽 끝 충돌
		break;
	case CHARMOTION::RIGHT:
		if (m_vecPosition.x > 615.0f)return true; // 오른쪽 끝 충돌
		break;
	case CHARMOTION::UP:
		if (m_vecPosition.y < 0.0f)return true; // 위쪽 끝 충돌

		break;
	case CHARMOTION::DOWN:
		if (m_vecPosition.y > 661.0f)return true; // 밑쪽 끝 충돌
		break;
	}
	return false;
}

bool CMyCharacter::ChkMapMove() // 맵 전체 움직일까 확인
{
	return false;
	
}


Vector2 CMyCharacter::GetPosition()
{
	return this->m_vecPosition;
}

Vector2 CMyCharacter::GetTmp(int count)
{
	return this->m_tmp[count];
}

CHARMOTION CMyCharacter::GetTmp2(int count)
{
	return this->m_tmp2[count];
}


void CMyCharacter::SetPosition(float x, float y)
{
	this->m_vecPosition.x = x;
	this->m_vecPosition.y = y;
}

RECT CMyCharacter::GetRect()
{
	RECT rcTemp = {
		this->m_vecPosition.x,
		this->m_vecPosition.y,
		this->m_vecPosition.x + m_rcFrame[0][0].right,
		this->m_vecPosition.y + m_rcFrame[0][0].bottom };
	return rcTemp;
}

int CMyCharacter::RectChk()
{
	

	RECT rcTmp;
	for (int i = 0; i < 8 ; i += 2)
	{
		RECT rcDog = { setData[0][1][i]+40,setData[0][1][i + 1]+40,setData[0][1][i] + 49,setData[0][1][i + 1] + 74 }; //개
		if (IntersectRect(&rcTmp, &this->GetRect(), &rcDog))
		{
			
			
			return i / 2;
		}
	}
	for (int i = 0; i < 2; i += 2)
	{
		RECT rcCat = { setData[0][2][i]+40,setData[0][2][i + 1]+40,setData[0][2][i] + 49,setData[0][2][i + 1] + 74 }; //고양이
		//RECT rcCat = { g_mgr + 40,setData[0][2][i + 1] + 40,setData[0][2][i] + 49,setData[0][2][i + 1] + 74 }; //고양이
		if (IntersectRect(&rcTmp, &this->GetRect(), &rcCat))
		{


			return i / 2 + 10;
		}
	}
	
	{
		RECT rcBul = { 470+50, 10,470 + 235, 10+275-50}; //건물
		if (IntersectRect(&rcTmp, &this->GetRect(), &rcBul))
			return 10;
		rcBul = { 0, 560 + 30,0 + 447 - 30, 560 + 220};
		if (IntersectRect(&rcTmp, &this->GetRect(), &rcBul))
			return 10;
		rcBul = { 100+30, 200+30, 100+91-30, 200+70};
		if (IntersectRect(&rcTmp, &this->GetRect(), &rcBul))
			return 10;
	}
	return -1;
}

Vector2 CMyCharacter::GetDirection()
{
	return m_vecDirection;
}

CHARMOTION CMyCharacter::GetAniType()
{
	return m_aniType;
}


int CMyCharacter::GetCount()
{
	return count;
}

void CMyCharacter::SetDirection(float x,float y)
{
	m_vecDirection.x = x;
	m_vecDirection.y = y;
}