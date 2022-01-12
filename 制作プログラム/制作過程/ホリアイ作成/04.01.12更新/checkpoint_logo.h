//=============================================================================
//
// �`�F�b�N�|�C���g���S�`�揈�� [checkpoint_logo.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _CHECKPOINT_LOGO_H_
#define _CHECKPOINT_LOGO_H_

#include "main.h"
#include "scene2D.h"

// �}�N����`
#define CHECK_SIZE	(D3DXVECTOR2(400.0f, 80.0f))
#define CHECK_POS	(D3DXVECTOR3(SCREEN_WIDTH + CHECK_SIZE.x, 360.0f, 0.0f))

//==============================================================================
// �`�F�b�N�|�C���g�N���X
//==============================================================================
class CCheckpointLogo : public CScene2D
{
public:
	// �ړ����
	typedef enum
	{
		LOGOMOVE_NONE = 0,	// �������
		LOGOMOVE_START,		// �ړ��J�n
		LOGOMOVE_STOP,		// �ꎞ��~
		LOGOMOVE_RESTART,	// �ړ��ĊJ
		LOGOMOVE_END,		// �I��
	}LOGOMOVE;

	CCheckpointLogo(int nPriority = PRIORITY_UI);
	~CCheckpointLogo();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CCheckpointLogo *Create(void);

	void MoveTypeNext(void) { if(m_logoMove == LOGOMOVE_NONE)m_logoMove = (LOGOMOVE)(m_logoMove + 1); }
	void MoveLogo(void);

private:
	CScene2D *m_pScene2D;	// 2D�|���S���N���X
	D3DXVECTOR3 m_pos;		// �ʒu
	LOGOMOVE m_logoMove;	// �ړ����
	int m_nCntStop;			// ��~�ԃJ�E���g
};

#endif