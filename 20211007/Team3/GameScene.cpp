//=============================================================================
//
// �Q�[����� [game.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Gamescene.h"
#include "Input.h"
#include "Manager.h"
#include "ObjectManager.h"
#include "Collision.h"
#include "Player.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CObjectManager *CGameScene::m_pObjectManager = NULL;
CCollision *CGameScene::m_pCollision = NULL;
CPlayer *CGameScene::m_pPlayer = NULL;

//*****************************************************************************
// �Q�[����ʃN���X ( �p����: �I�u�W�F�N�g�N���X [scene] )
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameScene::CGameScene()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameScene::~CGameScene()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CGameScene::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// ���f���Ǘ��N���X����
	m_pObjectManager = new CObjectManager;
	if (FAILED(m_pObjectManager->Init())) {
		return E_FAIL;
	}

	// �����蔻��N���X����
	m_pCollision = new CCollision;
	if (FAILED(m_pCollision->Init())) {
		return E_FAIL;
	}

	// ���|��
	m_pScene3D = CScene3D::Create(VECTOR3_ZERO, VECTOR3_ZERO, D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), "TexTest01");
	m_pScene3D->SetTextureUV(
		D3DXVECTOR2(0.0f, 10.0f),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(10.0f, 10.0f),
		D3DXVECTOR2(10.0f, 0.0f));

	// �e�X�g�v���C���[
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0, 10, 0), VECTOR3_ZERO);
	
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CGameScene::Uninit(void)
{
	m_pPlayer = NULL;

	// �����蔻��N���X�j��
	m_pCollision->Uninit();
	delete m_pCollision;
	m_pCollision = NULL;

	// ����Ǘ��N���X�j��
	m_pObjectManager->Uninit();
	delete m_pObjectManager;
	m_pObjectManager = NULL;

	// ���̃I�u�W�F�N�g�̊J��
	this->Release();
}

//=============================================================================
// �X�V
//=============================================================================
void CGameScene::Update(void)
{
	// ����Ǘ��N���X�X�V
	m_pObjectManager->Update();

	// �����蔻��X�V
	m_pCollision->Update();

	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();
	if (pKeyboard->GetTrigger(DIK_B))
	{

	}
}

//=============================================================================
// �`��
//=============================================================================
void CGameScene::Draw(void)
{

}
