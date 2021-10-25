//=============================================================================
//
// �I�u�W�F�N�g�Ǘ� [ObjectManager.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

//*****************************************************************************
// �w�b�_�̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �I�u�W�F�N�g�Ǘ��N���X
//*****************************************************************************
class CObjectManager
{
public:
	typedef struct {
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		int nType;
	} SCAFFOLD_INFO;

	typedef struct {
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		char aModelName[128];
	} MODEL_INFO;

	CObjectManager();
	~CObjectManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	HRESULT Read(void);

	vector<SCAFFOLD_INFO> m_scaffoldInfo;
	vector<MODEL_INFO> m_modelInfo;
};

#endif


