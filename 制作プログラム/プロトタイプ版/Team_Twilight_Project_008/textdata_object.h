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
	typedef enum
	{
		OBJECTINFO_POS_X = 0,	// �ʒuX���W
		OBJECTINFO_POS_Y,		// �ʒuY���W
		OBJECTINFO_POS_Z,		// �ʒuZ���W
		OBJECTINFO_ROT_X,		// �p�xX���W
		OBJECTINFO_ROT_Y,		// �p�xY���W
		OBJECTINFO_ROT_Z,		// �p�xZ���W
		OBJECTINFO_MAX			
	}OBJECTINFO;

	CTextDataObject();
	~CTextDataObject();

	void LoadData(void);
	void Unload(void);

	static CTextDataObject *Create(void);	// ����

	char *GetFileName(int nType) { return m_pFileObjectName[nType]; }				// �t�@�C�����̎擾
	int GetNumObject(void) { return m_nNumObject; }									// �I�u�W�F�N�g���̎擾
	int GetTypeObject(int nIdx) { return m_pType[nIdx]; }							// ��ނ̎擾
	float GetInfo(int nIdx, OBJECTINFO info) { return m_pObjectInfo[nIdx][info]; }	// �ʒu�E�p�x�̎擾
	float GetShadowWidth(int nIdx) { return m_pShadowWidth[nIdx]; }					// �e�̕�
	float GetShadowDepth(int nIdx) { return m_pShadowDepth[nIdx]; }					// �e�̉��s
	bool GetSavePoint(int nIdx) { return m_pSavePoint[nIdx]; }						// ���Ԓn�_�̉�

private:
	int m_nNumFile;					// �t�@�C�����̑���
	char **m_pFileObjectName;		// �t�@�C�����|�C���^
	char **m_pFileObjectNameLoad;	// �ǂݎ��p�t�@�C�����ϐ�

	int *m_pType;					// ���

	float **m_pObjectInfo;			// �I�u�W�F�N�g�̈ʒu�E�p�x���

	float *m_pShadowWidth;			// �e�̕�
	float *m_pShadowDepth;			// �e�̉��s

	bool *m_pSavePoint;				// ���Ԓn�_�̉�

	int m_nNumObject;				// �I�u�W�F�N�g�̑���
};

#endif
