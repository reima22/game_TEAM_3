#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
//
// �v���C���[�N���X [player.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�[�̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "Scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_MODEL_COUNT (10)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;

//*****************************************************************************
// ���f���N���X (�h�����F�I�u�W�F�N�g�N���X (scene) �j
//*****************************************************************************
class CPlayer : public CScene
{
public:
	CPlayer(int nPriority = 3);
	~CPlayer();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	CModel *m_apModel[PLAYER_MODEL_COUNT];	// ���f���ւ̃|�C���^
	int m_nIndexParent[PLAYER_MODEL_COUNT];	// �e���f����INDEX
	float m_aOffset[PLAYER_MODEL_COUNT][6];	// �e���f������̃I�t�Z�b�g
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	char m_aFilePath[PLAYER_MODEL_COUNT][128];
};

#endif