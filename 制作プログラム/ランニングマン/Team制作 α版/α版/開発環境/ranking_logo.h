//=============================================================================
//
// �����L���O���S�`�揈�� [ranking_logo.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RANKING_LOGO_H_
#define _RANKING_LOGO_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define RANK_LOGO_POS	(D3DXVECTOR3(SCREEN_WIDTH / 2, 70.0f, 0.0f))	// �ʏ�J�ڎ��̔z�u
#define RANK_LOGO_POS_T	(D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f))	// �����J�ڎ��̔z�u
#define RANK_LOGO_SIZE	(D3DXVECTOR2(240.0f, 40.0f))

//==============================================================================
// �����L���O���S�N���X
//==============================================================================
class CRankingLogo : public CRanking
{
public:
	CRankingLogo(int nPriority = PRIORITY_UI);
	~CRankingLogo();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRankingLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, char *pTypeCheck);

private:
	CScene2D *m_pScene2D;
};
#endif
