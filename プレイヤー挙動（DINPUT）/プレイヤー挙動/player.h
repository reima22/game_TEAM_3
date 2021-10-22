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

class CModel;
class CShadow;

// �}�N����`
#define KEYNUM_MAX	(10)	// �L�[�̍ő吔
#define MOVE_MOTION	(0.1f)	// �ړ����[�V�������s�����x
#define RUN_MOTION	(2.0f)	// ���郂�[�V�������s�����x
#define SPEED_DOWN	(0.2f)	// �����W��
#define GRAVITY_SCALE	(0.6f)	// �d��
#define WALK_SPEED	(0.5f)	// ����
#define RUN_SPEED	(1.0f)	// ����

//==============================================================================
// �v���C���[�Ǘ��N���X
//==============================================================================
class CPlayer : public CScene3D
{
public:
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,	// �j���[�g����
		MOTIONTYPE_WALK,		// ���s
		MOTIONTYPE_RUN,			// ���s
		MOTIONTYPE_JUMP,		// �W�����v
		MOTIONTYPE_STEP,		// ���n
		MOTIONTYPE_CLEAR,		// �N���A�|�[�Y
		MOTIONTYPE_MAX
	}MOTIONTYPE;

	// �L�[�v�f
	typedef enum
	{
		KEY_POS_X = 0,	// posX
		KEY_POS_Y,		// posY
		KEY_POS_Z,		// posZ
		KEY_ROT_X,		// rotX
		KEY_ROT_Y,		// rotY
		KEY_ROT_Z,		// rotZ
		KEY_MAX
	}KEY;

	CPlayer();
	~CPlayer();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *Create(D3DXVECTOR3 pos);

	// ���[�V�����̍X�V
	void UpdateMotion(MOTIONTYPE motionType);
	MOTIONTYPE GetMotion(void) { return m_motionType; }						// �擾
	void SetMotion(MOTIONTYPE motionType) { m_motionType = motionType; }	// �ݒ�

	int GetFrameCnt(void) { return m_nFrameCnt; }
	int GetKeyCnt(void) { return m_nKeyCnt; }

	// �ʒu�̎擾�E�ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	// �����̎擾�E�ݒ�
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	D3DXVECTOR3 GetRotDest(void) { return m_rotDest; }

	// �ړ��͂̎擾
	D3DXVECTOR3 GetMove(void) { return m_move;  }

	// �ړ�����
	void MovePlayer(void);

private:
	// ���f�����
	int m_nNumParts;			// �p�[�c��

	CModel **m_apModel;			// ���f���ւ̃|�C���^
	int *m_aIndexParent;		// �e���f���̃C���f�b�N�X
	float **m_aOffset;			// �e���f������̃I�t�Z�b�g

	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����

	D3DXVECTOR3 m_move;			// �ړ���
	//D3DXVECTOR3 m_posOld;		// �ߋ��̈ʒu
	D3DXVECTOR3 m_rotDest;		// �ߋ��̌���

	bool m_bJump;				// �W�����v���Ă���
	bool m_bLand;				// ���n���Ă���
	int m_nJumpCnt;				// �W�����v�{�^���������J�E���g

	int m_nDashCnt;				// �_�b�V�����Ă��鎞�̃J�E���g
	float m_fDashPower;			// �_�b�V����

	// ���[�V�������
	MOTIONTYPE m_motionType;			// �v���C���[�̃��[�V����
	MOTIONTYPE m_motionTypeOld;			// �ȑO�̃��[�V����
	float ***m_aKey[MOTIONTYPE_MAX];	// �L�[�v�f
	int m_nNumKey[MOTIONTYPE_MAX];		// �L�[�̐�
	bool m_bLoop;						// ���[�v���邩
	int *m_pFrame[MOTIONTYPE_MAX];		// �t���[����

	D3DXVECTOR3 *m_posMemo;				// �u�����h�ۑ��p�ʒu���
	D3DXVECTOR3 *m_rotMemo;				// �u�����h�ۑ��p�������
	bool m_bBlendMotion;				// 

	int m_nKeyCnt;						// �L�[�̃J�E���^
	int m_nFrameCnt;					// �t���[���̃J�E���^

	CShadow *m_pShadow;					// �e�|�C���^
};
#endif
