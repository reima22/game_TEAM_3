//==============================================================================
//
// �v���C���[�Ǘ��kplayer.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "input.h"
#include "gamepad.h"
#include "textdata_player.h"
#include "textdata_object.h"
#include "camera.h"
#include "collision.h"
#include "game.h"
#include "object.h"
#include "Terrain.h"
#include "shadowS.h"
#include "motion.h"
#include "motion_player.h"
#include "fall_count.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CPlayer::CPlayer()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CPlayer::~CPlayer()
{

}

//==============================================================================
// �v���C���[�̏���������
//==============================================================================
HRESULT CPlayer::Init(void)
{
	// �e�L�X�g�f�[�^�̎擾
	CTextDataPlayer *pDataPlayer = CTextDataPlayer::GetDataPlayer();

	// �����蔻��̒l
	m_pos = pDataPlayer->GetPosition();
	m_rot = pDataPlayer->GetRotation();
	m_fRadius = pDataPlayer->GetRadius();
	m_fHeight = pDataPlayer->GetHeight();

	// �����ʒu�̃��X�|�[���n�_
	m_posSave = m_pos;

	// �ߋ��̈ʒu
	m_posOld = VECTOR3_NULL;

	// �I�u�W�F�N�g�^�C�v
	SetObjType(OBJTYPE_PLAYER);

	// ���[�V�������̐���
	m_pMotionPlayer = CMotionPlayer::Create();

	// �e�̐ݒ�
	m_pShadowS = CShadowS::Create(m_pos);

	return S_OK;
}

//==============================================================================
// �v���C���[�̏I������
//==============================================================================
void CPlayer::Uninit(void)
{
	// ���[�V�����̔j��
	if (m_pMotionPlayer != NULL)
	{
		m_pMotionPlayer->Uninit();
		m_pMotionPlayer = NULL;
	}
}

//==============================================================================
// �v���C���[�̍X�V����
//==============================================================================
void CPlayer::Update(void)
{
	// �ړ�����
	MovePlayer();

	// ���[�V�����̍X�V
	if (m_pMotionPlayer != NULL)
	{
		m_pMotionPlayer->Update(m_pMotionPlayer->GetMotion());
	}

	// �e�̒Ǐ]
	if (m_pShadowS != NULL)
	{
		m_pShadowS->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y + 5.0f, m_pos.z));
	}

	// �ʒu�̍X�V
	SetPosition(m_pos);
	SetRotation(m_rot);
}

//==============================================================================
// �v���C���[�̕`�揈��
//==============================================================================
void CPlayer::Draw(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;										// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;												// ���݂̃}�e���A���ۑ��p

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// ���f���̕`��
	if (m_pMotionPlayer != NULL)
	{
		m_pMotionPlayer->Draw();
	}
}

//==============================================================================
// ��������
//==============================================================================
CPlayer *CPlayer::Create(void)
{
	// ���[�J���ϐ��錾
	CPlayer *pPlayer;
	pPlayer = new CPlayer;	// �C���X�^���X

	// ������
	if (pPlayer != NULL)
	{
		pPlayer->Init();
	}

	return pPlayer;
}

