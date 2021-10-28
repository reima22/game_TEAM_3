//=============================================================================
//
// �Q�[����� [game.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �w�b�_�[�̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "Scene2D.h"
#include "Scene3D.h"
#include "Scene3DModel.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObjectManager;

//*****************************************************************************
// �Q�[����ʃN���X ( �p����: �I�u�W�F�N�g�N���X [scene] )
//*****************************************************************************
class CGameScene : public CScene
{
public:
	CGameScene();
	~CGameScene();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CObjectManager *GetObjectManager(void) { return m_pObjectManager; }

private:
	CScene3D *m_pScene3D;

	static CObjectManager *m_pObjectManager;
};
#endif

