
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

// �}�N����`
//#define LIFE_POS		(D3DXVECTOR3(40.0f, 40.0f, 0.0f))			// ���C�t�z�u�J�n�ʒu
//#define SCORE_POS		(D3DXVECTOR3(1100.0f, 690.0f, 0.0f))		// �X�R�A�z�u�J�n�ʒu
//#define DEFEAT_POS		(D3DXVECTOR3(730.0f, 690.0f, 0.0f))		// ���j���̔z�u�ʒu
//#define INVASION_POS	(D3DXVECTOR3(870.0f, 690.0f, 0.0f))			// �N�����̔z�u�ʒu
//#define STOCK_POS		(D3DXVECTOR3(600.0f, 680.0f, 0.0f))			// �c�@���̔z�u�ʒu
//#define RESULT_GAMEEND	(D3DXVECTOR3(640.0f, 200.0f, 0.0f))		// �Q�[�����ʂ̕`��

// �O���錾
class CSceneX;		// �V�[��X�N���X
class CPlayer;		// �v���C���[�N���X
class CObject;		// �I�u�W�F�N�g�N���X
class CPause;		// �|�[�Y�N���X
class CTerrain;

//==============================================================================
// �Q�[�����[�h�N���X
//==============================================================================
class CGame : public CScene
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGame *Create(void);

	static int GetEndInvasion(void) { return m_nEndInvasion; }
	static bool GetStartGame(void) { return m_bGameStart; }

	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CTerrain *GetTerrain(void) { return m_pTerrain; }

	static CObject *GetPointObject(int nCnt) { return m_pObject[nCnt]; }

private:
	static int m_nClearDefeat;				// �Q�[���N���A�̌��j��
	static int m_nEndInvasion;				// �Q�[���I������N����

	static bool m_bGameStart;				// �Q�[���̊J�n����

	static int m_nCntDownEnd;				// �Q�[���I���܂ł̃J�E���g
	bool m_bSetLogo;
	
	static CPause *m_pPause;				// �|�[�Y�̃|�C���^

	static CPlayer *m_pPlayer;				// �v���C���[�̃|�C���^

	static CObject **m_pObject;				// �I�u�W�F�N�g�̃|�C���^
	int m_nNumObject;						// �I�u�W�F�N�g��

	static CTerrain *m_pTerrain;			// ���b�V��
};

#endif