//==============================================================================
// ��������
//==============================================================================
void CPlayer::MovePlayer(void)
{
	// �e�L�X�g�f�[�^�̎擾
	CTextDataPlayer *pDataPlayer = CTextDataPlayer::GetDataPlayer();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �J�����̎擾
	CCamera *pCamera = CManager::GetCamera();

	// �J�����̕���
	D3DXVECTOR3 rotCamera = pCamera->GetRotation();

	// ���b�V��
	CTerrain *pTerrain = CGame::GetTerrain();
	
	// �����J�E���g
	CFall *pFall;
	pFall = CGame::GetFall();

	// ���b�V���Ƃ̓����蔻��
	if (pTerrain != NULL)
	{
		if (pTerrain->FallCollider(this) == true)
		{
			// ���X�|�[���ʒu�ւ̑���
			m_pos = m_posSave;
			m_move = VECTOR3_NULL;
			m_nDashCnt = 0;

			// ���������Z
			pFall->GetFallCount()->AddFall(1);
		}
	}

	// ���I�u�W�F�N�g�Ƃ̓����蔻��
	CCollision *pCollision;
	pCollision = CManager::GetCollision(); // �����蔻��擾

	if (pCollision != NULL)
	{
		CTextDataObject *pDataObject;
		pDataObject = CTextData::GetDataObject();

		int nNumObject = pDataObject->GetNumObject();

		for (int nCntObject = 0; nCntObject < nNumObject; nCntObject++)
		{
			// �I�u�W�F�N�g�|�C���^
			CObject *pObject = CGame::GetPointObject(nCntObject);

			// ���f���|�C���^
			CModel *pModel = NULL;

			if (pObject != NULL)
			{
				pModel = pObject->GetModel();
			}

			// �ڐG���тɏ���Ă��锻��
			if (pModel != NULL)
			{
				if (pCollision->Collision3D(this, pModel) == true)
				{
					m_bLand = true;

					// ���Ԓn�_�̍X�V
					if (pObject->GetSavePoint() == true)
					{
						m_posSave = D3DXVECTOR3(pModel->GetPosition().x, m_posSave.y, pModel->GetPosition().z);
					}

					break;			// ����L����for���E�o
				}
			}
		}
	}

	// �ߋ��ʒu�̍X�V
	m_posOld = m_pos;

	// �d�͂̔���
	if (m_bLand == false)
	{
		m_move.y -= GRAVITY_SCALE;
	}
	else if (m_bLand == true)
	{// ���n���
		if (m_bJump == true)
		{// �W�����v���璅�n
			if (m_pMotionPlayer->GetMotion() == CMotionPlayer::MOTIONTYPE_JUMP || m_pMotionPlayer->GetMotion() == CMotionPlayer::MOTIONTYPE_RUN)
			{
				m_pMotionPlayer->SetMotion(CMotionPlayer::MOTIONTYPE_LANDING);
			}
		}

		m_bJump = false;
		m_move.y = 0.0f;
	}

	// �W�����v�F���n���Ă���
	if (keyboard->GetTrigger(CInput::KEYINFO_JUMP) == true ||
		gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		// ���n���Ă���Ƃ�
		if (m_bJump == false)
		{
			m_pMotionPlayer->SetMotion(CMotionPlayer::MOTIONTYPE_JUMP);		// �W�����v���[�V�����؂�ւ�
			m_move.y = 0.5f;												// �����W�����v�͂̐ݒ�
		}

		// ���n����̉���
		m_bLand = false;
	}
	if (keyboard->GetPress(CInput::KEYINFO_JUMP) == true ||
		gamepad->GetPress(CInput::KEYINFO_OK) == true)
	{
		// �؋���
		if (m_bJump == false && m_bLand == false)
		{
			if (m_nJumpCnt == 0)
			{
				m_move.y = 5.0f;
			}
			if (m_nJumpCnt < 9)
			{// ���E�l
				m_nJumpCnt++;
				m_move.y += 1.0f;
			}
			else
			{
				m_bJump = true;
			}
		}
	}
	if (keyboard->GetRelease(CInput::KEYINFO_JUMP) == true ||
		gamepad->GetRelease(CInput::KEYINFO_OK) == true)
	{
		m_nJumpCnt = 0;
		m_bJump = true;
	}

	// �ړ�
	m_pos += m_move;

	// �ړ�����	
	if (keyboard->GetPress(CInput::KEYINFO_WALK_UP) == true ||
		keyboard->GetPress(CInput::KEYINFO_WALK_DOWN) == true ||
		keyboard->GetPress(CInput::KEYINFO_WALK_LEFT) == true ||
		keyboard->GetPress(CInput::KEYINFO_WALK_RIGHT) == true ||
		gamepad->GetPress(CInput::KEYINFO_WALK_UP) == true ||
		gamepad->GetPress(CInput::KEYINFO_WALK_DOWN) == true ||
		gamepad->GetPress(CInput::KEYINFO_WALK_LEFT) == true ||
		gamepad->GetPress(CInput::KEYINFO_WALK_RIGHT) == true)
	{// ����
		if (keyboard->GetPress(CInput::KEYINFO_WALK_UP) == true ||
			gamepad->GetPress(CInput::KEYINFO_WALK_UP) == true)
		{// �����
			if (keyboard->GetPress(CInput::KEYINFO_WALK_LEFT) == true ||
				gamepad->GetPress(CInput::KEYINFO_WALK_LEFT) == true)
			{// �������
				m_move.x -= cosf(rotCamera.y + D3DX_PI / 4) * WALK_SPEED;
				m_move.z += sinf(rotCamera.y + D3DX_PI / 4) * WALK_SPEED;
				m_rotDest.y = rotCamera.y + (D3DX_PI * 3 / 4);
			}
			else if (keyboard->GetPress(CInput::KEYINFO_WALK_RIGHT) == true ||
				gamepad->GetPress(CInput::KEYINFO_WALK_RIGHT) == true)
			{// �E�����
				m_move.x += cosf(rotCamera.y - D3DX_PI / 4) * WALK_SPEED;
				m_move.z -= sinf(rotCamera.y - D3DX_PI / 4) * WALK_SPEED;
				m_rotDest.y = rotCamera.y - (D3DX_PI * 3 / 4);
			}
			else
			{// �����
				m_move.x += sinf(rotCamera.y) * WALK_SPEED;
				m_move.z += cosf(rotCamera.y) * WALK_SPEED;
				m_rotDest.y = rotCamera.y + D3DX_PI;
			}
		}
		else if (keyboard->GetPress(CInput::KEYINFO_WALK_DOWN) == true ||
			gamepad->GetPress(CInput::KEYINFO_WALK_DOWN) == true)
		{
			if (keyboard->GetPress(CInput::KEYINFO_WALK_LEFT) == true ||
				gamepad->GetPress(CInput::KEYINFO_WALK_LEFT) == true)
			{// ��������
				m_move.x += cosf(rotCamera.y + D3DX_PI * 3 / 4) * WALK_SPEED;
				m_move.z -= sinf(rotCamera.y + D3DX_PI * 3 / 4) * WALK_SPEED;
				m_rotDest.y = rotCamera.y + D3DX_PI / 4;
			}
			else if (keyboard->GetPress(CInput::KEYINFO_WALK_RIGHT) == true ||
				gamepad->GetPress(CInput::KEYINFO_WALK_RIGHT) == true)
			{// �E������
				m_move.x -= cosf(rotCamera.y - D3DX_PI * 3 / 4) * WALK_SPEED;
				m_move.z += sinf(rotCamera.y - D3DX_PI * 3 / 4) * WALK_SPEED;
				m_rotDest.y = rotCamera.y + D3DX_PI / -4;
			}
			else
			{// ������
				m_move.x += sinf(rotCamera.y - D3DX_PI) * WALK_SPEED;
				m_move.z += cosf(rotCamera.y - D3DX_PI) * WALK_SPEED;
				m_rotDest.y = rotCamera.y;
			}
		}
		else if (keyboard->GetPress(CInput::KEYINFO_WALK_LEFT) == true ||
			gamepad->GetPress(CInput::KEYINFO_WALK_LEFT) == true)
		{
			m_move.x -= cosf(rotCamera.y) * WALK_SPEED;
			m_move.z += sinf(rotCamera.y) * WALK_SPEED;
			m_rotDest.y = rotCamera.y + (D3DX_PI / 2);
		}
		else if (keyboard->GetPress(CInput::KEYINFO_WALK_RIGHT) == true ||
			gamepad->GetPress(CInput::KEYINFO_WALK_RIGHT) == true)
		{
			m_move.x += cosf(rotCamera.y) * WALK_SPEED;
			m_move.z -= sinf(rotCamera.y) * WALK_SPEED;
			m_rotDest.y = rotCamera.y + (D3DX_PI / -2);
		}
	}

	if (keyboard->GetPress(CInput::KEYINFO_UP) == true ||
		keyboard->GetPress(CInput::KEYINFO_DOWN) == true ||
		keyboard->GetPress(CInput::KEYINFO_LEFT) == true ||
		keyboard->GetPress(CInput::KEYINFO_RIGHT) == true ||
		gamepad->GetPress(CInput::KEYINFO_UP) == true ||
		gamepad->GetPress(CInput::KEYINFO_DOWN) == true ||
		gamepad->GetPress(CInput::KEYINFO_LEFT) == true ||
		gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
	{// ����
		m_nDashCnt++;	// �_�b�V���J�E���g���Z

		if (keyboard->GetPress(CInput::KEYINFO_UP) == true ||
			gamepad->GetPress(CInput::KEYINFO_UP) == true)
		{// �����
			if (keyboard->GetPress(CInput::KEYINFO_LEFT) == true ||
				gamepad->GetPress(CInput::KEYINFO_LEFT) == true)
			{// �������
				m_move.x -= cosf(rotCamera.y + D3DX_PI / 4) * m_fDashPower;
				m_move.z += sinf(rotCamera.y + D3DX_PI / 4) * m_fDashPower;
				m_rotDest.y = rotCamera.y + (D3DX_PI * 3 / 4);
			}
			else if (keyboard->GetPress(CInput::KEYINFO_RIGHT) == true ||
				gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
			{// �E�����
				m_move.x += cosf(rotCamera.y - D3DX_PI / 4) * m_fDashPower;
				m_move.z -= sinf(rotCamera.y - D3DX_PI / 4) * m_fDashPower;
				m_rotDest.y = rotCamera.y - (D3DX_PI * 3 / 4);
			}
			else
			{// �����
				m_move.x += sinf(rotCamera.y) * m_fDashPower;
				m_move.z += cosf(rotCamera.y) * m_fDashPower;
				m_rotDest.y = rotCamera.y + D3DX_PI;
			}
		}
		else if (keyboard->GetPress(CInput::KEYINFO_DOWN) == true ||
			gamepad->GetPress(CInput::KEYINFO_DOWN) == true)
		{
			if (keyboard->GetPress(CInput::KEYINFO_LEFT) == true ||
				gamepad->GetPress(CInput::KEYINFO_LEFT) == true)
			{// ��������
				m_move.x += cosf(rotCamera.y + D3DX_PI * 3 / 4) * m_fDashPower;
				m_move.z -= sinf(rotCamera.y + D3DX_PI * 3 / 4) * m_fDashPower;
				m_rotDest.y = rotCamera.y + D3DX_PI / 4;
			}
			else if (keyboard->GetPress(CInput::KEYINFO_RIGHT) == true ||
				gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
			{// �E������
				m_move.x -= cosf(rotCamera.y - D3DX_PI * 3 / 4) * m_fDashPower;
				m_move.z += sinf(rotCamera.y - D3DX_PI * 3 / 4) * m_fDashPower;
				m_rotDest.y = rotCamera.y + D3DX_PI / -4;
			}
			else
			{// ������
				m_move.x += sinf(rotCamera.y - D3DX_PI) * m_fDashPower;
				m_move.z += cosf(rotCamera.y - D3DX_PI) * m_fDashPower;
				m_rotDest.y = rotCamera.y;
			}
		}
		else if (keyboard->GetPress(CInput::KEYINFO_LEFT) == true ||
			gamepad->GetPress(CInput::KEYINFO_LEFT) == true)
		{
			m_move.x -= cosf(rotCamera.y) * m_fDashPower;
			m_move.z += sinf(rotCamera.y) * m_fDashPower;
			m_rotDest.y = rotCamera.y + (D3DX_PI / 2);
		}
		else if (keyboard->GetPress(CInput::KEYINFO_RIGHT) == true ||
			gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
		{
			m_move.x += cosf(rotCamera.y) * m_fDashPower;
			m_move.z -= sinf(rotCamera.y) * m_fDashPower;
			m_rotDest.y = rotCamera.y + (D3DX_PI / -2);
		}
	}
	else
	{
		if (m_nDashCnt > 0)
		{
			// ������Ԃ̌���
			m_nDashCnt -= 5;
		}
	}

	// �_�b�V���ɂ�����
	if (m_nDashCnt < SPEED_RANK_CNT)
	{
		m_fDashPower = 1.0f;
	}
	else if (m_nDashCnt <= 0)
	{
		m_fDashPower = 0.0f;
	}
	else if (m_nDashCnt < SPEED_RANK_CNT * 2)
	{
		m_fDashPower = 1.5f;
	}
	else
	{
		m_fDashPower = 2.0f;
	}

	// �ړI�̉�]�p�̏��
	if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2.0f;
	}
	else if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2.0f;
	}

	// �����̍X�V
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;

	// ���݂̉�]�p�̏��
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	// ������̌�������
	m_move.x += (0.0f - m_move.x) * SPEED_DOWN;
	m_move.z += (0.0f - m_move.z) * SPEED_DOWN;

	// ���[�V�����̐؂�ւ�
	if (m_move.x > MOVE_MOTION || m_move.z > MOVE_MOTION || m_move.x < -MOVE_MOTION || m_move.z < -MOVE_MOTION)
	{// �ړ��͂Ń��[�V�������ێ�
		if (m_bLand == true)
		{// �n��ɂ��鎞
			if (m_move.x > RUN_MOTION || m_move.z > RUN_MOTION || m_move.x < -RUN_MOTION || m_move.z < -RUN_MOTION)
			{
				// ���郂�[�V����
				m_pMotionPlayer->SetMotion(CMotionPlayer::MOTIONTYPE_RUN);
			}
			else
			{
				// �������[�V����
				m_pMotionPlayer->SetMotion(CMotionPlayer::MOTIONTYPE_WALK);
			}		
		}		
	}
	else if(m_pMotionPlayer->GetMotion() == CMotionPlayer::MOTIONTYPE_RUN || m_pMotionPlayer->GetMotion() == CMotionPlayer::MOTIONTYPE_WALK)
	{
		// �j���[�g�����֖߂�
		m_pMotionPlayer->SetMotion(CMotionPlayer::MOTIONTYPE_NEUTRAL);
	}
}