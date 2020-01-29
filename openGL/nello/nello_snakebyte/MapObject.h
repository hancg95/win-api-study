#pragma once
#include "MyObject.h"
#include <map>

using namespace std;

class CMapSubObject;

class CMapObject : public CMyObject
{
protected:
	typedef map<int, CMapSubObject *> MAP_SUBOBJ;
	MAP_SUBOBJ m_mapSubObject;
	CMapSubObject *m_pBackground;
	int among;
public:
	CMapObject();
	virtual ~CMapObject();

	bool Create(char *filename);
	void OnDraw(int x, int y);
	void OnUpdate(DWORD tick);
	void OnDrawBackground(int x, int y);
};

