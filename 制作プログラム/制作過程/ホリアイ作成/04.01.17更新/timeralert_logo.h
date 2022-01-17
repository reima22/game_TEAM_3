//=============================================================================
//
// �^�C�}�[�A���[�g���S�`�揈�� [timeralert_logo.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TIMERALERT_LOGO_H_
#define _TIMERALERT_LOGO_H_

#include "main.h"
#include "scene2D.h"

// �}�N����`
#define ALERT_SIZE	(D3DXVECTOR2(400.0f, 80.0f))
#define ALERT_POS	(D3DXVECTOR3(SCREEN_WIDTH + ALERT_SIZE.x, 360.0f, 0.0f))

//==============================================================================
// �^�C�}�[�A���[�g�N���X
//==============================================================================
class CAlertLogo : public CScene2D
{
public:
	// �ړ����
	typedef enum
	{
		ALERTLOGOMOVE_NONE = 0,	// �������
		ALERTLOGOMOVE_START,	// �ړ��J�n
		ALERTLOGOMOVE_STOP,		// �ꎞ��~
		ALERTLOGOMOVE_RESTART,	// �ړ��ĊJ
		ALERTLOGOMOVE_END,		// �I��
	}ALERTLOGOMOVE;

	CAlertLogo(int nPriority = PRIORITY_UI);
	~CAlertLogo();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CAlertLogo *Create(void);

	void MoveTypeNext(void) { if (m_alertLogoMove == ALERTLOGOMOVE_NONE)m_alertLogoMove = (ALERTLOGOMOVE)(m_alertLogoMove + 1); }
	void MoveLogo(void);

private:
	CScene2D *m_pScene2D;			// 2D�|���S���N���X
	D3DXVECTOR3 m_pos;				// �ʒu
	ALERTLOGOMOVE m_alertLogoMove;	// �ړ����
	int m_nCntStop;					// ��~�ԃJ�E���g
};

#endif#pragma once
