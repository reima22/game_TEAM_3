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
#include "object.h"

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

	char *GetFileName(int nType) { return m_pFileObjectName[nType]; }					// �t�@�C�����̎擾
	int GetNumObject(void) { return m_nNumObject; }										// �I�u�W�F�N�g���̎擾
	int GetTypeObject(int nIdx) { return m_pType[nIdx]; }								// ��ނ̎擾

	D3DXVECTOR3 GetPosition(int nIdx) { return m_pPos[nIdx]; }							// �ʒu
	D3DXVECTOR3 GetRotation(int nIdx) { return m_pRot[nIdx]; }							// �p�x
	D3DXVECTOR2 GetShadowSize(int nIdx) { return m_pShadowSize[nIdx]; }					// �e�̃T�C�Y

	CObject::OBJATTRIBUTE GetObjAttribute(int nIdx) { return m_pObjAttribute[nIdx]; }	// �I�u�W�F�N�g�̑���

	CObject::MOVETYPE GetMoveType(int nIdx) { return m_pMoveType[nIdx]; }				// �ړ��p�^�[��
	float GetMovePower(int nIdx) { return m_pMovePower[nIdx]; }

private:
	int m_nNumFile;							// �t�@�C�����̑���
	char **m_pFileObjectName;				// �t�@�C�����|�C���^
	char **m_pFileObjectNameLoad;			// �ǂݎ��p�t�@�C�����ϐ�

	int *m_pType;							// ���
	D3DXVECTOR3 *m_pPos;					// �ʒu
	D3DXVECTOR3 *m_pRot;					// �p�x
	D3DXVECTOR2 *m_pShadowSize;				// �e�̃T�C�Y

	CObject::OBJATTRIBUTE *m_pObjAttribute;	// �I�u�W�F�N�g�̎��

	CObject::MOVETYPE *m_pMoveType;			// �ړ����@
	float *m_pMovePower;					// �ړ��͂̊���

	int m_nNumObject;						// �I�u�W�F�N�g�̑���
};
#endif