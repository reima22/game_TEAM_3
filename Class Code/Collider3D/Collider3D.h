//===================================================================
//HeaderFile: Collider3D.h
//Author : Yo jitaku
//===================================================================
#ifndef _COLLIDER3D_H_
#define _COLLIDER3D_H_
#include "main.h"
#include "PhysicsBase.h"
#include "stdlib.h"
#define HITBOX_VERTEX_NUM 8							//�{�b�N�X�̒��_��
#define HITBOX_FACE_NUM 6							//�{�b�N�X�̖ʐ�
#define HITBOX_INDEX_NUM (HITBOX_FACE_NUM * 6)		//�`��K�v��Index��
#define HITBOX_DRAW_TRI_NUM (HITBOX_FACE_NUM * 2)	//���ۂɕ`�悷��̎O�p�`�ʐ�
#define AXIS_NUM 3									//�O��������
typedef struct
{
	D3DXVECTOR3 BoxSizeMin;						//����{�b�N�X���_���W�̍ŏ��l
	D3DXVECTOR3 BoxSizeMax;						//����{�b�N�X���_���W�̍ő�l
	D3DXVECTOR3 BoxSize;						//����{�b�N�X�̃T�C�Y
	D3DXVECTOR3 BoxPos;							//����{�b�N�X�̒��S���W
	D3DXVECTOR3 Rot;							//����{�b�N�X�̊p�x
	D3DXVECTOR3 BoxVtx[HITBOX_VERTEX_NUM];		//�{�b�N�X�̒��_���W
	D3DXVECTOR3 Model_Offset;					//�{�b�N�X�̒��S���W�Ƃ��t�@�C�����S��OFFSET(�����ł͂Ȃ��ꍇ�A�L��)
	D3DXVECTOR3 Axis_Vector[AXIS_NUM];			//�{�b�N�X�������̕����x�N�g��
	float Axis_VectorLength[AXIS_NUM];			//�{�b�N�X�������̒���
}BOX;

class CHitBox :public CPhysics
{
public:
	HRESULT Init();								//������
	void SetHitBox(LPD3DXMESH pMesh);			//�{�b�N�X����
	virtual void PhysicsUpdate();				//�X�V
	virtual void GraphicsDraw();				//�`��
	void DrawHitBox();							//
	bool SAT_func(CHitBox* pTarget);			//�����蔻��֐�
private:
	D3DXVECTOR3 GetVector(int nNum) {			// �w�莲�ԍ��̕����x�N�g�����擾	
		return m_Box.Axis_Vector[nNum];
	}

	FLOAT GetVecLength(int nNum) {				// �w�莲�����̒������擾
		return m_Box.Axis_VectorLength[nNum];
	}
	D3DXVECTOR3 GetPos() {						// �ʒu���擾
		return m_Box.BoxPos;
	}
	D3DXVECTOR3 GetTriangleNor(					//���ʂ̕����x�N�g�������֐�
		D3DXVECTOR3 pos1,
		D3DXVECTOR3 pos2,
		D3DXVECTOR3 pos3);
	float GetAxisProjectionlength(				//�{�b�N�XA�������̏�Ń{�b�N�XB�������̓��e����
		D3DXVECTOR3* Unit_Vec,
		D3DXVECTOR3* Box_x,
		D3DXVECTOR3* Box_y,
		D3DXVECTOR3* Box_z = 0);
	void SetSAT();								//�������̐ݒu
	void SetIndex();							//Index�o�b�t�@�̐ݒu
	void SetVertex();							//���_�o�b�t�@�̐ݒu
	BOX m_Box;
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;			//Index�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;			//���_�o�b�t�@
	LPDIRECT3DDEVICE9 m_pDevice;				//�f�o�C�X�����
	CRenderer *m_pRenderer;						//�����_�����O�̃|�C���^�[
	bool m_DrawHitBox;							//�`���L������̃}�[�N
};
#endif