//===================================================================
//SourceFile: Collider3D.cpp
//Author : Yo jitaku
//===================================================================
#include "Collider3D.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "GamePad.h"
#include "MouseKeyboard.h"

HRESULT CHitBox::Init()
{
	CResourceManager* pRe = CResourceManager::GetInstance();
	m_pRenderer = CRenderer::GetInstance();
	m_pDevice = m_pRenderer->GetDevice();
	m_DrawHitBox = false;

	switch (pParent->m_Type)
	{
	case T_SNOWMAN:
		SetHitBox(pRe->m_Model_Map["T_SNOWMAN"]->Xfile_Mesh);
		break;
	default:
		break;
	}

	//���_�o�b�t�@
	if (FAILED(m_pDevice->CreateVertexBuffer(HITBOX_VERTEX_NUM * sizeof(VERTEX_3D),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
		return E_FAIL;

	//index�o�b�t�@
	if (FAILED(m_pDevice->CreateIndexBuffer
	(HITBOX_INDEX_NUM * sizeof(WORD),//�`��K�v�̍Œ�̒��_��(�d���̒��_������) (���_����2�~�s���~(��+1)+2�~(�s��-1)) -> 2(xy+2x-1)
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL)))
		return E_FAIL;

	SetVertex();
	m_Box.Model_Offset = (m_Box.BoxSizeMax + m_Box.BoxSizeMin) / 2;
	SetSAT();
	SetIndex();

	return S_OK;
}
void CHitBox::SetVertex()
{
	m_Box.Rot = pParent->m_Rot;
	m_Box.BoxPos = pParent->m_Pos + m_Box.Model_Offset;
	VERTEX_3D* pVtx;//���_�o�b�t�@
	m_Box.BoxVtx[0] = m_Box.BoxPos + D3DXVECTOR3(-m_Box.BoxSize.x, -m_Box.BoxSize.y, -m_Box.BoxSize.z);
	m_Box.BoxVtx[1] = m_Box.BoxPos + D3DXVECTOR3(m_Box.BoxSize.x, -m_Box.BoxSize.y, -m_Box.BoxSize.z);
	m_Box.BoxVtx[2] = m_Box.BoxPos + D3DXVECTOR3(m_Box.BoxSize.x, -m_Box.BoxSize.y, m_Box.BoxSize.z);
	m_Box.BoxVtx[3] = m_Box.BoxPos + D3DXVECTOR3(-m_Box.BoxSize.x, -m_Box.BoxSize.y, m_Box.BoxSize.z);
	m_Box.BoxVtx[4] = m_Box.BoxPos + D3DXVECTOR3(-m_Box.BoxSize.x, m_Box.BoxSize.y, -m_Box.BoxSize.z);
	m_Box.BoxVtx[5] = m_Box.BoxPos + D3DXVECTOR3(m_Box.BoxSize.x, m_Box.BoxSize.y, -m_Box.BoxSize.z);
	m_Box.BoxVtx[6] = m_Box.BoxPos + D3DXVECTOR3(m_Box.BoxSize.x, m_Box.BoxSize.y, m_Box.BoxSize.z);
	m_Box.BoxVtx[7] = m_Box.BoxPos + D3DXVECTOR3(-m_Box.BoxSize.x, m_Box.BoxSize.y, m_Box.BoxSize.z);
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < HITBOX_VERTEX_NUM; nCnt++)
	{
		pVtx[nCnt].pos = m_Box.BoxVtx[nCnt];
		pVtx[nCnt].nor = D3DXVECTOR3(0.f, 1.f, 0.f);
		pVtx[nCnt].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	}
	m_pVtxBuff->Unlock();
}
void CHitBox::SetIndex()
{
	WORD* pIdx;//Index�o�b�t�@
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	//bottom
	pIdx[0] = 0;
	pIdx[1] = 1;
	pIdx[2] = 2;
	pIdx[3] = 2;
	pIdx[4] = 3;
	pIdx[5] = 0;
	//left
	pIdx[6] = 3;
	pIdx[7] = 0;
	pIdx[8] = 4;
	pIdx[9] = 4;
	pIdx[10] = 7;
	pIdx[11] = 3;
	//right
	pIdx[12] = 1;
	pIdx[13] = 2;
	pIdx[14] = 6;
	pIdx[15] = 6;
	pIdx[16] = 5;
	pIdx[17] = 1;
	//front
	pIdx[18] = 0;
	pIdx[19] = 1;
	pIdx[20] = 5;
	pIdx[21] = 5;
	pIdx[22] = 4;
	pIdx[23] = 0;
	//back
	pIdx[24] = 2;
	pIdx[25] = 3;
	pIdx[26] = 7;
	pIdx[27] = 7;
	pIdx[28] = 6;
	pIdx[29] = 2;
	//top
	pIdx[30] = 4;
	pIdx[31] = 5;
	pIdx[32] = 6;
	pIdx[33] = 6;
	pIdx[34] = 7;
	pIdx[35] = 4;
	m_pIdxBuff->Unlock();
}
void CHitBox::SetHitBox(LPD3DXMESH pMesh)
{
	//�����蔻��pbox�̐ݒ�
	int nNumVtx;													//���_��
	DWORD sizeFvF;													//����_format��size
	BYTE *pVtxBuff;													//���_buffer�ւ�pointer
	nNumVtx = pMesh->GetNumVertices();								//���_�������
	sizeFvF = D3DXGetFVFVertexSize(pMesh->GetFVF());				//format�̑傫��
	pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);	//���_buff��lock
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;					//���_�������
		pVtxBuff += sizeFvF;										//���ɍs��

		//�����蔻��pbox�̒��_��T��
		if (nCntVtx == 0)											//���߂̒��_
		{
			m_Box.BoxSizeMax = vtx;
			m_Box.BoxSizeMin = vtx;
		}
		else
		{
			if (vtx.x > m_Box.BoxSizeMax.x) m_Box.BoxSizeMax.x = vtx.x;
			else if (vtx.x < m_Box.BoxSizeMin.x) m_Box.BoxSizeMin.x = vtx.x;
			if (vtx.y > m_Box.BoxSizeMax.y) m_Box.BoxSizeMax.y = vtx.y;
			else if (vtx.y < m_Box.BoxSizeMin.y) m_Box.BoxSizeMin.y = vtx.y;
			if (vtx.z > m_Box.BoxSizeMax.z) m_Box.BoxSizeMax.z = vtx.z;
			else if (vtx.z < m_Box.BoxSizeMin.z) m_Box.BoxSizeMin.z = vtx.z;
		}
	}
	m_Box.BoxSize = (m_Box.BoxSizeMax - m_Box.BoxSizeMin) / 2.f;
	pMesh->UnlockVertexBuffer();									//unlock
}

