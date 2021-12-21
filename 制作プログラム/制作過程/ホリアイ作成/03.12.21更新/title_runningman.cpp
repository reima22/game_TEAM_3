//==============================================================================
//
// �^�C�g�����S�`�揈���ktitle_runningman.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "title_logo.h"
#include "title_runningman.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"

// �ÓI�����o�ϐ��錾
bool CTitleRunningMan::m_bRunningManMoveEnd;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTitleRunningMan::CTitleRunningMan(int nPriority) : CScene2D(nPriority)
{
	// �|���S���̏�����
	m_pScene2D = NULL;

	m_bRunningManMoveEnd = false;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTitleRunningMan::~CTitleRunningMan()
{
}

//==============================================================================
// �����j���O�}���̏���������
//==============================================================================
HRESULT CTitleRunningMan::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;

	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create();
		m_pScene2D->SetPosition(pos);
		m_pScene2D->SetSize(T_RUNNINGMAN_SIZE);
		m_pScene2D->SetTex(1, 1, 0, 0, 0, 0);
		m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pScene2D->BindTexture("TITLE_RUNNINGMAN");
	}

	//�A�j���[�V�����p�J�E���g
	m_nCounterAnim = 0;
	m_nPatternAnimX = 0;
	m_nPatternAnimY = 0;

	return S_OK;
}

//==============================================================================
// �����j���O�}���̏I������
//==============================================================================
void CTitleRunningMan::Uninit(void)
{
	if (m_pScene2D != NULL)
	{// NULL�`�F�b�N��ɔj��
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �����j���O�}���̍X�V����
//==============================================================================
void CTitleRunningMan::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �F
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�A�j���[�V�����p�J�E���g
	m_nCounterAnim++;

	//�A�j���[�V����
	if (m_nCounterAnim % ANIMATION_COUNT == 0)
	{
		//�A�j���[�V�����p�p�^�[����
		m_nPatternAnimX++;
	}

	//�A�j���[�V�����p�e�N�X�`�����W
	m_pScene2D->SetTex(8, 1, m_nPatternAnimX, 0, 0, 0);

	if (m_pos.x < T_RUNNINGMAN_SETPOS.x)
	{// �ʒu���l��荶�������ꍇ

		// �ړ��l
		m_move.x = MOVE_RUNNINGMAN_X;
	}
	else
	{
		//�������珉���ʒu�ɖ߂�
		m_pos.x = 0.0f - T_RUNNINGMAN_SIZE.x;
	}

	// �ړ��l���ʒu���W�ɑ���
	m_pos += m_move;

	// �ʒu
	m_pScene2D->SetPosition(m_pos);
}

//==============================================================================
// �����j���O�}���̕`�揈��
//==============================================================================
void CTitleRunningMan::Draw(void)
{

}

//==============================================================================
// �����j���O�}���̐�������
//==============================================================================
CTitleRunningMan *CTitleRunningMan::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CTitleRunningMan *pTitleRunningman;
	pTitleRunningman = new CTitleRunningMan;

	// ������
	pTitleRunningman->Init(pos);

	return pTitleRunningman;
}