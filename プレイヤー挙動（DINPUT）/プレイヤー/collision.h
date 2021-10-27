//=============================================================================
//
// �����蔻��Ǘ� [collision.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"
#include "model.h"
#include "player.h"

//==============================================================================
// �����蔻��Ǘ��N���X
//==============================================================================
class CCollision
{
public:

	CCollision();
	~CCollision();

	static CCollision *Create(void);

	// 3D���f���Ԃ̓����蔻��
	bool Collision3D(CPlayer *pPlayer, CModel *pObject);

	bool GetCollisionBool(void) { return m_bCollision; }

private:
	bool m_bCollision;			// �G��Ă��锻��
};

#endif