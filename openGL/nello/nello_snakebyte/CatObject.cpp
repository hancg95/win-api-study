#include "CatObject.h"



CatObject::CatObject()
{
}


CatObject::~CatObject()
{
}

bool CatObject::Create(char *filename)
{
	m_aniType = CHARMOTION::LEFT;
	m_aniIndex = 0;
	m_interval = 0;
	speed = 50.0f;
	twice = 0;

	m_vecDirection = { -1.0f, 0.0f };
	m_vecPosition = { 0.0f, 0.0f };

	if (m_pSprite != NULL)
		delete m_pSprite;

	m_pSprite = new dsTexture(filename);
	if (m_pSprite->LoadFromFilename(filename) == false)
	{
		return false;
	}

	FILE *fp = fopen("catdata.txt", "rt");
	int index;
	int left, top, width, height;
	while (!feof(fp))
	{
		fscanf(fp, "%d", &index);
		fscanf(fp, "%d %d %d %d", &left, &top, &width, &height);
		SetRect(&m_rcFrame[index][0], left, top, width, height);
		fscanf(fp, "%d %d %d %d", &left, &top, &width, &height);
		SetRect(&m_rcFrame[index][1], left, top, width, height);
		fscanf(fp, "%d %d %d %d", &left, &top, &width, &height);
		SetRect(&m_rcFrame[index][2], left, top, width, height);
		if (feof(fp))
			break;
	}
	fclose(fp);

	return true;
}

void CatObject::OnDraw(int x, int y)
{
	m_pSprite->Draw(x,y,
		m_rcFrame[m_aniType][m_aniIndex].left,
		m_rcFrame[m_aniType][m_aniIndex].top,
		m_rcFrame[m_aniType][m_aniIndex].right,
		m_rcFrame[m_aniType][m_aniIndex].bottom, 0);

}

void CatObject::OnDraw()
{
	m_pSprite->Draw(m_vecPosition.x, m_vecPosition.y,
		m_rcFrame[m_aniType][m_aniIndex].left,
		m_rcFrame[m_aniType][m_aniIndex].top,
		m_rcFrame[m_aniType][m_aniIndex].right,
		m_rcFrame[m_aniType][m_aniIndex].bottom, 0);

}

void CatObject::OnUpdate(DWORD tick)
{
	m_interval += tick;

	if (m_interval > 100)
	{
		m_interval = 0;
		m_aniIndex++;
		if (m_aniIndex > 2)
		{
			m_aniIndex = 0;
			twice++;
		}
	}
	if (twice > 3)
	{
		if (m_aniType > 0) m_aniType = CHARMOTION::LEFT;
		else m_aniType = CHARMOTION::RIGHT;
		m_vecDirection.x *= -1.0f;
		twice = 0;
	}
	m_vecPosition.x += (m_vecDirection.x * 200.0f * tick / 1000.0f);
	m_vecPosition.y += (m_vecDirection.y * 200.0f * tick / 1000.0f);
}

void CatObject::SetPosition(float x, float y) 
{
	this->m_vecPosition.x = x;
	this->m_vecPosition.y = y;
}

RECT CatObject::GetRect()
{
	RECT rcTemp = {
		this->m_vecPosition.x,
		this->m_vecPosition.y,
		this->m_vecPosition.x + m_rcFrame[0][0].right,
		this->m_vecPosition.y + m_rcFrame[0][0].bottom };
	return rcTemp;
}