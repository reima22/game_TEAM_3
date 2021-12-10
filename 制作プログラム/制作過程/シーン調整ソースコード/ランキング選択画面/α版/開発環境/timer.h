//=============================================================================
//
// �^�C�}�[�`�揈�� [timer.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define TIMER_UIBASE_POS	(D3DXVECTOR3(140.0f, 50.0f, 0.0f))	// UI�x�[�X�̈ʒu
#define TIMER_UIBASE_SIZE	(D3DXVECTOR2(140.0f, 50.0f))		// UI�x�[�X�̃T�C�Y
#define TIMER_COUNT_POS		(D3DXVECTOR3(150.0f, 50.0f, 0.0f))	// �J�E���g�̈ʒu
#define TIMER_COUNT_SIZE	(D3DXVECTOR2(20.0f, 40.0f))			// �J�E���g1�����̃T�C�Y
#define TIMER_LOGO_POS		(D3DXVECTOR3(70.0f, 50.0f, 0.0f))	// ���S�̈ʒu
#define TIMER_LOGO_SIZE		(D3DXVECTOR2(60.0f, 40.0f))			// ���S�̃T�C�Y

// �O���錾
class CUiBase;			// UI�x�[�X�N���X
class CTimerCount;		// �^�C�}�[�J�E���g�N���X
class CTimerLogo;		// �^�C�}�[���S�N���X

//==============================================================================
// �^�C�}�[�N���X
//==============================================================================
class CTimer : public CScene
{
public:
	CTimer(int nPriority = PRIORITY_UI);
	~CTimer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimer *Create(void);

	// �^�C�}�[�J�E���g�̎擾
	CTimerCount	*GetTimerCnt(void) { return m_pTimerCount; }

private:
	CUiBase *m_pUiBase;				// UI�x�[�X�N���X
	CTimerCount *m_pTimerCount;		// �^�C�}�[�J�E���g�N���X�|�C���^
	CTimerLogo *m_pTimerLogo;		// �^�C�}�[���S�N���X�|�C���^
};

#endif
