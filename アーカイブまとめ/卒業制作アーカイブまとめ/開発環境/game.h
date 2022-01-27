
//=============================================================================
//
// �Q�[�����[�h���� [game.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "mode.h"

// �O���錾
class CBonus;			// �{�[�i�X�N���X
//class CCheckpointLogo;	// �`�F�b�N�|�C���g���S�N���X
class CGamesetLogo;		// �Q�[�����ʃ��S
//class CFall;			// �������N���X
class CFog;				// �t�H�O���ʃN���X
class CMeshfield;		// ���b�V���t�B�[���h�N���X
class CObject;			// �I�u�W�F�N�g�N���X
class CPause;			// �|�[�Y�N���X
class CPlayer;			// �v���C���[�N���X
//class CStartCntdown;	// �J�n���J�E���g�_�E���N���X
class CTerrain;			// ���b�V��
//class CTimer;			// �^�C�}�[�N���X
class CUi;				// UI�N���X

//==============================================================================
// �Q�[�����[�h�N���X
//==============================================================================
class CGame : public CMode
{
public:
	// �Q�[���N���A�t�F�C�Y
	typedef enum
	{
		CLEARPHASE_NONE = 0,	// �N���A����Ȃ�
		CLEARPHASE_WAIT,		// �ҋ@
		CLEARPHASE_PAUSE,		// �N���A�|�[�Y���o
		CLEARPHASE_FADE,		// �t�F�[�h�A�E�g
		CLEARPHASE_MAX
	}CLEARPHASE;

	// �Q�[���I�[�o�[�t�F�C�Y
	typedef enum
	{
		GAMEOVERPHASE_NONE = 0,		// ���薳��
		GAMEOVERPHASE_WAIT,			// �ҋ@
		GAMEOVERPHASE_DIRECTION,	// ���o
		GAMEOVERPHASE_FADE,			// �t�F�[�h�A�E�g
		GAMEOVERPHASE_MAX
	}GAMEOVERPHASE;

	CGame(int nPriority = PRIORITY_DEFAULT);
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGame *Create(void);

	void SetStageObject(void);	// �X�e�[�W�I�u�W�F�N�g�̐ݒ�

	void EndGame(void);		// �Q�[���I��
	void GameClear(void);	// �Q�[���N���A����
	void GameOver(void);	// �Q�[���I�[�o�[����

	static CPlayer *GetPlayer(void) { return m_pPlayer; }						// �v���C���[�|�C���^
	static CTerrain *GetTerrain(void) { return m_pTerrain; }					// ���S���胁�b�V���|�C���^
	static CObject *GetPointObject(int nCnt) { return m_ppObject[nCnt]; }		// �I�u�W�F�N�g�|�C���^
	static CMeshfield *GetMeshField(int nIdx) { return m_ppMeshField[nIdx]; }	// ���b�V���t�B�[���h�|�C���^
	static CFog *GetFog(void) { return m_pFog; }								// �t�H�O�擾
	static CUi *GetUi(void) { return m_pUi; }									// UI�̎擾

	// �Q�[���I���t���O�̎擾�E�ݒ�
	static bool GetGameEnd(void) { return m_bGameEnd; }
	static void SetGameEnd(bool bGameEnd) { m_bGameEnd = bGameEnd; }

	// �Q�[���N���A�̃t�F�C�Y�̎擾�E�ݒ�
	static CLEARPHASE GetClearPhase(void) { return m_clearPhase; }
	static void SetClearPhase(CLEARPHASE clearPhase) { m_clearPhase = clearPhase; }

	// �Q�[���I�[�o�[�t�F�C�Y�̎擾�E�ݒ�
	static GAMEOVERPHASE GetOverPhase(void) { return m_gameoverPhase; }
	static void SetOverPhase(GAMEOVERPHASE overPhase) { m_gameoverPhase = overPhase; }

private:
	int m_nNumObject;						// �I�u�W�F�N�g��
	int m_nNumMeshfield;					// ���b�V���t�B�[���h�̐�
	static CPause *m_pPause;				// �|�[�Y�̃|�C���^
	static CPlayer *m_pPlayer;				// �v���C���[�̃|�C���^

	static CTerrain *m_pTerrain;			// ���b�V��	

	static CObject **m_ppObject;				// �I�u�W�F�N�g�̃|�C���^
	static CMeshfield **m_ppMeshField;		// �I���W�i�����b�V��

	static CFog *m_pFog;					// �t�H�O���ʃN���X

	static bool m_bGameEnd;					// �Q�[���I���̃t���O
	static int m_nClearDirectingCnt;		// �N���A���o�J�E���g

	static CLEARPHASE m_clearPhase;			// �N���A���̃t�F�C�Y����
	static GAMEOVERPHASE m_gameoverPhase;	// �Q�[���I�[�o�[���̃t�F�[�Y����

	static CGamesetLogo *m_pGamesetLogo;	// �Q�[���I�����̃��S�|�C���^

	static CUi *m_pUi;						// UI�̃|�C���^
};

#endif