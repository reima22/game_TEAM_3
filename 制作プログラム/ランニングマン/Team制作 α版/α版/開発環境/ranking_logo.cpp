//==============================================================================
//
// �����L���O���S�̕`�揈���kranking_logo.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "ranking.h"
#include "ranking_logo.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CRankingLogo::CRankingLogo(int nPriority) : CRanking(nPriority)
{
	// �|���S���̏�����
	//m_pPolygon = NULL;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CRankingLogo::~CRankingLogo()
{
}

//==============================================================================
// �����L���O���S�̏���������
//==============================================================================
HRESULT CRankingLogo::Init(void)
{
	//// �|���S��������
	//if (m_pPolygon == NULL)
	//{
	//	m_pPolygon = CPolygon::Create(D3DXVECTOR3(pos.x, pos.y, 0.0f),
	//		RANK_LOGO_SIZEX, RANK_LOGO_SIZEY,
	//		9);
	//	// �e�N�X�`���ݒ�
	//	m_pPolygon->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	//}
	//CScene2D::Init();
	//CScene2D::SetPosition(pos);
	//CScene2D::SetSize(RANK_LOGO_SIZE);
	//CScene2D::SetCol(COLOR_DEFAULT);
	//CScene2D::SetTex(1, 1, 0, 0, 0.0f, 0.0f);

	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create();
		m_pScene2D->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	}

	return S_OK;
}

//==============================================================================
// �����L���O���S�̏I������
//==============================================================================
void CRankingLogo::Uninit(void)
{
	//if (m_pPolygon != NULL)
	//{// NULL�`�F�b�N��ɔj��
	//	m_pPolygon->Uninit();
	//	m_pPolygon = NULL;
	//}

	//CScene2D::Uninit();

	// �|���S���̔j��
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �����L���O���S�̍X�V����
//==============================================================================
void CRankingLogo::Update(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Update();
	}
}

//==============================================================================
// �����L���O���S�̕`�揈��
//==============================================================================
void CRankingLogo::Draw(void)
{
	//CScene2D::Draw();
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Draw();
	}
}

//==============================================================================
// �����L���O���S�̐�������
//==============================================================================
CRankingLogo *CRankingLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, char *pTypeCheck)
{
	// �C���X�^���X����
	CRankingLogo *pRankingLogo;
	pRankingLogo = new CRankingLogo;

	// ������
	if (pRankingLogo != NULL)
	{
		pRankingLogo->Init();
		pRankingLogo->m_pScene2D->SetPosition(pos);
		pRankingLogo->m_pScene2D->SetSize(size);
		pRankingLogo->m_pScene2D->BindTexture(pTypeCheck);
	}

	return pRankingLogo;
}