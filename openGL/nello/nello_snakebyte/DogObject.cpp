#include "DogObject.h"



DogObject::DogObject()
{
}


DogObject::~DogObject()
{
}

bool DogObject::Create(char *filename)
{
	m_aniType = CHARMOTION::ROPE;
	m_aniIndex = 0;
	m_interval = 0;
	onoff = true;
	twice = 0;
	count = 0;

	m_vecDirection = { 0.0f, 0.0f };
	m_vecPosition = { 0.0f, 0.0f };

	if (m_pSprite != NULL)
		delete m_pSprite;

	m_pSprite = new dsTexture(filename);
	if (m_pSprite->LoadFromFilename(filename) == false)
	{
		return false;
	}

	FILE *fp = fopen("dogdata.txt", "rt");
	int index;
	int left, top, width, height;
	while (!feof(fp))
	{
		fscanf(fp, "%d", &index);
		fscanf(fp, "%d %d %d %d", &left, &top, &width, &height);
		SetRect(&m_rcFrame[index][0], left, top, width, height);
		fscanf(fp, "%d %d %d %d", &left, &top, &width, &height);
		SetRect(&m_rcFrame[index][1], left, top, width, height);
		if (feof(fp))
			break;
		fscanf(fp, "%d %d %d %d", &left, &top, &width, &height);
		SetRect(&m_rcFrame[index][2], left, top, width, height);
		if (feof(fp))
			break;
	}
	fclose(fp);

	return true;
}

void DogObject::OnDraw(int x, int y)
{
	m_pSprite->Draw(x, y,
		m_rcFrame[m_aniType][m_aniIndex].left,
		m_rcFrame[m_aniType][m_aniIndex].top,
		m_rcFrame[m_aniType][m_aniIndex].right,
		m_rcFrame[m_aniType][m_aniIndex].bottom, 0);
}

void DogObject::OnDraw()
{
	m_pSprite->Draw(m_vecPosition.x, m_vecPosition.y,
		m_rcFrame[m_aniType][m_aniIndex].left,
		m_rcFrame[m_aniType][m_aniIndex].top,
		m_rcFrame[m_aniType][m_aniIndex].right,
		m_rcFrame[m_aniType][m_aniIndex].bottom, 0);

}

void DogObject::OnUpdate(DWORD tick, CMyCharacter *g_Char, int num)
{
	m_interval += tick;
	if (m_interval > 100)
	{
		m_interval = 0;
		m_aniIndex++;
		if (m_aniIndex > 2)
		{
			m_aniIndex = 0;
			if(!onoff)twice++;
		}
	}

	if (twice == 2)
	{
		if (g_Char->GetCount() - (num * 200) < 0)
		{
			count = 999 + g_Char->GetCount() - (num * 200);
		}
		else
		{
			count = g_Char->GetCount() - (num * 200);
		}
		
		
	}
	else if (twice > 2)
	{
		if (count > 999)
			count = 0;
		m_vecPosition = g_Char->GetTmp(count);
		this->SetAnimationChange(g_Char->GetTmp2(count));
		count++;
	}

	
}

void DogObject::SetAnimationChange(CHARMOTION ani)
{
	if (m_aniType == ani && twice > 3)
		return;
	else
		m_aniType = ani;
}

void DogObject::SetAniType(CHARMOTION ani)
{
	m_aniType = ani;
}

void DogObject::SetPosition(float x, float y)
{
	this->m_vecPosition.x = x;
	this->m_vecPosition.y = y;
}

RECT DogObject::GetRect()
{
	RECT rcTemp = {
		this->m_vecPosition.x,
		this->m_vecPosition.y,
		this->m_vecPosition.x + m_rcFrame[0][0].right,
		this->m_vecPosition.y + m_rcFrame[0][0].bottom };
	return rcTemp;
}


bool DogObject::GetOnOff()
{
	return this->onoff;
}
void DogObject::SetOnOff(bool onOff)
{
	this->onoff = onOff;
}

Vector2 DogObject::GetPosition()
{
	return this->m_vecPosition;
}

int DogObject::GetTwice()
{
	return this->twice;
}