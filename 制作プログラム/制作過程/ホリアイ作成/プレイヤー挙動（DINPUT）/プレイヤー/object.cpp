//==============================================================================
//
// 3D�I�u�W�F�N�g�Ǘ��kobject.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "model.h"
#include "input.h"
#include "gamepad.h"
#include "shadow.h"
#include "textdata_object.h"
#include "player.h"
#include "game.h"
#include "collision.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CObject::CObject()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CObject::~CObject()
{

}

//==============================================================================
// 3D�I�u�W�F�N�g�̏���������
//==============================================================================
HRESULT CObject::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �ǂݎ��f�[�^�|�C���^
	CTextDataObject *pDataObject = CTextData::GetDataObject();

	// �t�@�C�����̎擾
	m_pFileName = pDataObject->GetFileName(m_nType);

	// ���f���̐���
	m_pModel = CModel::Create(m_pFileName, m_pos, m_rot);

	// �e�̐���
	m_pShadow = CShadow::Create(m_shadowSize);

	return S_OK;
}

//==============================================================================
// 3D�I�u�W�F�N�g�̏I������
//==============================================================================
void CObject::Uninit(void)
{
	// ���f�����̔j��
	if (m_pModel != NULL)
	{
		delete m_pModel;
		m_pModel = NULL;
	}
}

//==============================================================================
// 3D�I�u�W�F�N�g�̍X�V����
//==============================================================================
void CObject::Update(void)
{	
	// �����蔻��
	CCollision *pCollision;
	pCollision = CManager::GetCollision();
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pCollision != NULL && pPlayer != NULL)
	{
		pCollision->Collision3D(pPlayer, m_pModel);
	}

	// �e�̒Ǐ]
	if (m_pShadow != NULL)
	{
		m_pShadow->SetPosition(D3DXVECTOR3(m_pos.x, 0.5f, m_pos.z));
	}
}

//==============================================================================
// 3D�I�u�W�F�N�g�̕`�揈��
//==============================================================================
void CObject::Draw(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;										// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;												// ���݂̃}�e���A���ۑ��p

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//// �����̔��f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//// �ʒu�𔽉f
	//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// ���f���̕`��
	if (m_pModel != NULL)
	{
		m_pModel->Draw();
	}
}

//==============================================================================
// ��������
//==============================================================================
CObject *CObject::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int nType, D3DXVECTOR2 shadowSize)
{
	// ���[�J���ϐ��錾
	CObject *pObject;
	pObject = new CObject;	// �C���X�^���X

	// ������
	if (pObject != NULL)
	{
		// ���̐ݒ�
		pObject->SetPosition(pos);
		pObject->SetRotation(rot);
		pObject->SetType(nType);
		pObject->SetShadowSize(shadowSize);

		pObject->Init();
	}

	return pObject;
}