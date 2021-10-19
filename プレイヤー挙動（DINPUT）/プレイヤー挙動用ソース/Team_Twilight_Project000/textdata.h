//=============================================================================
//
// �e�L�X�g�f�[�^�Ǘ� [textdata.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_H_
#define _TEXTDATA_H_

#include "main.h"

// �}�N����`
#define TEXT_NUM	(128)	// �e�L�X�g�f�[�^�o�C�g��

// �O���錾
class CTextDataPlayer;
class CTextDataObject;


//==============================================================================
// �e�L�X�g�Ǘ��N���X
//==============================================================================
class CTextData
{
public:
	// �e�L�X�g�f�[�^�̎��
	typedef enum
	{
		TEXTDATA_RANKING = 0,	// �����L���O�̃f�[�^
		TEXTDATA_SYSTEM,		// �Q�[�����[���f�[�^
		TEXTDATA_PLAYER,		// �v���C���[�̃f�[�^
		TEXTDATA_OBJECT,		// 3D�I�u�W�F�N�g�f�[�^
		TEXTDATA_MAX
	}TEXTDATA;

	CTextData();
	~CTextData();

	static void LoadTextAll(void);
	static CTextDataPlayer *GetDataPlayer(void) { return m_pDataPlayer; }

protected:
	static char *m_pFileName[TEXTDATA_MAX];	// �ǂݍ��ރt�@�C�����p�X
	static CTextDataPlayer *m_pDataPlayer;	// �v���C���[�f�[�^
	static CTextDataObject *m_pDataObject;	// �I�u�W�F�N�g�f�[�^
};

#endif