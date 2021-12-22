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
#include "input.h"

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

	if (pCollision != NULL)
	{
		pCollision->SetCollisionBool(false);
	}

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
	D3DXVECTOR3 posObject = pObject->GetPosition();		// �I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3 vtxMin = pObject->GetVtxMin();			// �I�u�W�F�N�g6���̍ŏ��l
	D3DXVECTOR3 vtxMax = pObject->GetVtxMax();			// �I�u�W�F�N�g6���̍ő�l
	D3DXVECTOR3 moveObject = pObject->GetMove();		// �I�u�W�F�N�g�̈ړ���
	D3DXVECTOR3 posOldObject = pObject->GetPosOld();	// �I�u�W�F�N�g�̉ߋ��̈ʒu

	float fPlayerVec[COLLISION_NUM];					// �v���C���[�ւ̃x�N�g�����l

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

		if ((posPlayer.y <= (posObject.y + vtxMax.y) &&
			posPlayer.y > posObject.y + vtxMin.y - fHeight) || 
			posPlayer.y == posOldObject.y + vtxMax.y)
		{
			// ���~���̕␳
			if (moveObject.y < 0.0f && m_bOnObject == true)
			{
				posPlayer.y = posObject.y + vtxMax.y + moveObject.y;
			}

			if (posPlayer.y <= posObject.y + vtxMax.y &&
				(posOld.y >= posObject.y + vtxMax.y || posPlayer.y >= posOldObject.y + vtxMax.y))
			{// �㑤
				//if (posPlayer.y < posObject.y + vtxMax.y)
				{
					m_bCollision = true;
				}

				// �ʒu�̔��f
				posPlayer.y = posObject.y + vtxMax.y;

				// �ړ��͂̔��f
				posPlayer.x += moveObject.x;				
				posPlayer.z += moveObject.z;
			}

			//else if (m_bOnObject == true)
			//{
			//	//if (posPlayer.y < posObject.y + vtxMax.y)
			//	//{
			//	//	m_bCollision = true;
			//	//}

			//	//// �ʒu�̔��f
			//	posPlayer.y = posObject.y + vtxMax.y + moveObject.y;

			//	// �ړ��͂̔��f
			//	posPlayer += moveObject;
			//}

			else if (posPlayer.y + fHeight > posObject.y + vtxMin.y && posOld.y < posObject.y + vtxMin.y && m_bUnderObject == true)
			{// ����
				posPlayer.y = posObject.y + vtxMin.y - fHeight;
				pPlayer->SetMove(D3DXVECTOR3(move.x, -move.y / 2.0f, move.z));
			}

			//else if (posPlayer.x > posOld.x && posOld.x < posObject.x + vtxMin.x)
			else if (posPlayer.x < posObject.x && posOld.x < posObject.x + vtxMin.x)
			{// ����	
				posPlayer.x = posObject.x + vtxMin.x - fRadius - 1.0f;
				pPlayer->SetDashCnt(0);
			}
			//else if (posPlayer.x < posOld.x && posOld.x > posObject.x + vtxMax.x)
			else if (posPlayer.x > posObject.x && posOld.x > posObject.x + vtxMax.x)
			{// �E��	
				posPlayer.x = posObject.x + vtxMax.x + fRadius + 1.0f;
				pPlayer->SetDashCnt(0);
			}
			//else if (posPlayer.z <= posOld.z && posPlayer.z > posObject.z)
			else if (posPlayer.z >= posObject.z)
			{// ����
				posPlayer.z = posObject.z + vtxMax.z + fRadius + 1.0f;
				pPlayer->SetDashCnt(0);
			}
			//else if (posPlayer.z >= posOld.z && posPlayer.z < posObject.z)
			else if (posPlayer.z <= posObject.z)
			{// ��O
				posPlayer.z = posObject.z + vtxMin.z - fRadius - 1.0f;
				pPlayer->SetDashCnt(0);
			}
		}

		// �ʒu�̔��f
		pPlayer->SetPosition(posPlayer);
	}
	//else
	//{
	//	if (posPlayer.y <= (posObject.y + vtxMax.y) && posOld.y >= posObject.y + vtxMax.y && pPlayer->GetLandObj() == true)
	//	{// ����Ă��������痎����ꍇ
	//		pPlayer->SetLandObj(false);
	//	}
	//}

	// �I�u�W�F�N�g�̉ߋ��̈ʒu���X�V
	pObject->SetPosOld(posObject);

	return m_bCollision;
}

