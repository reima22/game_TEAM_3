//=============================================================================
//
// �^�C�}�[�J�E���g�`�揈�� [timer_count.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TIMER_COUNT_H_
#define _TIMER_COUNT_H_

#include "main.h"
#include "timer.h"

// �}�N����`
#define TIMER_DIGIT_NUM	(3)	// �ő包��

// �O���錾
class CNumber;

//==============================================================================
// �^�C�}�[�J�E���g�N���X
//==============================================================================
class CTimerCount : public CTimer
{
public:
	CTimerCount();
	~CTimerCount();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimerCount *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	void TimerDecrease(void);		// �^�C�}�[����

	// �^�C�}�[���l�̎擾�E�ݒ�
	int GetNumber(void) { return m_nTimer; }
	void SetNumber(int nTimer);

	// �^�C�}�[�J�E���g�J�n�t���O�ݒ�
	bool GetStartCnt(void) { return m_bStartCnt; }
	void SetStartCnt(bool bStartCnt) { m_bStartCnt = bStartCnt; }

	// �^�C�}�[�̈��p��
	static int GetTimerNum(void) { return m_nTimerResult; }

private:
	CNumber *m_apNumber[TIMER_DIGIT_NUM];	// �i���o�[�N���X�|�C���^
	int m_nTimer;							// �^�C�}�[���l
	int m_nDecereaseCnt;					// �����J�E���g
	bool m_bStartCnt;						// �J�E���g�J�n�̃t���O
	static int m_nTimerResult;				// ���U���g�ֈ����p���l
};

#endif
