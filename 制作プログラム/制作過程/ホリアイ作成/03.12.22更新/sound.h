//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	CSound();
	~CSound();
	//�T�E���h�t�@�C��
	typedef enum
	{
		SOUND_LABEL_BGM000,				// BGM0
		SOUND_LABEL_BGM001,				// BGM1
		SOUND_LABEL_BGM002,				// BGM2
		SOUND_LABEL_BGM003,				// BGM3
		SOUND_LABEL_BGM004,				// BGM4
		SOUND_LABEL_BGM005,				// BGM5
		SOUND_LABEL_BGM006,				// BGM6
		SOUND_LABEL_SE_JUMP,			// �W�����v��
		SOUND_LABEL_SE_SELECT,			// �Z���N�g��
		SOUND_LABEL_SE_DECIDE,			// ���艹
		SOUND_LABEL_SE_DIVE00,			// �_�C�u��0
		SOUND_LABEL_SE_DIVE01,			// �_�C�u��1
		SOUND_LABEL_SE_DIVE02,			// �_�C�u��2
		SOUND_LABEL_SE_SAVEPOINT,		// ���Ԓn�_���n��
		SOUND_LABEL_SE_CNTDOWN,			// �J�E���g�_�E����
		SOUND_LABEL_SE_COUNT,			// ���l�J�E���g��
		SOUND_LABEL_SE_TITLEENTER,		// �^�C�g���G���^�[
		SOUND_LABEL_SE_SELECTCURSOR,	// �X�e�[�W�Z���N�g�̃J�[�\����
		SOUND_LABEL_SE_SELECTSTAGE,		// �X�e�[�W�Z���N�g��
		SOUND_LABEL_SE_GOAL,			// �S�[��
		SOUND_LABEL_SE_STAGECLEAR,		// �N���A�t�@���t�@�[��
		SOUND_LABEL_SE_TIMEWARNING,		// �c�莞�Ԃ킸��
		SOUND_LABEL_SE_TIMEOVER,		// ���Ԑ؂�
		SOUND_LABEL_SE_GAMEOVER,		// �Q�[���I�[�o�[
		SOUND_LABEL_SE_EARTHQUAKE,		// ����h��
		SOUND_LABEL_SE_FALL_SCCAFORD,	// ���ꗎ����
		SOUND_LABEL_MAX
	}SOUND_LABEL;

	// BGM�̎��
	typedef enum
	{
		BGMTYPE_TITLE = 0,		// �^�C�g��
		BGMTYPE_STAGESELECT,	// �X�e�[�W�Z���N�g
		BGMTYPE_GAME,			// �Q�[��
		BGMTYPE_RESULT,			// ���U���g
		BGMTYPE_RANKING,		// �����L���O
		BGMTYPE_MAX
	}BGMTYPE;

	static HRESULT Init(HWND hWnd);
	static void Uninit(void);
	static HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	static void Stop(void);

	// ��������
	static CSound *Create(HWND hWnd);

private:
	// �p�����[�^�\����
	typedef struct
	{
		char *pFilename;
		int nCntLoop;
	}PARAM;

	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	static HRESULT ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	static IXAudio2 *m_pXAudio2;

	static PARAM m_aParam[SOUND_LABEL_MAX];

	static IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y
};
#endif