//==============================================================================
// ���b�V���t�B�[���h�̔���
//==============================================================================
bool CCollision::CollisionMesh(CPlayer *pPlayer, CMeshfield *pMesh)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	D3DXVECTOR3 vec[3];
	D3DXVECTOR3 vecA, vecB, vecC;
	float fPlayerVec[3];

	int nWidth = pMesh->GetWidthNum();
	int nDepth = pMesh->GetDepthNum();
	int nWidthPoint = pMesh->GetWidthPoint();
	int nDepthPoint = pMesh->GetDepthPoint();

	// �v���C���[�̏��
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();		// ���݂̈ʒu
	D3DXVECTOR3 posPlayerOld = pPlayer->GetPosOld();	// �ߋ��̈ʒu
	bool bLand = false;									// �v���C���[�̒��n���
	bool bInMesh = false;								// ���b�V���͈͓̔�

	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard;
	keyboard = CManager::GetInputKeyboard();

	// �o�b�t�@�̎擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = pMesh->GetVtxBuff();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�ʂ̎Z�o
	for (int nCntDepth = 0; nCntDepth < nDepth; nCntDepth++)
	{// ���s�ʐ�
		int nCntOdd = 0;	// ��J�E���g
		int nCntEven = 0;	// �����J�E���g

		for (int nCntWidth = 0; nCntWidth < nWidth * 2; nCntWidth++)
		{// �������_���i�O�p�`�|���S�����j						
			if (nCntWidth % 2 == 0)
			{
				// �������x�N�g��
				vecA =
					pVtx[nWidthPoint + (nWidthPoint * nCntDepth) - nWidthPoint + nCntEven].pos -
					pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntEven].pos;

				vecB =
					pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntEven + 1].pos -
					pVtx[nWidthPoint + (nWidthPoint * nCntDepth) - nWidthPoint + nCntEven].pos;

				vecC =
					pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntEven].pos -
					pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntEven + 1].pos;

				vec[0] = posPlayer - pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntEven].pos;
				vec[1] = posPlayer - pVtx[nWidthPoint + (nWidthPoint * nCntDepth) - nWidthPoint + nCntEven].pos;
				vec[2] = posPlayer - pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntEven + 1].pos;

				nCntEven++;		// �����J�E���g
			}
			else
			{
				// ����x�N�g��
				vecA =
					pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntOdd - nWidth + nWidthPoint].pos -
					pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntOdd - nWidth].pos;

				vecB =
					pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntOdd - nWidth - 1].pos -
					pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntOdd - nWidth + nWidthPoint].pos;

				vecC =
					pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntOdd - nWidth].pos -
					pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntOdd - nWidth - 1].pos;

				vec[0] = posPlayer - pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntOdd - nWidth].pos;
				vec[1] = posPlayer - pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntOdd - nWidth + nWidthPoint].pos;
				vec[2] = posPlayer - pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntOdd - nWidth - 1].pos;

				nCntOdd++;		// ��J�E���g
			}

			fPlayerVec[0] = (vecA.z * vec[0].x) - (vec[0].z * vecA.x);
			fPlayerVec[1] = (vecB.z * vec[1].x) - (vec[1].z * vecB.x);
			fPlayerVec[2] = (vecC.z * vec[2].x) - (vec[2].z * vecC.x);

			if (fPlayerVec[0] >= 0.0f && fPlayerVec[1] >= 0.0f && fPlayerVec[2] >= 0.0f)
			{// ���b�V���̈��
				bInMesh = true;

				// ���[�J���ϐ��錾
				D3DXVECTOR3 vec0, vec1, vec2, vecP, nor;	// �v�Z�p�x�N�g��
				float fHeight = 0;							// �v�Z����v���C���[�̍���

				if (nCntWidth % 2 == 0)
				{
					nCntEven--;

					vec0 = pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntEven].pos;
					vec1 =
						pVtx[nWidthPoint + (nWidthPoint * nCntDepth) - nWidthPoint + nCntEven].pos -
						pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntEven].pos;

					vec2 =
						pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntEven + 1].pos -
						pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntEven].pos;
				}
				else
				{
					nCntOdd--;

					vec0 = pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntOdd - nWidth].pos;

					vec1 =
						pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntOdd - nWidth + nWidthPoint].pos -
						pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntOdd - nWidth].pos;

					vec2 =
						pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntOdd - nWidth - 1].pos -
						pVtx[nWidthPoint + (nWidthPoint * nCntDepth) + nCntOdd - nWidth].pos;
				}

				// ����̒��_����v���C���[�ւ̃x�N�g��
				vecP = posPlayer - vec0;

				// �@���x�N�g���̌v�Z
				D3DXVec3Cross(&nor, &vec1, &vec2);

				// �@���̐��K��
				D3DXVec3Normalize(&nor, &nor);

				// ���ς�0�ł��邱�Ƃ𗘗p�����v���C���[�̍����v�Z
				if (nor.y != 0.0f)
				{
					fHeight = (-vecP.x * nor.x - vecP.z * nor.z) / nor.y + vec0.y;

					// �ʒu�̐ݒ�
					if (posPlayer.y <= fHeight /*&& (posPlayerOld.y >= fHeight || posPlayerOld.y < fHeight)*/)
					{// ���b�V���ɐڒn����
						// ���ړ�����̊ђʕ␳
						if (posPlayer.y <= posPlayerOld.y)
						{
							if (posPlayerOld.y < fHeight)
							{
								posPlayerOld.y = fHeight;
							}
						}
						else if (posPlayer.y > posPlayerOld.y)
						{
							if (posPlayerOld.y > fHeight)
							{
								posPlayerOld.y = fHeight;
							}
						}

						// ���b�V���̏�ł���
						if ((posPlayer.y <= posPlayerOld.y && posPlayerOld.y >= fHeight) ||
							(posPlayer.y > posPlayerOld.y && posPlayerOld.y < fHeight))
						{
							bLand = true;
						}

											if (bLand == true)
					{
						pPlayer->SetPosition(D3DXVECTOR3(posPlayer.x, fHeight, posPlayer.z));
						return bLand;
					}
					}


					

					//if(posPlayer.y <= fHeight && posPlayerOld.y >= fHeight)
					//{
					//	pPlayer->SetPosition(D3DXVECTOR3(posPlayer.x, fHeight, posPlayer.z));
					//	bLand = true;
					//}
					//else if (posPlayer.y < posPlayerOld.y && posPlayerOld.y > fHeight)
					//{
					//	if (posPlayer.y <= fHeight)
					//	{
					//		pPlayer->SetPosition(D3DXVECTOR3(posPlayer.x, fHeight, posPlayer.z));
					//		bLand = true;
					//	}
					//}
					//else if (posPlayerOld.y < fHeight)
					//{
					//	if (posPlayer.y >= posPlayerOld.y)
					//	{
					//		pPlayer->SetPosition(D3DXVECTOR3(posPlayer.x, fHeight, posPlayer.z));
					//		bLand = true;
					//	}
					//}
					//else if (posPlayer.y > fHeight && posPlayer.y >= posPlayerOld.y)
					//{
					//	pPlayer->SetPosition(D3DXVECTOR3(posPlayer.x, fHeight, posPlayer.z));
					//	bLand = true;
					//}
				}
			}
		}
	}

	if (bInMesh == false)
	{
		//pPlayer->SetLandMesh(false);
		return false;
	}

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();

	return bLand;
}