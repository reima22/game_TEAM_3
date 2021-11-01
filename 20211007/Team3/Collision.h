//=============================================================================
//
// �����蔻�� [Collision.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

//*****************************************************************************
// �w�b�_�̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �����蔻��N���X
//*****************************************************************************
class CCollision
{
public:
	CCollision();
	~CCollision();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static bool AABB2(
		D3DXVECTOR3 posA,
		D3DXVECTOR3 sizeA,
		D3DXVECTOR3 posB,
		D3DXVECTOR3 sizeB);

private:
	//void PlayerCollide(CScene *pCollider);
};

#endif


