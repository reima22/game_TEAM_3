//=============================================================================
//
// �������J�E���g�`�揈�� [fall_count.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _FALL_COUNT_H_
#define _FALL_COUNT_H_

#include "main.h"
#include "fall.h"
#include "scene2D.h"

// �}�N����`
#define FALL_DIGIT_NUM	(3)	// �ő包��
#define FALL_COUNT_POS		(D3DXVECTOR3(1160.0f, 50.0f, 0.0f))	// �J�E���g�̈ʒu
#define FALL_COUNT_SIZE		(D3DXVECTOR2(20.0f, 40.0f))			// �J�E���g1�����̃T�C�Y

// �O���錾
class CNumber;

//==============================================================================
// �������J�E���g�N���X
//==============================================================================
class CFallCount : public CFall
{
public:
	CFallCount();
	~CFallCount();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFallCount *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	// ���l�̐ݒ�
	int GetNumber(void) { return m_nFall; }
	void SetNumber(int nFall);

	// �������̉��Z
	void AddFall(int nAdd);

	void SizeReturn(void);	// �T�C�Y�߂�

	// ���U���g�ւ̌p��
	static int GetFallNum(void) { return m_nFallResult; }

private:
	CNumber *m_apNumber[FALL_DIGIT_NUM];	// �i���o�[�N���X�|�C���^
	int m_nFall;							// �������l
	static int m_nFallResult;				// ���U���g�ֈ����p���l
};
#endif