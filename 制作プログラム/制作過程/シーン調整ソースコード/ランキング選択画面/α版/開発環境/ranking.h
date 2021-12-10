
//=============================================================================
//
// �����L���O���[�h���� [ranking.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "scene.h"
#include "mode.h"

// �}�N����`
#define RANK_NUM		(5)		// ���ʂ̐�
#define AUTO_FADE_CNT_T	(300)	// �^�C�g���ւ̎����J�ڃJ�E���g

// �O���錾
class CScore;

//==============================================================================
// �����L���O���[�h�N���X
//==============================================================================
class CRanking : public CMode
{
public:
	CRanking(int nPriority = PRIORITY_DEFAULT);
	~CRanking();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRanking *Create(void);

private:
	bool m_bFromTitle;					// �^�C�g������̑J�ڔ���
	int m_nAutoFadeCnt;					// �^�C�g���֖߂鎩���J�ڃJ�E���g
};

#endif
