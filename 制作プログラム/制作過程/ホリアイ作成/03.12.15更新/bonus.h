//=============================================================================
//
// �{�[�i�X�J�E���gUI�`�揈�� [bonus.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _BONUS_H_
#define _BONUS_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define BONUS_UIBASE_POS	(D3DXVECTOR3(1130.0f, 150.0f, 0.0f))	// UI�x�[�X�̈ʒu
#define BONUS_UIBASE_SIZE	(D3DXVECTOR2(150.0f, 50.0f))			// UI�x�[�X�̃T�C�Y
#define BONUS_COUNT_POS		(D3DXVECTOR3(1160.0f, 150.0f, 0.0f))	// �J�E���g�̈ʒu
#define BONUS_COUNT_SIZE	(D3DXVECTOR2(20.0f, 40.0f))				// �J�E���g1�����̃T�C�Y
#define BONUS_LOGO_POS		(D3DXVECTOR3(1070.0f, 150.0f, 0.0f))	// ���S�̈ʒu
#define BONUS_LOGO_SIZE		(D3DXVECTOR2(60.0f, 40.0f))				// ���S�̃T�C�Y

// �O���錾
class CBonusLogo;		// �{�[�i�X���S�N���X
class CBonusCount;		// �{�[�i�X�J�E���g�N���X

//==============================================================================
// ������UI�N���X
//==============================================================================
class CBonus : public CScene
{
public:
	CBonus(int nPriority = PRIORITY_UI);
	~CBonus();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBonus *Create(void);

	CBonusCount *GetCount(void) { return m_pBonusCount; }

private:
	CBonusLogo *m_pBonusLogo;	// �{�[�i�X���S�N���X�|�C���^
	CBonusCount *m_pBonusCount;	// �{�[�i�X�J�E���g�N���X�|�C���^
};

#endif#pragma once
