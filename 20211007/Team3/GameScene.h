#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "main.h"
#include "Resource.h"
class CGameScene
{
public:
	HRESULT InitScene();
	void UninitScene();
	void UpdateScene();
	void DrawScene();
private:
	CResourceManager* m_pResource;
};
#endif