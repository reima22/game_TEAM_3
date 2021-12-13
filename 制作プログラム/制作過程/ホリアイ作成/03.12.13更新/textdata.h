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
#define TEXT_NUM	(128)		// �e�L�X�g�f�[�^�o�C�g��

// �O���錾
class CTextDataPlayer;			// �v���C���[�f�[�^�N���X
class CTextDataObject;			// �I�u�W�F�N�g�f�[�^�N���X
class CTextDataTexture;			// �e�N�X�`���f�[�^�N���X
class CTextDataPause;			// �|�[�Y�f�[�^�N���X
class CTextDataRankingSelect;	// �����L���O�I���f�[�^�N���X
class CTextDataTerrain;			// ���b�V���f�[�^�N���X
class CTextDataMeshfield;		// ���b�V���t�B�[���h�f�[�^
class CTextDataRanking;			// �����L���O�f�[�^
class CTextDataSound;			// �T�E���h�f�[�^�N���X

								//==============================================================================
								// �e�L�X�g�Ǘ��N���X
								//==============================================================================
class CTextData
{
public:
	// �e�L�X�g�f�[�^�̎��
	typedef enum
	{
		TEXTDATA_SYSTEM = 0,	// �Q�[�����[���f�[�^
		TEXTDATA_PLAYER,		// �v���C���[�̃f�[�^
		TEXTDATA_TEXTURE,		// �e�N�X�`���f�[�^
		TEXTDATA_PAUSE,			// �|�[�Y�f�[�^
		TEXTDATA_RANKINGSELECT,	// �����L���O�I���f�[�^
		TEXTDATA_TERRAIN,		// ���b�V���n�`�f�[�^
		TEXTDATA_MESHFIELD,		// ���b�V���t�B�[���h�f�[�^
		TEXTDATA_SOUND,			// �T�E���h�f�[�^
		TEXTDATA_MAX
	}TEXTDATA;

	// �X�e�[�W���
	typedef enum
	{
		STAGEINFO_VALLEY = 0,	// �k�J�X�e�[�W���
		STAGEINFO_SEA,			// �C�m�X�e�[�W���
		STAGEINFO_LAVA,			// �n��X�e�[�W���
		STAGEINFO_MAX
	}STAGEINFO;

	CTextData();
	~CTextData();

	static CTextData *Create(void);	// ����

	static void LoadTextAll(void);
	static void UninitAll(void);

	// �f�[�^�̎擾
	static CTextDataPlayer *GetDataPlayer(void) { return m_pDataPlayer; }
	static CTextDataObject *GetDataObject(int nStage) { return m_pDataObject[nStage]; }
	static CTextDataTexture *GetDataTexture(void) { return m_pDataTexture; }
	static CTextDataPause *GetDataPause(void) { return m_pDataPause; }
	static CTextDataTerrain *GetDataTerrain(void) { return m_pDataTerrain; }
	static CTextDataMeshfield *GetDataMeshfield(void) { return m_pDataMeshfield; }
	static CTextDataRanking	*GetDataRanking(int nStage) { return m_apDataRanking[nStage]; }
	static CTextDataRankingSelect *GetDataSelectRanking(void) { return m_pDataRankingSelect; }

protected:
	static char *m_pFileName[TEXTDATA_MAX];			// �ǂݍ��ރt�@�C�����p�X
	static char *m_pFileNameObj[STAGEINFO_MAX];		// �ǂݎ��I�u�W�F�N�g�t�@�C�����p�X
	static char *m_pFileNameRanking[STAGEINFO_MAX];	// �ǂݎ�郉���L���O�t�@�C�����p�X

private:
	static CTextDataPlayer *m_pDataPlayer;						// �v���C���[�f�[�^
	static CTextDataObject *m_pDataObject[STAGEINFO_MAX];		// �I�u�W�F�N�g�f�[�^
	static CTextDataTexture *m_pDataTexture;					// �e�N�X�`���f�[�^
	static CTextDataPause *m_pDataPause;						// �|�[�Y�f�[�^
	static CTextDataTerrain *m_pDataTerrain;					// ���b�V���n�`�f�[�^�|�C���^
	static CTextDataMeshfield *m_pDataMeshfield;				// ���b�V���t�B�[���h�f�[�^
	static CTextDataRanking *m_apDataRanking[STAGEINFO_MAX];	// �����L���O�f�[�^
	static CTextDataRankingSelect *m_pDataRankingSelect;		// �����L���O�I���f�[�^

	static CTextDataSound *m_pDataSound;						// �T�E���h�f�[�^�|�C���^
};

#endif