//=============================================================================
//
// ���U���g�̗����J�E���g�`�揈�� [result_fallcount.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_FALLCOUNT_H_
#define _RESULT_FALLCOUNT_H_

#include "main.h"
#include "scene.h"
#include "result.h"
#include "ranking.h"
#include "score.h"

// �}�N����`
#define RESULT_FC_POS	(D3DXVECTOR3(440.0f, 600.0f, 0.0f))	// �ʏ�J�ڎ��̔z�u
#define RESULT_FC_SIZE	(D3DXVECTOR2(30.0f,45.0f))			// �ꌅ���̃T�C�Y

// �O���錾
class CFallCount;	// �����J�E���g�N���X

//==============================================================================
// ���U���g�̗����J�E���g�`��N���X
//==============================================================================
class CResultFallCount : public CResult
{
public:
	CResultFallCount(int nPriority = PRIORITY_UI);
	~CResultFallCount();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResultFallCount *Create();

	//static int GetScore(void) { return m_nScore; }
	//static int GetShuffleCnt(void) { return m_nShuffleCnt; }
	//static void SetShuffleCnt(int nSet) { m_nShuffleCnt = nSet; }
	//static bool GetEnd(void) { return m_bCntEventEnd; }

private:
	CFallCount *m_pFallCount;	// �����J�E���g�N���X
	int m_nFall;				// ���ʗ����J�E���g

	//D3DXVECTOR3 m_pos;			// �ʒu
	//static int m_nShuffleCnt;	// �X�R�A�\���V���b�t���J�E���g
	//static bool m_bCntEventEnd;	// �J�E���g���o�̏I��
};
#endif