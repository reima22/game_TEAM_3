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
// �e�L�X�g�Ǘ��isystem�j�N���X
//==============================================================================
class CTextDataObject : public CTextData
{
public:
	CTextDataObject();
	~CTextDataObject();

	void LoadData(void);
	void Uninit(void);

	static CTextDataObject *Create(void);	// ����

	char *GetFileName(int nType) { return m_pFileObjectName[nType]; }	// �t�@�C�����̎擾
	int GetNumObject(void) { return m_nNumObject; }						// �I�u�W�F�N�g���̎擾
	int GetTypeObject(int nIdx) { return m_pType[nIdx]; }				// ��ނ̎擾
	D3DXVECTOR3 GetPosObject(int nIdx) { return m_pPos[nIdx]; }			// �ʒu�̎擾
	D3DXVECTOR3 GetRotObject(int nIdx) { return m_pRot[nIdx]; }			// �����̎擾

private:
	int m_nNumModel;				// ���f���̑���
	char **m_pFileObjectName;		// �t�@�C�����|�C���^
	char **m_pFileObjectNameLoad;	// �ǂݎ��p�t�@�C�����ϐ�

	int *m_pType;					// ���
	D3DXVECTOR3 *m_pPos;			// �ʒu
	D3DXVECTOR3 *m_pRot;			// �p�x
	int m_nNumObject;				// �I�u�W�F�N�g�̑���
	int m_nNumObjectIn;				// �I�u�W�F�N�g�m�ې�
};

#endif
