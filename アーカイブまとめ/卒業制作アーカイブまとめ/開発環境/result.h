
//=============================================================================
//
// ���U���g���[�h���� [result.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "scene.h"
#include "mode.h"

// �O���錾
class CResultPicture;		// ���U���g�ɕ\������}�̃N���X
class CResultScore;			// ���U���g�X�R�A�̃N���X
class CResultTimer;			// ���U���g�^�C�}�[�N���X
class CResultBonus;			// ���U���g�{�[�i�X�N���X
class CResultFallCount;		// ���U���g�����J�E���g�N���X
class CResultScoreEx;		// �����U���g�X�R�A�N���X
class CBg;					// �w�i�N���X

//==============================================================================
// ���U���g���[�h�N���X
//==============================================================================
class CResult : public CMode
{
public:
	// �Q�[���I�����̃N���A���
	typedef enum
	{
		ENDSTATE_NONE = 0,		// ���ʂ��o�Ă��Ȃ�
		ENDSTATE_CLEAR,			// �N���A
		ENDSTATE_GAMEOVER,		// �Q�[���I�[�o�[
		ENDSTATE_MAX
	}ENDSTATE;

	// �\������}�̎��
	typedef enum
	{
		PICTYPE_MAIN = 0,		// ���C���̕\��
		PICTYPE_YOURSCORE,		// �X�R�A�\�����S
		PICTYPE_TIMERLOGO,		// �^�C�}�[���S
		PICTYPE_COUNTLOGO,		// �J�E���g���S
		PICTYPE_BONUSLOGO,		// �{�[�i�X���S
		PICTYPE_TIMERMARK_0,	// �^�C�}�[�Z�p�L��0
		PICTYPE_TIMERMARK_1,	// �^�C�}�[�Z�p�L��1
		PICTYPE_TIMERMARK_2,	// �^�C�}�[�Z�p�L��2
		PICTYPE_COUNTMARK_0,	// �J�E���g�Z�p�L��0
		PICTYPE_COUNTMARK_1,	// �J�E���g�Z�p�L��1
		PICTYPE_COUNTMARK_2,	// �J�E���g�Z�p�L��2
		PICTYPE_BONUSMARK_0,	// �{�[�i�X�Z�p�L��0
		PICTYPE_BONUSMARK_1,	// �{�[�i�X�Z�p�L��1
		PICTYPE_BONUSMARK_2,	// �{�[�i�X�Z�p�L��2
		PICTYPE_MAX
	}PICTYPE;

	// ���X�R�A�̎��
	typedef enum
	{
		EXSCORETYPE_TIMER = 0,		// �^�C�}�[�̂��X�R�A
		EXSCORETYPE_TIMER_CALCU,	// �^�C�}�[�X�R�A�̌v�Z����
		EXSCORETYPE_COUNT,			// �����J�E���g�ɂ��X�R�A
		EXSCORETYPE_COUNT_CALCU,	// �J�E���g�X�R�A�̌v�Z����
		EXSCORETYPE_BONUS,			// �{�[�i�X�J�E���g�ɂ��X�R�A
		EXSCORETYPE_BONUS_CALCU,	// �{�[�i�X�X�R�A�̌v�Z����
		EXSCORETYPE_MAX
	}EXSCORETYPE;

	CResult(int nPriority = PRIORITY_DEFAULT);
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResult *Create(void);

	// �X�R�A�\�L�̍X�V
	void UpdateScore(void);

	// �w�i�X�V
	void UpdateBg(void);

	static void SetEndState(ENDSTATE endState) { m_endState = endState; }
	static ENDSTATE GetEndState(void) { return m_endState; }

	// �X�R�A�̎擾
	CResultScoreEx *GetScoreExPoint(EXSCORETYPE type) { return m_pResultScoreEx[type]; }

private:
	static CResultPicture *m_pResultPicture[PICTYPE_MAX];			// �摜�|�C���^
	static CResultScore *m_pResultScore;							// ���U���g�X�R�A�|�C���^
	static CResultTimer *m_pResultTimer;							// ���U���g�^�C�}�[�|�C���^
	static CResultFallCount *m_pResultFallCount;					// ���U���g�������|�C���^
	static CResultScoreEx *m_pResultScoreEx[EXSCORETYPE_MAX];		// �����U���g�X�R�A�|�C���^
	static CResultBonus * m_pResultBonus;							// ���U���g�{�[�i�X�|�C���^

	CBg *m_pBg;					// �w�i�|�C���^
	static ENDSTATE m_endState;	// �Q�[���I�����̏��
};
#endif
