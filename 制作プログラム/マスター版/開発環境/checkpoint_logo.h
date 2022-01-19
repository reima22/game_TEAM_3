//=============================================================================
//
// �`�F�b�N�|�C���g���S�`�揈�� [checkpoint_logo.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _CHECKPOINT_LOGO_H_
#define _CHECKPOINT_LOGO_H_

#include "main.h"
#include "scene.h"

// �}�N����`
#define CHECK_POS	(D3DXVECTOR3(SCREEN_WIDTH + CHECK_SIZE.x, 360.0f, 0.0f))	// �ʒu
#define CHECK_SIZE	(D3DXVECTOR2(400.0f, 80.0f))								// �T�C�Y
#define CHECK_MOVE	(20.0f)														// �ړ���

// �O���錾
class CScene2D;

//==============================================================================
// �`�F�b�N�|�C���g�N���X
//==============================================================================
class CCheckpointLogo : public CScene
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

	// �ړ����@�̐ݒ�
	void MoveTypeNext(void) { if(m_logoMove == LOGOMOVE_NONE)m_logoMove = (LOGOMOVE)(m_logoMove + 1); }
	
	// ���S�̈ړ�
	void MoveLogo(void);

private:
	CScene2D *m_pScene2D;	// 2D�|���S���N���X
	LOGOMOVE m_logoMove;	// �ړ����
	int m_nCntStop;			// ��~�ԃJ�E���g
};

#endif