//=============================================================================
//
// �^�C�g�������j���O�}���`�揈�� [title_ruuningman.h]
// Author : Tatasuki Matsuda
//
//============================================================================= 
#ifndef _TITLE_RUNNINGMAN_H_
#define _TITLE_RUNNINGMAN_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

// �}�N����`
#define T_RUNNINGMAN_POS	(D3DXVECTOR3(0.0f, 350.0f, 0))									// �����j���O�}���̈ʒu
#define T_RUNNINGMAN_SIZE	(D3DXVECTOR2(260.0f, 320.0f))									// �����j���O�}���̃T�C�Y
#define T_RUNNINGMAN_SETPOS	(D3DXVECTOR3(SCREEN_WIDTH+T_RUNNINGMAN_SIZE.x, 300.0f, 0.0f))	// �����j���O�}���̍ŏI���W

#define ANIMATION_PATTERN		(8)									//	�A�j���[�V�����p�^�[����
#define ANIMATION_COUNT			(6)									//	�A�j���[�V�����J�E���g

#define MOVE_RUNNINGMAN_Y		(0.0f)								//	�^�C�g���@	Y���̈ړ��l
#define MOVE_RUNNINGMAN_X		(10.0f)								//	�^�C�g���@	X���̈ړ��l
#define MOVE_SPEED				(15.0f)								//	���x�l

//==============================================================================
// �����j���O�}���N���X
//==============================================================================
class CTitleRunningMan : public CScene2D
{
public:
	CTitleRunningMan(int nPriority = PRIORITY_UI);
	~CTitleRunningMan();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitleRunningMan *Create(D3DXVECTOR3 pos);

	static bool GetLogoState(void) { return m_bRunningManMoveEnd; }

private:
	CScene2D *m_pScene2D;				// 2D�|���S���N���X�|�C���^
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_move;					// �ړ���
	D3DXCOLOR m_col;					// �F

	float m_fSpead;						// ���x

	bool m_bEnter;						// �G���^�[�����������ǂ���
	bool m_bNextScene;					// ���̃V�[���Ɉړ����邩�ǂ���
	bool m_bJump;						// �W�����v����
	static bool m_bRunningManMoveEnd;	// �����j���O�}���ړ��̏I�� 

	int m_nPatternAnimX;				// �A�j���[�V����X��No.
	int m_nPatternAnimY;				// �A�j���[�V����Y��No.
	int m_nCounterAnim;					// �A�j���[�V�����J�E���^�[
	int m_nTimer;						// �^�C�}�[
};
#endif