void CHitBox::PhysicsUpdate()
{
	SetVertex();
	//UpDateHitBoxPos();
}

void CHitBox::GraphicsDraw()
{
	DrawHitBox();
}

void CHitBox::DrawHitBox()
{
#ifdef _DEBUG
	//CKeyBoard* pBoard = CKeyBoard::GetInstance();
	//CGamePad* pPad = CGamePad::GetInstance();
	//if (pBoard->GetkeyboardTrigger(DIK_F5))
	//	m_DrawHitBox = !m_DrawHitBox;
	if (!m_DrawHitBox)
	{
		D3DXMATRIX mtxRot, mtxTrans, mtxworld;
		D3DXMatrixIdentity(&mtxworld);//�P��matrix
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pParent->m_Rot.x, 0, pParent->m_Rot.z);//��]�p�x(���[�V���������[�h�̓��[�C���O�p���Ȃ���)
		//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Box.Rot.x, m_Box.Rot.y, m_Box.Rot.z);//��]�p�x(���[�V���������[�h�̓��[�C���O�p���Ȃ���)
		D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxRot); //���Z�@���Ematrix�̈ړ�
		D3DXMatrixTranslation(&mtxTrans, m_Box.BoxPos.x, m_Box.BoxPos.y, m_Box.BoxPos.z); //���Ematrix�S�́@�ړ������������Ƃ���matrix�̍��Z
		D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxRot); //���Z�@���Ematrix�̈ړ�
		m_pDevice->SetTransform(D3DTS_WORLD, &mtxworld); //set the world into Map

		m_pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
		m_pDevice->SetIndices(m_pIdxBuff);
		m_pDevice->SetFVF(FVF_VERTEX_3D);
		m_pDevice->SetTexture(0, nullptr);
		m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);//���ʕ`��
		m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);	//���C���[�t���[�����[�h
		m_pDevice->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			0,
			HITBOX_VERTEX_NUM,
			0,
			HITBOX_DRAW_TRI_NUM);			
		m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		//SOLID���[�h�ɖ߂�														//List���[�h�Ń��b�V����`��
		m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); //���ʕ`�悵�Ȃ�	}
	}
#endif
}

