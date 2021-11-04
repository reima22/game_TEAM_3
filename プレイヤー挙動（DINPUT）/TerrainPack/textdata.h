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
class CTextDataPlayer;		// �v���C���[�f�[�^�N���X
class CTextDataObject;		// �I�u�W�F�N�g�f�[�^�N���X
class CTextDataTexture;		// �e�N�X�`���f�[�^�N���X
class CTextDataPause;		// �|�[�Y�f�[�^�N���X
class CTextDataTerrain;
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
		TEXTDATA_TEXTURE,		// �e�N�X�`���f�[�^
		TEXTDATA_PAUSE,			// �|�[�Y�f�[�^
		TEXTDATA_TERRAIN,		// �n�`�f�[�^
		TEXTDATA_MAX
	}TEXTDATA;

	CTextData();
	~CTextData();

	static CTextData *Create(void);	// ����

	static void LoadTextAll(void);
	static void UninitAll(void);

	static CTextDataPlayer *GetDataPlayer(void) { return m_pDataPlayer; }
	static CTextDataObject *GetDataObject(void) { return m_pDataObject; }
	static CTextDataTexture *GetDataTexture(void) { return m_pDataTexture; }
	static CTextDataPause *GetDataPause(void) { return m_pDataPause; }
	static CTextDataTerrain *GetDataTerrain(void) { return m_pDataTerrain; }
protected:
	static char *m_pFileName[TEXTDATA_MAX];		// �ǂݍ��ރt�@�C�����p�X
	static CTextDataPlayer *m_pDataPlayer;		// �v���C���[�f�[�^
	static CTextDataObject *m_pDataObject;		// �I�u�W�F�N�g�f�[�^
	static CTextDataTexture *m_pDataTexture;	// �e�N�X�`���f�[�^
	static CTextDataPause *m_pDataPause;		// �|�[�Y�f�[�^
	static CTextDataTerrain *m_pDataTerrain;
};

#endif