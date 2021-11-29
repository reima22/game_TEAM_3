//=============================================================================
//
// ���� [Scaffold.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _SCAFFOLD_H_
#define _SCAFFOLD_H_

//*****************************************************************************
// �w�b�_�̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "Scene3DModel.h"

//*****************************************************************************
// ����N���X
//*****************************************************************************
class CScaffold : public CScene3DModel
{
public:
	CScaffold();
	~CScaffold();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScaffold *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:

};

#endif


