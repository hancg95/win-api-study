#include "MapObject.h"
#include "MapSubObject.h"

CMapObject::CMapObject()
{

}


CMapObject::~CMapObject()
{
	MAP_SUBOBJ::iterator it = m_mapSubObject.begin();
	for (; it != m_mapSubObject.end(); it++)
	{
		CMapSubObject *pSubObj = (CMapSubObject *)it->second;

		pSubObj->Draw(m_pSprite);
	}
	m_mapSubObject.clear();
	delete m_pBackground;
}

bool CMapObject::Create(char *filename)
{
	if (m_pSprite != NULL)
		delete m_pSprite;

	among = 3; // °Ç¹° ¼ö

	m_pSprite = new dsTexture(filename);
	if (m_pSprite->LoadFromFilename(filename) == false)
	{
		return false;
	}

	FILE *fp = fopen("mapdata.txt", "rt");

	int index;
	int left, top, width, height;
	int x, y;

	fscanf(fp, "%d", &index);
	fscanf(fp, "%d %d %d %d", &left, &top, &width, &height);
	fscanf(fp, "%d %d", &x, &y);

	m_pBackground = new CMapSubObject();

	m_pBackground->SetObectRect(left, top, width, height);
	m_pBackground->SetPosition((float)x, (float)y);

	
	for (int i = 0; i<among; i++)
	{

		fscanf(fp, "%d", &index);
		fscanf(fp, "%d %d %d %d", &left, &top, &width, &height);
		fscanf(fp, "%d %d", &x, &y);

		CMapSubObject *pSubObj = new CMapSubObject();
		pSubObj->SetObectRect(left, top, width, height);
		pSubObj->SetPosition((float)x , (float)y);
		m_mapSubObject[index] = pSubObj;
	}
	
	fclose(fp);
}

void CMapObject::OnDraw(int x, int y)
{
	MAP_SUBOBJ::iterator it = m_mapSubObject.begin();
	for (; it != m_mapSubObject.end(); it++)
	{
		CMapSubObject *pSubObj = (CMapSubObject *)it->second;

		pSubObj->Draw(m_pSprite);
	}
}

void CMapObject::OnDrawBackground(int x, int y)
{
	m_pBackground->Draw(m_pSprite);
}

void CMapObject::OnUpdate(DWORD tick)
{

}


