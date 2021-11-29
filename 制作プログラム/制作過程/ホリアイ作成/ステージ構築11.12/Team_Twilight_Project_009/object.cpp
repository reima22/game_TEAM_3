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

	// �I�u�W�F�N�g�^�C�v
	SetObjType(OBJTYPE_OBJECT);

	// �ǂݎ��f�[�^�|�C���^
	CTextDataObject *pDataObject = CTextData::GetDataObject();

	// �f�[�^�̎擾
	m_pos = pDataObject->GetPosition(m_nIdx);
	m_rot = pDataObject->GetRotation(m_nIdx);
	m_nType = pDataObject->GetTypeObject(m_nIdx);
	m_shadowSize = pDataObject->GetShadowSize(m_nIdx);
	m_bSavePoint = pDataObject->GetSavePoint(m_nIdx);
	m_bStartPoint = pDataObject->GetStartPoint(m_nIdx);
	m_bGoalPoint = pDataObject->GetGoalPoint(m_nIdx);

	m_pFileName = pDataObject->GetFileName(m_nType);

	// ���f���̐���
	m_pModel = CModel::Create(m_pFileName, m_pos, m_rot);

	// �e�̐���
	if (m_shadowSize == VECTOR2_NULL)
	{
		m_pShadow = CShadow::Create(m_shadowSize);
	}
	else
	{
		m_pShadow = NULL;
	}

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
	// �e�̒Ǐ]
	if (m_pShadow != NULL)
	{
		m_pShadow->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z));
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
//CObject *CObject::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int nType, D3DXVECTOR2 shadowSize, bool bSavePoint, bool bGoalPoint)
//{
//	// ���[�J���ϐ��錾
//	CObject *pObject;
//	pObject = new CObject;	// �C���X�^���X
//
//	// ������
//	if (pObject != NULL)
//	{
//		// ���̐ݒ�
//		pObject->SetPosition(pos);
//		pObject->SetRotation(rot);
//		pObject->SetType(nType);
//		pObject->SetShadowSize(shadowSize);
//		pObject->SetSavePoint(bSavePoint);
//		pObject->SetGoalPoint(bGoalPoint);
//
//		pObject->Init();
//	}
//
//	return pObject;
//}

CObject *CObject::Create(int nIdx)
{
	// ���[�J���ϐ��錾
	CObject *pObject;
	pObject = new CObject;	// �C���X�^���X

							// ������
	if (pObject != NULL)
	{
		// ���̐ݒ�
		pObject->SetIdx(nIdx);

		pObject->Init();
	}

	return pObject;
}