//*******************************************************************
//�O�̒��_���W�Ɋ�Â��ĎO�p�`�ʂ̕����x�N�g�����v�Z����֐�
//*******************************************************************
D3DXVECTOR3 CHitBox::GetTriangleNor(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3)
{
	D3DXVECTOR3 t1, t2, nor;
	float length = 0;
	t1 = pos1 - pos2;
	t2 = pos2 - pos3;
	nor.x = t1.y * t2.z - t1.z * t2.y;
	nor.y = -(t1.x * t2.z - t1.z * t2.x);
	nor.z = t1.x * t2.y - t1.y * t2.x;
	length = D3DXVec3Length(&nor);
	if (length == 0)
		length = 1;
	nor /= length;
	return nor;
}

bool CHitBox::SAT_func(CHitBox* pTarget)
{
	// �e�����x�N�g���̊m��
	D3DXVECTOR3 BoxA_x_e = GetVector(0);
	D3DXVECTOR3 BoxA_y_e = GetVector(1);
	D3DXVECTOR3 BoxA_z_e = GetVector(2);
	D3DXVECTOR3 BoxA_x = GetVector(0) * GetVecLength(0);
	D3DXVECTOR3 BoxA_y = GetVector(1) * GetVecLength(1);
	D3DXVECTOR3 BoxA_z = GetVector(2) * GetVecLength(2);
	D3DXVECTOR3 BoxB_x_e = pTarget->GetVector(0);
	D3DXVECTOR3 BoxB_y_e = pTarget->GetVector(1);
	D3DXVECTOR3 BoxB_z_e = pTarget->GetVector(2);
	D3DXVECTOR3 BoxB_x = pTarget->GetVector(0) * pTarget->GetVecLength(0);
	D3DXVECTOR3 BoxB_y = pTarget->GetVector(1) * pTarget->GetVecLength(1);
	D3DXVECTOR3 BoxB_z = pTarget->GetVector(2) * pTarget->GetVecLength(2);
	D3DXVECTOR3 BoxAB_Vec = m_Box.BoxPos - pTarget->m_Box.BoxPos;

	// ������ : A_x
	float rA = D3DXVec3Length(&BoxA_x);
	float rB = GetAxisProjectionlength(&BoxA_x_e, &BoxB_x, &BoxB_y, &BoxB_z);
	float L = fabs(D3DXVec3Dot(&BoxAB_Vec, &BoxA_x_e));
	if (L > rA + rB)
		return false; // �Փ˂��Ă��Ȃ�

					  // ������ : A_y
	rA = D3DXVec3Length(&BoxA_y);
	rB = GetAxisProjectionlength(&BoxA_y_e, &BoxB_x, &BoxB_y, &BoxB_z);
	L = fabs(D3DXVec3Dot(&BoxAB_Vec, &BoxA_y_e));
	if (L > rA + rB)
		return false;

	// ������ : A_z
	rA = D3DXVec3Length(&BoxA_z);
	rB = GetAxisProjectionlength(&BoxA_z_e, &BoxB_x, &BoxB_y, &BoxB_z);
	L = fabs(D3DXVec3Dot(&BoxAB_Vec, &BoxA_z_e));
	if (L > rA + rB)
		return false;

	// ������ : B_x
	rA = GetAxisProjectionlength(&BoxB_x_e, &BoxA_x, &BoxA_y, &BoxA_z);
	rB = D3DXVec3Length(&BoxB_x);
	L = fabs(D3DXVec3Dot(&BoxAB_Vec, &BoxB_x_e));
	if (L > rA + rB)
		return false;

	// ������ : B_y
	rA = GetAxisProjectionlength(&BoxB_y_e, &BoxA_x, &BoxA_y, &BoxA_z);
	rB = D3DXVec3Length(&BoxB_y);
	L = fabs(D3DXVec3Dot(&BoxAB_Vec, &BoxB_y_e));
	if (L > rA + rB)
		return false;

	// ������ : B_z
	rA = GetAxisProjectionlength(&BoxB_z_e, &BoxA_x, &BoxA_y, &BoxA_z);
	rB = D3DXVec3Length(&BoxB_z);
	L = fabs(D3DXVec3Dot(&BoxAB_Vec, &BoxB_z_e));
	if (L > rA + rB)
		return false;

	// ������ : AB_xx
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &BoxA_x_e, &BoxB_x_e);
	rA = GetAxisProjectionlength(&Cross, &BoxA_y, &BoxA_z);
	rB = GetAxisProjectionlength(&Cross, &BoxB_y, &BoxB_z);
	L = fabs(D3DXVec3Dot(&BoxAB_Vec, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : AB_xy
	D3DXVec3Cross(&Cross, &BoxA_x_e, &BoxB_y_e);
	rA = GetAxisProjectionlength(&Cross, &BoxA_y, &BoxA_z);
	rB = GetAxisProjectionlength(&Cross, &BoxB_x, &BoxB_z);
	L = fabs(D3DXVec3Dot(&BoxAB_Vec, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : AB_xz
	D3DXVec3Cross(&Cross, &BoxA_x_e, &BoxB_z_e);
	rA = GetAxisProjectionlength(&Cross, &BoxA_y, &BoxA_z);
	rB = GetAxisProjectionlength(&Cross, &BoxB_x, &BoxB_y);
	L = fabs(D3DXVec3Dot(&BoxAB_Vec, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : AB_yx
	D3DXVec3Cross(&Cross, &BoxA_y_e, &BoxB_x_e);
	rA = GetAxisProjectionlength(&Cross, &BoxA_x, &BoxA_z);
	rB = GetAxisProjectionlength(&Cross, &BoxB_y, &BoxB_z);
	L = fabs(D3DXVec3Dot(&BoxAB_Vec, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : AB_yy
	D3DXVec3Cross(&Cross, &BoxA_y_e, &BoxB_y_e);
	rA = GetAxisProjectionlength(&Cross, &BoxA_x, &BoxA_z);
	rB = GetAxisProjectionlength(&Cross, &BoxB_x, &BoxB_z);
	L = fabs(D3DXVec3Dot(&BoxAB_Vec, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : AB_yz
	D3DXVec3Cross(&Cross, &BoxA_y_e, &BoxB_z_e);
	rA = GetAxisProjectionlength(&Cross, &BoxA_x, &BoxA_z);
	rB = GetAxisProjectionlength(&Cross, &BoxB_x, &BoxB_y);
	L = fabs(D3DXVec3Dot(&BoxAB_Vec, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : AB_zx
	D3DXVec3Cross(&Cross, &BoxA_z_e, &BoxB_x_e);
	rA = GetAxisProjectionlength(&Cross, &BoxA_x, &BoxA_y);
	rB = GetAxisProjectionlength(&Cross, &BoxB_y, &BoxB_z);
	L = fabs(D3DXVec3Dot(&BoxAB_Vec, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : AB_zy
	D3DXVec3Cross(&Cross, &BoxA_z_e, &BoxB_y_e);
	rA = GetAxisProjectionlength(&Cross, &BoxA_x, &BoxA_y);
	rB = GetAxisProjectionlength(&Cross, &BoxB_x, &BoxB_z);
	L = fabs(D3DXVec3Dot(&BoxAB_Vec, &Cross));
	if (L > rA + rB)
		return false;

	// ������ : AB_zz
	D3DXVec3Cross(&Cross, &BoxA_z_e, &BoxB_z_e);
	rA = GetAxisProjectionlength(&Cross, &BoxA_x, &BoxA_y);
	rB = GetAxisProjectionlength(&Cross, &BoxB_x, &BoxB_y);
	L = fabs(D3DXVec3Dot(&BoxAB_Vec, &Cross));
	if (L > rA + rB)
		return false;

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	return true;

}

// �������ɓ��e���ꂽ���������瓊�e���������Z�o
float CHitBox::GetAxisProjectionlength(
	D3DXVECTOR3* Unit_Vec,
	D3DXVECTOR3* Box_x,
	D3DXVECTOR3* Box_y,
	D3DXVECTOR3* Box_z)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	float r1 = fabs(D3DXVec3Dot(Unit_Vec, Box_x));
	float r2 = fabs(D3DXVec3Dot(Unit_Vec, Box_y));
	float r3 = Box_z ? (fabs(D3DXVec3Dot(Unit_Vec, Box_z))) : 0;
	return r1 + r2 + r3;
}

void CHitBox::SetSAT()
{
	//x��
	m_Box.Axis_VectorLength[0] = m_Box.BoxSize.x;
	m_Box.Axis_Vector[0] = GetTriangleNor(m_Box.BoxVtx[1], m_Box.BoxVtx[2], m_Box.BoxVtx[6]);
	//y��
	m_Box.Axis_VectorLength[1] = m_Box.BoxSize.y;
	m_Box.Axis_Vector[1] = GetTriangleNor(m_Box.BoxVtx[4], m_Box.BoxVtx[5], m_Box.BoxVtx[6]);
	//z��
	m_Box.Axis_VectorLength[2] = m_Box.BoxSize.z;
	m_Box.Axis_Vector[2] = GetTriangleNor(m_Box.BoxVtx[2], m_Box.BoxVtx[3], m_Box.BoxVtx[7]);
}