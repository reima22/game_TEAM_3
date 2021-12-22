//=============================================================================
//
// �|�[�Y�I�������� [pause_select.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _PAUSE_SELECT_H_
#define _PAUSE_SELECT_H_

#include "main.h"
#include "pause.h"

//==============================================================================
// �|�[�Y�I�����N���X
//==============================================================================
class CPauseSelect : public CScene
{
public:
	// �|�[�Y���̑I����
	typedef enum
	{
		PAUSE_CONTINUE = 0,	// �R���e�j���[
		PAUSE_RETRY,		// ���g���C
		PAUSE_QUIT,			// �I��
		PAUSE_MAX
	}PAUSE;

	CPauseSelect(int nPriority = CScene::PRIORITY_PAUSE);
	~CPauseSelect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPauseSelect *Create(void);
	static void SetPause(PAUSE pause) { m_pause = pause; }
	void SetMode(void);

private:
	static CScene2D *m_apScene2D[PAUSE_MAX];	// Scene2D�N���X
	static PAUSE m_pause;						// �I�𒆂̃J�[�\��
	static D3DXCOLOR m_col;						// �I�𒆂̃J�[�\���F
	bool m_bAlphaDown;							// �I�𒆃J�[�\���_�ŗp����
};
#endif
