//=============================================================================
//
// �e�L�X�g�f�[�^�i���b�V���t�B�[���h�j�Ǘ� [textdata_meshfield.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_MESHFIELD_H_
#define _TEXTDATA_MESHFIELD_H_

#include "main.h"
#include "textdata.h"
#include "meshfield.h"

//==============================================================================
// �e�L�X�g�Ǘ��i���b�V���t�B�[���h�j�N���X
//==============================================================================
class CTextDataMeshfield : public CTextData
{
public:
	CTextDataMeshfield();
	~CTextDataMeshfield();

	void LoadData(void);
	void Unload(void);

	static CTextDataMeshfield *Create(void);	// ����

	//char *GetFileName(int nType) { return m_pFileObjectName[nType]; }				// �t�@�C�����̎擾
	//int GetNumObject(void) { return m_nNumObject; }									// �I�u�W�F�N�g���̎擾
	//int GetTypeObject(int nIdx) { return m_pType[nIdx]; }								// ��ނ̎擾
	//float GetInfo(int nIdx, OBJECTINFO info) { return m_pObjectInfo[nIdx][info]; }	// �ʒu�E�p�x�̎擾
	//float GetShadowWidth(int nIdx) { return m_pShadowWidth[nIdx]; }					// �e�̕�
	//float GetShadowDepth(int nIdx) { return m_pShadowDepth[nIdx]; }					// �e�̉��s
	//bool GetSavePoint(int nIdx) { return m_pSavePoint[nIdx]; }						// ���Ԓn�_�̉�

	// ���擾
	int GetNumMesh(void) { return m_nNumMesh; }											// ���b�V����
	int GetTexType(int nIdx) { return m_pType[nIdx]; }									// �e�N�X�`���̎��
	D3DXVECTOR3 GetPosition(int nIdx) { return m_pPos[nIdx]; }
	D3DXVECTOR3 GetRotation(int nIdx) { return m_pRot[nIdx]; }
	D3DXVECTOR2 GetSize(int nIdx) { return m_pSize[nIdx]; }

	int GetWidthPoly(int nIdx) { return m_pWidth[nIdx]; }								// �ʂ̐�
	int GetDepthPoly(int nIdx) { return m_pDepth[nIdx]; }								// �ʂ̐�


	D3DXVECTOR3 GetPosVtx(int nIdx,int nIdxPoint) { return m_pPosVtx[nIdx][nIdxPoint]; }	// ���b�V�����_���

private:
	int *m_pType;			// ���
	D3DXVECTOR3 *m_pPos;	// �ʒu
	D3DXVECTOR3 *m_pRot;	// �p�x
	D3DXVECTOR2 *m_pSize;	// 1�ʓ�����̃T�C�Y
	int *m_pWidth;			// �����̃|���S������
	int *m_pDepth;			// ���s�̃|���S������

	int *m_pIdxPoint;			// �����_��
	D3DXVECTOR3 **m_pPosVtx;	// ���_���W

	int m_nNumMesh;		// ���b�V���̑���
};
#endif