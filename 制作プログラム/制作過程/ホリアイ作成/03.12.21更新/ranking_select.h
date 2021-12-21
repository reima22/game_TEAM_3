//=============================================================================
//
// �|�[�Y�I�������� [ranking_select.h]
// Author : Tatasuki Matsuda
//
//============================================================================= 
#ifndef _RANKING_SELECT_H_
#define _RANKING_SELECT_H_

#include "main.h"
#include "ranking.h"

//==============================================================================
// �����L���O�I�����N���X
//==============================================================================
class CRankingSelect : public CRanking
{
public:
	// �����L���O���̑I����
	typedef enum
	{
		RANKING_RETRY = 0,	// ���g���C
		RANKING_STAGE,		// �X�e�[�W�Z���N�g
		RANKING_QUIT,		// �I��
		RANKING_MAX
	}RANKING;

	CRankingSelect(int nPriority = CScene::PRIORITY_UI);
	~CRankingSelect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRankingSelect *Create(void);
	static void SetRanking(RANKING ranking) { m_ranking = ranking; }
	void SetMode(void);

private:
	static CScene2D *m_apScene2D[RANKING_MAX];	// Scene2D�N���X
	static RANKING m_ranking;					// �I�𒆂̃J�[�\��
	static D3DXCOLOR m_col;						// �I�𒆂̃J�[�\���F
	bool m_bAlphaDown;							// �I�𒆃J�[�\���_�ŗp����
	bool m_bOK;									// �I������p����
	bool m_bSelect;								// ���݂̑I�𔻒�
	int m_nCntTime;								// �_�ŃJ�E���g����
};
#endif
