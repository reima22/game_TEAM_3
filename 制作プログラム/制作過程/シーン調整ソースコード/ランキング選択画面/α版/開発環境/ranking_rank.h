//=============================================================================
//
// �����L���O���ʕ`�揈�� [ranking_rank.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RANKING_RANK_H_
#define _RANKING_RANK_H_

#include "main.h"
#include "scene.h"
#include "ranking.h"

// �}�N����`
#define RANK_POS				(D3DXVECTOR3(440.0f, 170.0f, 0.0f))	// �ʏ�J�ڎ��̔z�u
#define RANK_POS_T				(D3DXVECTOR3(440.0f, 220.0f, 0.0f))	// �����J�ڎ��̔z�u
#define RANK_SIZE				(D3DXVECTOR2(50.0f, 30.0f))			// �T�C�Y

#define RESULT_SCORE_LOGO_POS	(D3DXVECTOR3(440.0f, 640.0f,0.0f))	// ���ʃX�R�A�̃��S 

// �O���錾
class CScene2D;

//==============================================================================
// �����L���O���ʕ`��N���X
//==============================================================================
class CRankingRank : public CRanking
{
public:
	CRankingRank(int nPriority = PRIORITY_UI);
	~CRankingRank();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �����L���O���ʂ̐���
	static CRankingRank *Create(void);
	
	// ���ʕ\�L�̐ݒ�
	void SetRank(void);

private:
	CScene2D *m_apScene2D[RANK_NUM];	// ���ʕ\�L
	CScene2D *m_pYourScore;				// �u����̃X�R�A�v���S

	bool m_bFromTitle;					// �����J�ڔ���
	static int m_aRank[RANK_NUM];		// ����
	int m_aScore[RANK_NUM];				// �����L���O�X�R�A
	D3DXVECTOR3 m_posBase;				// 1�Ԗڂ̊�ƂȂ�ʒu
};
#endif