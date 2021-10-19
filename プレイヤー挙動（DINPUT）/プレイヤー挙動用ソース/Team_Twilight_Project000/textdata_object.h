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

private:
	int m_nNumModel;
	char **m_pFileObjectName;
	char **m_pFileObjectNameLoad;

	int m_nType;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
};

#endif#pragma once
