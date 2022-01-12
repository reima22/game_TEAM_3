//=============================================================================
//
// ���U���g�X�R�A�`�揈�� [result_score.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_SCORE_H_
#define _RESULT_SCORE_H_

#include "main.h"
#include "scene.h"
#include "result.h"
#include "ranking.h"
#include "score.h"

// �}�N����`
#define RESULT_SCORE_POS	(D3DXVECTOR3(440.0f, 260.0f, 0.0f))	// �ʏ�J�ڎ��̔z�u
#define RESULT_SCORE_SIZE	(D3DXVECTOR2(30.0f, 45.0f))
//#define RESULT_SHUFFLE_NUM	(4)									// �V���b�t�����鐔�l�̐�

#define RESULT_SHUFFLE_START	(30)	// �V���b�t���J�n		
#define RESULT_SHUFFLE	(150)			// ���l�V���b�t�������������l
#define RESULT_SHUFFLE_END	(330)		

//==============================================================================
// ���U���g�X�R�A�`��N���X
//==============================================================================
class CResultScore : public CResult
{
public:
	// �X�R�A�̎��
	typedef enum 
	{
		SCORETYPE_TIMER = 0,	// �^�C�}�[
		SCORETYPE_BONUS,		// �{�[�i�X
		SCORETYPE_FALL,			// ������
		SCORETYPE_MAIN,			// ���C���X�R�A
		SCORETYPE_MAX
	}SCORETYPE;

	CResultScore(int nPriority = PRIORITY_UI);
	~CResultScore();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResultScore *Create(D3DXVECTOR3 pos);
	static int GetScore(void) { return m_nScore; }

	static int GetShuffleCnt(void) { return m_nShuffleCnt; }
	static void SetShuffleCnt(int nSet) { m_nShuffleCnt = nSet; }

	static bool GetEnd(int nIdx) { return m_bCntEventEnd[nIdx]; }

private:
	CScore *m_pScore;								// �|���S���N���X�|�C���^
	static int m_nScore;							// ���ʃX�R�A
	D3DXVECTOR3 m_pos;								// �ʒu
	static int m_nShuffleCnt;						// �X�R�A�\���V���b�t���J�E���g
	static bool m_bCntEventEnd[SCORETYPE_MAX];		// �J�E���g���o�̏I��
	int m_nShaffleIdx;								// �V���b�t������X�R�A�̃C���f�b�N�X
};
#endif