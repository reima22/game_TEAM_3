//=============================================================================
//
// �`���[�g���A���y�[�W�`�揈�� [tutorial_page.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TUTORIAL_PAGE_H_
#define _TUTORIAL_PAGE_H_

#include "main.h"
#include "scene.h"

//==============================================================================
// �`���[�g���A���y�[�W�N���X
//==============================================================================
class CTutorialPage : public CScene2D
{
public:
	typedef enum
	{
		TUTORIAL_PAGE_0 = 0,
		TUTORIAL_PAGE_1,
		TUTORIAL_PAGE_2,
		TUTORIAL_PAGE_MAX
	}TUTORIAL_PAGE;

	CTutorialPage(int nPriority = PRIORITY_BG);
	~CTutorialPage();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTutorialPage *Create(D3DXVECTOR3 pos);

	int GetPageCnt(void) { return m_nPageCnt; }

private:
	CScene2D *m_pScene2D[TUTORIAL_PAGE_MAX];		// �|���S���N���X�|�C���^
	int m_nPageCnt;									// �y�[�W�̃J�E���g
	static D3DXCOLOR m_col[TUTORIAL_PAGE_MAX];		// �F
};
#endif
