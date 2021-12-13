//=============================================================================
//
// �v���C���[���[�V�����Ǘ� [motion_player.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _MOTION_PLAYER_H_
#define _MOTION_PLAYER_H_

#include "main.h"
#include "motion.h"

//==============================================================================
// �v���C���[���[�V�����N���X
//==============================================================================
class CMotionPlayer : public CMotion
{
public:
	// ���[�V�����̎��
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,	// �j���[�g����
		MOTIONTYPE_WALK,		// ���s
		MOTIONTYPE_RUN,			// ���s
		MOTIONTYPE_JUMP,		// �W�����v
		MOTIONTYPE_LANDING,		// ���n
		MOTIONTYPE_CLEAR,		// �N���A�|�[�Y
		MOTIONTYPE_MAX
	}MOTIONTYPE;

	CMotionPlayer();
	~CMotionPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(MOTIONTYPE motionType);	// ���[�V�����̍X�V
	void Draw(void);					// ���f���`��

	static CMotionPlayer *Create(void);

	// ���[�V������Ԃ̎擾�E�ݒ�
	MOTIONTYPE GetMotion(void) { return m_motionType; }
	void SetMotion(MOTIONTYPE motionType) { m_motionType = motionType; }

	// �t���[���J�E���g�̎擾�E�ݒ�
	int GetFrameCnt(void) { return m_nFrameCnt; }
	void SetFrameCnt(int nCnt) { m_nFrameCnt = nCnt; }

	// �L�[�J�E���g�̎擾�E�ݒ�
	int GetKeyCnt(void) { return m_nKeyCnt; }
	void SetKeyCnt(int nCnt) { m_nKeyCnt = nCnt; }

	// ���n��Ԃ̎擾�E�ݒ�
	//bool GetLanding(void) { return m_bLand; }
	//void SetLanding(bool bLand) { m_bLand = bLand; }

private:
	// ���[�V�������
	MOTIONTYPE m_motionType;			// �v���C���[�̃��[�V����
	MOTIONTYPE m_motionTypeOld;			// �ȑO�̃��[�V����
};
#endif