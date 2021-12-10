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
#include "textdata.h"
#include "textdata_object.h"
#include "player.h"
#include "game.h"
#include "collision.h"
#include "select.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CObject::CObject()
{
	m_bDropOut = false;
	m_nDropCnt = 0;
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
	// ���e�I�u�W�F�N�g�̐ݒ�
	PhantomObject();

	// ���f���|�C���^
	if (m_pModel != NULL)
	{
		if (m_bDropOut == false)
		{
			if (m_moveType != MOVETYPE_NONE)
			{
				m_pModel->Update();

				// �ړ�����
				MoveObject();
			}
		}
		else
		{
			m_pModel->Update();

			if (m_nDropCnt < CNT_ONE_SECOND)
			{
				// �ړ�����
				MoveObject();
			}

			DropObject();
		}
	}

	// ��������
	m_pos += m_move;
	m_pModel->SetPosition(m_pos);
	m_pModel->SetMove(m_move);

	// �Q�[���I�[�o�[���A�S�Ă̗���
	if (CGame::GetOverPhase() != CGame::GAMEOVERPHASE_NONE && (m_objAttribute == OBJATTRIBUTE_SCAFFOLD || m_objAttribute == OBJATTRIBUTE_SAVE))
	{
		m_bDropOut = true;
	}

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

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// ���f���̕`��
	if (m_pModel != NULL)
	{
		m_pModel->Draw();
	}

	// �e�̒Ǐ]
	if (m_pShadow != NULL)
	{
		m_pShadow->Draw();
	}
}

//==============================================================================
// ��������
//==============================================================================
CObject *CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pFileName, D3DXVECTOR2 shadowSize, MOVETYPE moveType, float fMovePower, OBJATTRIBUTE objAttribute)
{
	// ���[�J���ϐ��錾
	CObject *pObject;
	pObject = new CObject;	// �C���X�^���X

	// ������
	if (pObject != NULL)
	{
		// ���̐ݒ�
		pObject->SetPosition(pos);				// �ʒu
		pObject->SetRotation(rot);				// �p�x
		pObject->SetFileName(pFileName);		// �ǂݍ��ރt�@�C����
		pObject->SetShadowSize(shadowSize);		// �e�̑傫��
		pObject->SetMoveType(moveType);			// �ړ��^�C�v
		pObject->SetMovePower(fMovePower);		// �ړ���
		pObject->SetObjAttribute(objAttribute);	// �I�u�W�F�N�g�̑���

		pObject->Init();
	}

	return pObject;
}

//==============================================================================
// 3D�I�u�W�F�N�g�̏���������(�e�L�X�g�f�[�^)
//==============================================================================
HRESULT CObject::InitFromData(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �I�u�W�F�N�g�^�C�v
	SetObjType(OBJTYPE_OBJECT);

	// �f�[�^�e�L�X�g�̎擾
	CStageSelect::STAGE_SELECT select = CStageSelect::GetSelectingStage();

	// �ǂݎ��f�[�^�|�C���^
	CTextDataObject *pDataObject = CTextData::GetDataObject(select);

	// �f�[�^�̎擾
	m_pos = pDataObject->GetPosition(m_nIdx);
	m_rot = pDataObject->GetRotation(m_nIdx);
	m_nType = pDataObject->GetTypeObject(m_nIdx);
	m_shadowSize = pDataObject->GetShadowSize(m_nIdx);
	m_moveType = pDataObject->GetMoveType(m_nIdx);
	m_fMovePower = pDataObject->GetMovePower(m_nIdx);
	m_pFileName = pDataObject->GetFileName(m_nType);
	m_objAttribute = pDataObject->GetObjAttribute(m_nIdx);

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
// �e�L�X�g�f�[�^���琶��
//==============================================================================
CObject *CObject::CreateFromData(int nIdx)
{
	// ���[�J���ϐ��錾
	CObject *pObject;
	pObject = new CObject;	// �C���X�^���X

	// ������
	if (pObject != NULL)
	{
		// ���̐ݒ�
		pObject->SetIdx(nIdx);

		pObject->InitFromData();
	}

	return pObject;
}

//==============================================================================
// �I�u�W�F�N�g�̈ړ�
//==============================================================================
void CObject::MoveObject(void)
{
	// �ړ��̎��
	if (m_moveType != MOVETYPE_NONE)
	{
		switch (m_moveType)
		{
		case MOVETYPE_SIDE:

			m_moveRot.y += 0.01f;

			if (m_moveRot.y > D3DX_PI)
			{
				m_moveRot.y -= PI_DEFAULT;
			}

			m_move = D3DXVECTOR3(cosf(m_moveRot.y) * m_fMovePower, 0.0f, 0.0f);

			break;

		case MOVETYPE_DEPTH:	// �O��ړ�
			m_moveRot.y += 0.01f;

			if (m_moveRot.y > D3DX_PI)
			{
				m_moveRot.y -= PI_DEFAULT;
			}

			m_move = D3DXVECTOR3(0.0f, 0.0f, cosf(m_moveRot.y) * m_fMovePower);

			break;

		case MOVETYPE_UPDOWN:	// �O��ړ�
			m_moveRot.y += 0.01f;

			if (m_moveRot.y > D3DX_PI)
			{
				m_moveRot.y -= PI_DEFAULT;
			}

			m_move = D3DXVECTOR3(0.0f, cosf(m_moveRot.y) * m_fMovePower, 0.0f);

			break;
		}
	}
}

//==============================================================================
// �I�u�W�F�N�g�̗���
//==============================================================================
void CObject::DropObject(void)
{
	// SE�̍Đ�
	if (m_nDropCnt <= 0)
	{
		m_pSound->Play(CSound::SOUND_LABEL_SE_EARTHQUAKE);
	}
	else if (m_nDropCnt == CNT_ONE_SECOND)
	{
		m_pSound->Play(CSound::SOUND_LABEL_SE_FALL_SCCAFORD);
	}

	// �J�E���g
	m_nDropCnt++;

	// ��������
	if (m_nDropCnt > 0 && m_nDropCnt < CNT_ONE_SECOND)
	{
		// �U��
		float fRandom = (float)(rand() % 628 - 314) / 100;

		if (m_moveType == MOVETYPE_NONE)
		{
			m_move.x = sinf(fRandom);
			m_move.z = cosf(fRandom);
		}
		else
		{
			m_move.x += sinf(fRandom);
			m_move.z += cosf(fRandom);
		}
	}
	else
	{
		// ����
		m_move.x = 0.0f;
		m_move.z = 0.0f;
		m_move.y -= 0.02f;
	}
}

//==============================================================================
// �I�u�W�F�N�g�̕���
//==============================================================================
void CObject::ResetObject(void)
{
	// �f�[�^�e�L�X�g�̎擾
	CStageSelect::STAGE_SELECT select = CStageSelect::GetSelectingStage();

	// �ǂݎ��f�[�^�|�C���^
	CTextDataObject *pDataObject = CTextData::GetDataObject(select);

	// �����������̂̕���
	if (m_bDropOut == true)
	{
		m_pos = pDataObject->GetPosition(m_nIdx);
		m_move = VECTOR3_NULL;
		m_pModel->SetPosition(m_pos);
		m_pModel->SetMove(m_move);
		m_nDropCnt = 0;
		m_bDropOut = false;
	}
}

//==============================================================================
// ���e�I�u�W�F�N�g�̐ݒ�
//==============================================================================
void CObject::PhantomObject(void)
{
	if (m_objAttribute == OBJATTRIBUTE_PHANTOM && m_pModel != NULL)
	{
		m_pModel->SetCol(D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.3f));
	}
}