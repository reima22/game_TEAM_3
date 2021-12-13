//=============================================================================
//
// ���U���g�^�C�}�[�`�揈�� [result_timer.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_TIMER_H_
#define _RESULT_TIMER_H_

#include "main.h"
#include "scene.h"
#include "result.h"
#include "ranking.h"
#include "score.h"

// �}�N����`
#define RESULT_TIMER_POS	(D3DXVECTOR3(250.0f, 450.0f, 0.0f))	// �ʏ�J�ڎ��̔z�u
#define RESULT_TIMER_SIZE	(D3DXVECTOR2(20.0f, 30.0f))			// �ꌅ���̃T�C�Y

// �O���錾
class CTimerCount;	// �^�C�}�[�J�E���g�N���X

//==============================================================================
// ���U���g�^�C�}�[�`��N���X
//==============================================================================
class CResultTimer : public CResult
{
public:
	CResultTimer(int nPriority = PRIORITY_UI);
	~CResultTimer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResultTimer *Create(void);

private:
	CTimerCount *m_pTimerCount;	// �����J�E���g�N���X
	int m_nTimer;				// ���ʗ����J�E���g
};
#endif