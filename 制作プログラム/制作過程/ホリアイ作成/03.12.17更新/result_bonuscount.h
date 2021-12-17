//=============================================================================
//
// ���U���g�̃{�[�i�X�J�E���g�`�揈�� [result_bonuscount.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_BONUSCOUNT_H_
#define _RESULT_BONUSCOUNT_H_

#include "main.h"
#include "scene.h"
#include "result.h"
#include "ranking.h"
#include "score.h"

// �}�N����`
#define RESULT_BONUS_POS	(D3DXVECTOR3(250.0f, 650.0f, 0.0f))	// �ʏ�J�ڎ��̔z�u
#define RESULT_BONUS_SIZE	(D3DXVECTOR2(20.0f, 30.0f))			// �ꌅ���̃T�C�Y

// �O���錾
class CBonusCount;	// �{�[�i�X�J�E���g�N���X

//==============================================================================
// ���U���g�̃{�[�i�X�J�E���g�`��N���X
//==============================================================================
class CResultBonus : public CResult
{
public:
	CResultBonus(int nPriority = PRIORITY_UI);
	~CResultBonus();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResultBonus *Create(void);

private:
	CBonusCount *m_pBonusCount;	// �{�[�i�X�J�E���g�N���X
	int m_nBonus;				// ���ʃ{�[�i�X�J�E���g
};
#endif