//=============================================================================
//
// �e�L�X�g�f�[�^�i3D�I�u�W�F�N�g�j�Ǘ� [textdata_object.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_OBJECT_H_
#define _TEXTDATA_OBJECT_H_

#include "main.h"
#include "textdata.h"

//==============================================================================
// �z�u�I�u�W�F�N�g�Ǘ��N���X
//==============================================================================
class CTextDataObject : public CTextData
{
public:
	CTextDataObject();
	~CTextDataObject();

	void LoadData(STAGEINFO stage);
	void Unload(void);

	static CTextDataObject *Create(STAGEINFO stage);	// ����

	char *GetFileName(int nType) { return m_pFileObjectName[nType]; }				// �t�@�C�����̎擾
	int GetNumObject(void) { return m_nNumObject; }									// �I�u�W�F�N�g���̎擾
	int GetTypeObject(int nIdx) { return m_pType[nIdx]; }							// ��ނ̎擾

	D3DXVECTOR3 GetPosition(int nIdx) { return m_pPos[nIdx]; }						// �ʒu
	D3DXVECTOR3 GetRotation(int nIdx) { return m_pRot[nIdx]; }						// �p�x
	D3DXVECTOR2 GetShadowSize(int nIdx) { return m_pShadowSize[nIdx]; }				// �e�̃T�C�Y

	//float GetInfo(int nIdx, OBJECTINFO info) { return m_pObjectInfo[nIdx][info]; }	// �ʒu�E�p�x�̎擾
	//float GetShadowWidth(int nIdx) { return m_pShadowWidth[nIdx]; }					// �e�̕�
	//float GetShadowDepth(int nIdx) { return m_pShadowDepth[nIdx]; }					// �e�̉��s

	bool GetSavePoint(int nIdx) { return m_pSavePoint[nIdx]; }						// ���Ԓn�_�̉�
	bool GetStartPoint(int nIdx) { return m_pStartPoint[nIdx]; }					// �X�^�[�g�n�_�̉�
	bool GetGoalPoint(int nIdx) { return m_pGoalPoint[nIdx]; }						// �S�[���n�_�̉�

	int GetStartIdx(void) { return m_nStartPointIdx; }

private:
	int m_nNumFile;					// �t�@�C�����̑���
	char **m_pFileObjectName;		// �t�@�C�����|�C���^
	char **m_pFileObjectNameLoad;	// �ǂݎ��p�t�@�C�����ϐ�

	int *m_pType;					// ���
	D3DXVECTOR3 *m_pPos;			// �ʒu
	D3DXVECTOR3 *m_pRot;			// �p�x
	D3DXVECTOR2 *m_pShadowSize;		// �e�̃T�C�Y

	bool *m_pSavePoint;				// ���Ԓn�_�̉�
	bool *m_pStartPoint;			// �X�^�[�g�n�_�̉�
	bool *m_pGoalPoint;				// �S�[���n�_�̉�
	int m_nStartPointIdx;			// �X�^�[�g�n�_�̃C���f�b�N�X

	int m_nNumObject;				// �I�u�W�F�N�g�̑���
};

#endif
