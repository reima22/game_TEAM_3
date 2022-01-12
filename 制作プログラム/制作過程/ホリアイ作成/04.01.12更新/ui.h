//=============================================================================
//
// UI�̕`�揈�� [ui.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _UI_H_
#define _UI_H_

#include "main.h"
#include "scene.h"

// �O���錾
class CTimer;			// �^�C�}�[UI
class CFall;			// ������UI
class CBonus;			// �{�[�i�XUI
class CStartCntdown;	// �J�E���g�_�E�����S
class CCheckpointLogo;	// �`�F�b�N�|�C���g���S
class CAlertLogo;		// �^�C�}�[�A���[�g���S

//==============================================================================
// UI�N���X
//==============================================================================
class CUi : public CScene
{
public:
	CUi(int nPriority = PRIORITY_UI);
	~CUi();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CUi *Create(void);

	static CTimer *GetTimer(void) { return m_pTimer; }
	static CFall *GetFall(void) { return m_pFall; }
	static CStartCntdown *GetStartCntdown(void) { return m_pStartCntdown; }
	static CBonus *GetBonus(void) { return m_pBonus; }
	static CCheckpointLogo *GetCheckPointLogo(void) { return m_pCheckPointLogo; }
	static CAlertLogo *GetAlertLogo(void) { return m_pAlertLogo; }

private:
	static CTimer *m_pTimer;					// �^�C�}�[�̃|�C���^
	static CFall *m_pFall;						// �������̃|�C���^
	static CBonus *m_pBonus;					// �{�[�i�X�N���X�|�C���^
	static CStartCntdown *m_pStartCntdown;		// �J�n���J�E���g�_�E���N���X
	static CCheckpointLogo *m_pCheckPointLogo;	// �`�F�b�N�|�C���g���S
	static CAlertLogo *m_pAlertLogo;			// �^�C�}�[�A���[�g���S
};

#endif