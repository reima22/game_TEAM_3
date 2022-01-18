//=============================================================================
//
// �{�[�i�X�J�E���g�`�揈�� [bonus_count.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _BONUS_COUNT_H_
#define _BONUS_COUNT_H_

#include "main.h"
#include "bonus.h"
#include "scene2D.h"

// �}�N����`
#define BONUS_DIGIT_NUM	(3)	// �ő包��

// �O���錾
class CNumber;

//==============================================================================
// �������J�E���g�N���X
//==============================================================================
class CBonusCount : public CBonus
{
public:
	CBonusCount();
	~CBonusCount();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBonusCount *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	// ���l�̐ݒ�
	int GetNumber(void) { return m_nBonus; }
	void SetNumber(int nBonus);

	// ���̉��Z
	void AddBonus(int nAdd);

	void SizeReturn(void);

	// ���U���g�ւ̌p��
	static int GetBonusNum(void) { return m_nBonusResult; }

	// ���Ԓn�_�ŕۑ�
	static void SaveBonus(int nSave) { m_nSaveBonus = nSave; }

private:
	CNumber *m_apNumber[BONUS_DIGIT_NUM];	// �i���o�[�N���X�|�C���^
	int m_nBonus;							// �������l
	static int m_nSaveBonus;				// ���Ԓn�_�ŕۑ�����l
	static int m_nBonusResult;				// ���U���g�ֈ����p���l
};
#endif