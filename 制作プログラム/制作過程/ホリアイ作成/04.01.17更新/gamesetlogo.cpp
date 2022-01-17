//==============================================================================
//
// �Q�[�����ʃ��S�����kgamesetlogo.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "texture.h"
#include "gamesetlogo.h"
#include "select.h"
#include "game.h"
#include "player.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CGamesetLogo::CGamesetLogo(int nPriority) : CScene(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CGamesetLogo::~CGamesetLogo()
{

}

//==============================================================================
// �Q�[�����ʃ��S�̏���������
//==============================================================================
HRESULT CGamesetLogo::Init(void)
{
	// �v���C���[���
	CPlayer *pPlayer = CGame::GetPlayer();

	if (m_pScene2D == NULL)
	{
		// 2D�|���S���𐶐�
		m_pScene2D = CScene2D::Create();

		// �ʒu�ݒ�
		m_pScene2D->SetPosition(LOGO_POS);

		// �T�C�Y�ݒ�
		m_pScene2D->SetSize(LOGO_SIZE);

		m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		m_pScene2D->SetTex(1, 1, 0, 0, 0, 0);

		// �e�N�X�`���ݒ�
		if (pPlayer->GetGameClear() == true)
		{
			m_pScene2D->BindTexture("G_RESULT_CLEAR");
		}
		else
		{
			m_pScene2D->BindTexture("G_RESULT_GAMEOVER");
		}
	}

	return S_OK;
}

//==============================================================================
// �Q�[�����ʃ��S�̏I������
//==============================================================================
void CGamesetLogo::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}
}

//==============================================================================
// �Q�[�����ʃ��S�̍X�V����
//==============================================================================
void CGamesetLogo::Update(void)
{

}

//==============================================================================
// �Q�[�����ʃ��S�̕`�揈��
//==============================================================================
void CGamesetLogo::Draw(void)
{

}

//==============================================================================
// �Q�[�����ʃ��S�̐�������
//==============================================================================
CGamesetLogo *CGamesetLogo::Create(void)
{
	// �C���X�^���X����
	CGamesetLogo *pGamesetLogo;
	pGamesetLogo = new CGamesetLogo;

	// CNumber�̏�����
	if (pGamesetLogo != NULL)
	{
		pGamesetLogo->Init();
	}

	return pGamesetLogo;
}