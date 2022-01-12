//=============================================================================
//
// �v���C���[�Ǘ� [player.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"

// �O���錾
class CModel;			// ���f���N���X
class CShadow;			// �e�N���X
class CShadowS;			// �X�e���V���V���h�E
class CMotionPlayer;	// �v���C���[�̃��[�V�����N���X

// �}�N����`
#define KEYNUM_MAX		(10)		// �L�[�̍ő吔
#define MOVE_MOTION		(0.1f)		// �ړ����[�V�������s�����x�
#define RUN_MOTION		(2.0f)		// ���郂�[�V�������s�����x�
#define SPEED_DOWN		(0.2f)		// �����W��
#define GRAVITY_SCALE	(0.6f)		// �d��
#define WALK_SPEED		(0.5f)		// �������x
#define RUN_SPEED		(1.0f)		// ���鑬�x
#define SPEED_RANK_CNT	(60)		// ���x�����N�J�E���g
#define AIR_CONTROL		(30)		// �󒆂ő���\�Ȋ��ԃJ�E���g

//==============================================================================
// �v���C���[�Ǘ��N���X
//==============================================================================
class CPlayer : public CScene3D
{
public:
	typedef enum
	{
		RESETPHASE_NONE = 0,	// �����s
		RESETPHASE_WAIT,		// �ҋ@���
		RESETPHASE_ON,			// ���Z�b�g���s
		RESETPHASE_MAX
	}RESETPHASE;

	CPlayer();
	~CPlayer();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *Create(void);

	// �ړ�����
	void MovePlayer(void);
	void ControlPlayer(void);

	void Collision(void);

	// ��������
	void ResetPlayer(void);

	// �N���A���̃��[�V�����ݒ�
	void ClearMotion(void);

	// �ʒu�̎擾�E�ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	// �����̎擾�E�ݒ�
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	// �ߋ��̈ʒu�̎擾
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }

	// ���n��Ԃ̎擾�E�ݒ�
	bool GetLandObj(void) { return m_bLandObj; }
	void SetLandObj(bool bLand) { m_bLandObj = bLand; }
	bool GetLandMesh(void) { return m_bLandMesh; }
	void SetLandMesh(bool bLand) { m_bLandMesh = bLand; }

	// �ߋ��̊p�x�擾
	D3DXVECTOR3 GetRotDest(void) { return m_rotDest; }

	// �ړ��͂̎擾
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

	// �����蔻�蔼�a�̎擾
	float GetRadius(void) { return m_fRadius; }

	// �����蔻�荂���̎擾
	float GetHeight(void) { return m_fHeight; }

	// �_�b�V���J�E���g�̐ݒ�
	void SetDashCnt(int nCnt) { m_nDashCnt = nCnt; }

	// ���X�|�[���n�_�̎擾
	D3DXVECTOR3 GetPosSave(void) { return m_posSave; }

	// ���[�V�������
	CMotionPlayer *GetMotionPlayer(void) { return m_pMotionPlayer; }

	// �Q�[���I���t���O
	bool GetGameClear(void) { return m_bSetGameClear; }
	void SetGameClear(bool bSetGameClear) { m_bSetGameClear = bSetGameClear; }

	bool GetGameOver(void) { return m_bSetGameOver; }
	void SetGameOver(bool bSetGameOver) { m_bSetGameOver = bSetGameOver; }

	// ���Z�b�g��Ԃ̎擾
	RESETPHASE GetResetPhase(void) { return m_resetPhase; }

	// ���Z�b�g��Ԃ̐؂�ւ�
	void ResetOn(void)
	{ if (m_resetPhase == RESETPHASE_NONE) 
		m_resetPhase = RESETPHASE_WAIT; 
		m_pos = m_posNeutral;
	}

private:
	// ���f�����
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����

	D3DXVECTOR3 m_posNeutral;			// �����ʒu

	D3DXVECTOR2 m_shadowSize;			// �e�̑傫��
	D3DXVECTOR3 m_move;					// �ړ���
	D3DXVECTOR3 m_posOld;				// �ߋ��̈ʒu
	D3DXVECTOR3 m_rotDest;				// �ߋ��̌���

	float m_fRadius;					// �����蔻�蔼�a
	float m_fHeight;					// �����蔻�荂��

	bool m_bJump;						// �W�����v���Ă���(�؋���)

	int m_nCntAir;						// �؋�J�E���g
	bool m_bAirControl;					// �󒆐���t���O
	
	bool m_bLanding;					// ���n���Ă��锻��
	bool m_bLandObj;					// �I�u�W�F�N�g�ɒ��n���Ă���
	bool m_bLandMesh;					// ���b�V���̒��n���Ă���

	int m_nJumpCnt;						// �W�����v�{�^���������J�E���g

	int m_nDashCnt;						// �_�b�V�����Ă��鎞�̃J�E���g
	float m_fDashPower;					// �_�b�V����

	D3DXVECTOR3 m_posSave;				// ���Ԓn�_���W

	CShadowS *m_pShadowS;				// �X�e���V���V���h�E�|�C���^

	// ���[�V�������
	CMotionPlayer *m_pMotionPlayer;		// ���[�V�������
	bool m_bSetGameClear;				// �Q�[���N���A����
	bool m_bSetGameOver;				// �Q�[���I�[�o�[����

	int m_nCntSandEffect;				// �����G�t�F�N�g�̔����J�E���g

	RESETPHASE m_resetPhase;			// ���Z�b�g�t�F�[�Y
	int m_nCntReset;					// ���Z�b�g�t�F�[�Y�̃J�E���g

	D3DXVECTOR3 m_posLava;				// �n�◎���ʒu
	bool m_bIntoLava;					// �n��֗���
};
#endif
