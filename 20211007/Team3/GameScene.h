#include "main.h"
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
class CCamera;
class CLight;
class CGameScene
{
public:
	HRESULT InitScene();
	void UninitScene();
	void UpdateScene();
	void DrawScene();
};
#endif