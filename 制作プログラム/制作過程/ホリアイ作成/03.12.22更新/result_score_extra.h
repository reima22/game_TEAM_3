//=============================================================================
//
// �����U���g�X�R�A�`�揈�� [result_score_extra.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_SCORE_EXTRA_H_
#define _RESULT_SCORE_EXTRA_H_

#include "main.h"
#include "scene.h"
#include "result.h"
#include "ranking.h"
#include "score.h"
#include "result_score.h"

// �}�N����`
#define EXSCORE_TIMER_POS		(D3DXVECTOR3(580.0f, 450.0f, 0.0f))	// �^�C�}�[�v�Z����
#define EXSCORE_TIMERCALCU_POS	(D3DXVECTOR3(850.0f, 450.0f, 0.0f))	// �^�C�}�[�v�Z���ʐ���

#define EXSCORE_COUNT_POS		(D3DXVECTOR3(580.0f, 550.0f, 0.0f))	// �J�E���g�v�Z����
#define EXSCORE_COUNTCALCU_POS	(D3DXVECTOR3(850.0f, 550.0f, 0.0f))	// �J�E���g�v�Z���ʐ���

#define EXSCORE_BONUS_POS		(D3DXVECTOR3(580.0f, 650.0f, 0.0f))	// �J�E���g�v�Z����	
#define EXSCORE_BONUSCALCU_POS	(D3DXVECTOR3(850.0f, 650.0f, 0.0f))	// �J�E���g�v�Z���ʐ���

#define EXSCORE_SIZE			(D3DXVECTOR2(20.0f, 30.0f))			// ���l�ꌅ�̃T�C�Y
#define EXSCORE_DIGIT			(4)									// ����
#define EXSCORE_TIMER			(1000)								// �^�C�}�[�v�Z����l
#define EXSCORE_COUNT			(1000)								// �J�E���g�v�Z����l

#define EXSCORE_CALCU_SIZE		(D3DXVECTOR2(25.0f, 40.0f))			// �v�Z���ʐ��l�ꌅ�̃T�C�Y
#define EXSCORE_CALCU_DIGIT		(8)									// �v�Z���ʌ���

//==============================================================================
// �����U���g�X�R�A�`��N���X
//==============================================================================
class CResultScoreEx : public CResultScore
{
public:
	CResultScoreEx(int nPriority = PRIORITY_UI);
	~CResultScoreEx();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nDigit, int nScore);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResultScoreEx *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nDigit, int nScore);

	int GetScoreEx(void) { return m_nScoreEx; }
	void SetScoreEx(int nScore);

	// �F�̐ݒ�
	void SetCol(D3DXCOLOR col);

	// ���l�̃V���b�t��
	void ShffleNum(int nType);

private:
	CNumber **m_pNumber;	// �����N���X
	int m_nDigit;			// ����
	int m_nScoreEx;			// �X�R�A�l
	int m_nShfflCnt;		// �V���b�t���J�E���g
};
#endif
