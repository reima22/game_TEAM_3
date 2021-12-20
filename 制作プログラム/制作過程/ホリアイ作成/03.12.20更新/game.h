
//=============================================================================
//
// �Q�[�����[�h���� [game.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "mode.h"

// �}�N����`
#define LOGO_POS	(D3DXVECTOR3(640.0f, 360.0f,0.0f))
#define LOGO_SIZE	(D3DXVECTOR2(480.0f,80.0f))

// �O���錾
class CSceneX;			// �V�[��X�N���X
class CPlayer;			// �v���C���[�N���X
class CObject;			// �I�u�W�F�N�g�N���X
class CPause;			// �|�[�Y�N���X
class CTerrain;			// ���b�V��
class CTimer;			// �^�C�}�[�N���X
class CFall;			// �������N���X
class CSound;			// �T�E���h�N���X
class CMeshfield;		// ���b�V���t�B�[���h�N���X
class CStartCntdown;	// �J�n���J�E���g�_�E���N���X
class CFog;				// �t�H�O���ʃN���X
class CBonus;			// �{�[�i�X�N���X
class CCheckpointLogo;	// �`�F�b�N�|�C���g���S�N���X

//==============================================================================
// �Q�[�����[�h�N���X
//==============================================================================
class CGame : public CMode
{
public:
	// �t�F�C�Y����
	typedef enum
	{
		CLEARPHASE_NONE = 0,	// �N���A����Ȃ�
		CLEARPHASE_WAIT,		// �ҋ@
		CLEARPHASE_PAUSE,		// �N���A�|�[�Y���o
		CLEARPHASE_FADE,		// �t�F�[�h�A�E�g
		CLEARPHASE_MAX
	}CLEARPHASE;

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

	void SetStageObject(void);

	void EndGame(void);
	void GameClear(void);
	void GameOver(void);

	void CreateLogo(void);

	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CTerrain *GetTerrain(void) { return m_pTerrain; }
	static CTimer *GetTimer(void) { return m_pTimer; }
	static CFall *GetFall(void) { return m_pFall; }
	static CObject *GetPointObject(int nCnt) { return m_pObject[nCnt]; }
	static CMeshfield *GetMeshField(int nIdx) { return m_pMeshField[nIdx]; }	// ���b�V���t�B�[���h�|�C���^
	static CStartCntdown *GetStartCntdown(void) { return m_pStartCntdown; }		// �J�n���J�E���g�_�E���N���X
	static CFog *GetFog(void) { return m_pFog; }								// �t�H�O�擾
	static CBonus *GetBonus(void) { return m_pBonus; }
	static CCheckpointLogo *GetCheckPointLogo(void) { return m_pCheckPointLogo; }


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

	static CTimer *m_pTimer;				// �^�C�}�[�̃|�C���^
	static CFall *m_pFall;					// �������̃|�C���^
	static CTerrain *m_pTerrain;			// ���b�V��	

	static CObject **m_pObject;				// �I�u�W�F�N�g�̃|�C���^
	static CMeshfield **m_pMeshField;		// �I���W�i�����b�V��
	static CStartCntdown *m_pStartCntdown;	// �J�n���J�E���g�_�E���N���X
	static CFog *m_pFog;					// �t�H�O���ʃN���X

	static bool m_bGameEnd;					// �Q�[���I���̃t���O
	static int m_nClearDirectingCnt;		// �N���A���o�J�E���g

	static CLEARPHASE m_clearPhase;			// �N���A���̃t�F�C�Y����
	static GAMEOVERPHASE m_gameoverPhase;	// �Q�[���I�[�o�[���̃t�F�[�Y����

	CScene2D *m_pResultLogo;				// ���ʃ��S

	static CBonus *m_pBonus;				// �{�[�i�X�N���X�|�C���^
	static CCheckpointLogo * m_pCheckPointLogo;	// �`�F�b�N�|�C���g���S
};

#endif