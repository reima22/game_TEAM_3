//==============================================================================
//
// �����蔻��Ǘ��kcollision.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"
#include "shadow.h" 

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CCollision::CCollision()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CCollision::~CCollision()
{

}

//==============================================================================
// �����蔻��|�C���^�̐���
//==============================================================================
CCollision *CCollision::Create(void)
{
	// �����蔻��
	CCollision *pCollision;
	pCollision = new CCollision;

	pCollision->SetCollisionBool(false);

	return pCollision;
}

//==============================================================================
// 3D���f���Ԃ̓����蔻�菈��
//==============================================================================
bool CCollision::Collision3D(CPlayer *pPlayer, CModel *pObject)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 aVec[COLLISION_NUM];				// ��`���_���画��Ώۂւ̃x�N�g��
	
	// �v���C���[���
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();	// ����Ώۂ̈ʒu
	D3DXVECTOR3 posOld = pPlayer->GetPosOld();		// �v���C���[�̉ߋ��̈ʒu
	float fRadius = pPlayer->GetRadius();			// �v���C���[���a�̎擾
	float fHeight = pPlayer->GetHeight();			// �v���C���[�����̎擾
	D3DXVECTOR3 move = pPlayer->GetMove();			// �v���C���[�̈ړ���

	// �I�u�W�F�N�g���
	D3DXVECTOR3 posObject = pObject->GetPosition();	// �I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3 vtxMin = pObject->GetVtxMin();		// �I�u�W�F�N�g6���̍ŏ��l
	D3DXVECTOR3 vtxMax = pObject->GetVtxMax();		// �I�u�W�F�N�g6���̍ő�l

	float fPlayerVec[COLLISION_NUM];				// �v���C���[�ւ̃x�N�g�����l

	m_bOnObject = false;
	m_bUnderObject = false;
	m_bCollision = false;

	// �I�u�W�F�N�g�Ƃ̓����蔻��
	for (int nCnt = 0; nCnt < COLLISION_NUM; nCnt++)
	{
		// ���[�J���ϐ��錾
		D3DXVECTOR3 posVtx = pObject->GetPosVtx(nCnt);
		D3DXVECTOR3 vecVtx = pObject->GetVecVtx(nCnt);

		if (nCnt == 0)
		{// ����
			aVec[nCnt] = posPlayer + D3DXVECTOR3(fRadius, 0.0f, 0.0f) - posVtx;
		}
		else if (nCnt == 1)
		{// ����
			aVec[nCnt] = posPlayer + D3DXVECTOR3(0.0f, 0.0f, -fRadius) - posVtx;
		}
		else if (nCnt == 2)
		{// �E��
			aVec[nCnt] = posPlayer + D3DXVECTOR3(-fRadius, 0.0f, 0.0f) - posVtx;
		}
		else if (nCnt == 3)
		{// ��O
			aVec[nCnt] = posPlayer + D3DXVECTOR3(0.0f, 0.0f, fRadius) - posVtx;
		}

		// ���l���u+�v�̎��A�����蔻�肪�L��
		fPlayerVec[nCnt] = (vecVtx.z * aVec[nCnt].x) - (vecVtx.x * aVec[nCnt].z);
	}

	// �����蔻��
	if (fPlayerVec[0] > 0.0f && fPlayerVec[1] > 0.0f && fPlayerVec[2] > 0.0f && fPlayerVec[3] > 0.0f)
	{// �Z�o�����x�N�g���͈͓̔�����
		if (posPlayer.y >= posObject.y + vtxMax.y)
		{
			m_bOnObject = true;
		}
		else if (posOld.y + fHeight < posObject.y + vtxMin.y)
		{
			m_bUnderObject = true;
		}
		
		if (posPlayer.y <= (posObject.y + vtxMax.y) &&
			posPlayer.y > posObject.y + vtxMin.y - fHeight)
		{
			if (posPlayer.y <= posObject.y + vtxMax.y && posOld.y >= posObject.y + vtxMax.y)
			{// �㑤
				if (posPlayer.y < posObject.y + vtxMax.y)
				{
					m_bCollision = true;
				}

				// �ʒu�̔��f
				posPlayer.y = posObject.y + vtxMax.y;
			}

			else if (posPlayer.y + fHeight > posObject.y + vtxMin.y && posOld.y < posObject.y + vtxMin.y && m_bUnderObject == true)
			{// ����
				posPlayer.y = posObject.y + vtxMin.y - fHeight;
				pPlayer->SetMove(D3DXVECTOR3(move.x, -move.y / 2.0f, move.z));
			}

			else if (posPlayer.x > posOld.x && posOld.x < posObject.x + vtxMin.x)
			{// ����
				posPlayer.x = posObject.x + vtxMin.x - fRadius;
				pPlayer->SetDashCnt(0);
			}
			else if (posPlayer.x < posOld.x && posOld.x > posObject.x + vtxMax.x)
			{// �E��
				posPlayer.x = posObject.x + vtxMax.x + fRadius;
				pPlayer->SetDashCnt(0);
			}
			else if (posPlayer.z <= posOld.z && posPlayer.z > posObject.z)
			{// ����
				posPlayer.z = posObject.z + vtxMax.z + fRadius;
				pPlayer->SetDashCnt(0);
			}
			else if (posPlayer.z >= posOld.z && posPlayer.z < posObject.z)
			{// ��O
				posPlayer.z = posObject.z + vtxMin.z - fRadius;
				pPlayer->SetDashCnt(0);
			}
		}

		// �ʒu�̔��f
		pPlayer->SetPosition(posPlayer);
	}
	else
	{
		if (posPlayer.y <= (posObject.y + vtxMax.y) && posOld.y >= posObject.y + vtxMax.y)
		{// ����Ă��������痎����ꍇ
			pPlayer->SetLanding(false);
		}
	}

	return m_bCollision;
}