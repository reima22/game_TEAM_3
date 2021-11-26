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
#include "meshfield.h"

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
	bool Collision3DMove(CPlayer *pPlayer, CModel *pObject);

	// ���b�V���t�B�[���h�̔���
	bool CollisionMesh(CPlayer *pPlayer, CMeshfield *pMesh);

	bool GetCollisionBool(void) { return m_bCollision; }
	void SetCollisionBool(bool bCollision) { m_bCollision = bCollision; }

	bool GetOnObject(void) { return m_bOnObject; }

private:
	bool m_bCollision;			// �G��Ă��锻��
	bool m_bOnObject;			// �I�u�W�F�N�g������ɂ���
	bool m_bUnderObject;		// �I�u�W�F�N�g�������ɂ���
};

#endif