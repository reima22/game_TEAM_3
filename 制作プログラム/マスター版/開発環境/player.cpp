//==============================================================================
//
// �v���C���[�Ǘ��kplayer.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "bonus.h"
#include "bonus_count.h"
#include "camera.h"
#include "checkpoint_logo.h"
#include "collision.h"
#include "effect.h"
#include "fade.h"
#include "fall_count.h"
#include "game.h"
#include "gamepad.h"
#include "input.h"
#include "main.h"
#include "manager.h"
#include "motion.h"
#include "motion_player.h"
#include "object.h"
#include "player.h"
#include "renderer.h"
#include "result.h"
#include "select.h"
#include "shadowS.h"
#include "start_cntdown.h"
#include "Terrain.h"
#include "textdata_player.h"
#include "textdata_object.h"
#include "timer.h"
#include "timer_count.h"
#include "ui.h"

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

	m_posNeutral = pDataPlayer->GetPosition();

	// �����ʒu�̃��X�|�[���n�_
	m_posSave = m_pos;

	// �ߋ��̈ʒu
	m_posOld = VECTOR3_NULL;

	m_nCntSandEffect = 0;

	// �I�u�W�F�N�g�^�C�v
	SetObjType(OBJTYPE_PLAYER);

	// ���[�V�������̐���
	m_pMotionPlayer = CMotionPlayer::Create();

	// �e�̐ݒ�
	m_pShadowS = CShadowS::Create(m_pos);

	// �I�������菉����
	m_bSetGameClear = false;
	m_bSetGameOver = false;

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

	// �e�̊J��
	if (m_pShadowS != NULL)
	{
		m_pShadowS->Uninit();
		m_pShadowS = NULL;
	}
}

//==============================================================================
// �v���C���[�̍X�V����
//==============================================================================
void CPlayer::Update(void)
{
	// UI���
	CUi *pUi = CGame::GetUi();

	// �^�C�}�[�ɂ�锻��
	if (pUi != NULL)
	{
		if (pUi->GetTimer()->GetTimerCnt()->GetNumber() <= 0 && m_bSetGameOver == false)
		{
			m_bSetGameOver = true;
			m_pSound->Play(CSound::SOUND_LABEL_SE_GAMEOVER);
		}
	}

	// �ړ�����
	if (pUi->GetStartCntdown()->GetCntDown() == false && m_resetPhase == RESETPHASE_NONE)
	{
		MovePlayer();
	}
	else
	{
		m_nDashCnt = 0;
		m_nJumpCnt = 0;
		m_pMotionPlayer->SetMotion(CMotionPlayer::MOTIONTYPE_NEUTRAL);
	}

	// ���X�|�[���ʒu�ւ̑��ҏ���
	ResetPlayer();

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

	// �N���A���̋���
	if (m_bSetGameClear == true)
	{
		ClearMotion();
	}
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
	// �t�F�[�h���̎擾
	CFade *pFade;
	pFade = CManager::GetFade();

	// �e�L�X�g�f�[�^�̎擾
	CTextDataPlayer *pDataPlayer = CTextDataPlayer::GetDataPlayer();

	if (CGame::GetGameEnd() == false)
	{
		// ���I�u�W�F�N�g�Ƃ̓����蔻��
		Collision();
	}

	// �ߋ��ʒu�̍X�V
	m_posOld = m_pos;

	// �d�͂̔���
	if (m_bLandObj == false && m_bLandMesh == false)
	{
		m_move.y -= GRAVITY_SCALE;
		m_nCntAir++;
		if (m_nCntAir >= AIR_CONTROL)
		{
			m_bAirControl = false;
		}
	}
	else
	{// ���n���
		if (m_bJump == true)
		{// �W�����v���璅�n
			if (m_pMotionPlayer->GetMotion() == CMotionPlayer::MOTIONTYPE_JUMP || m_pMotionPlayer->GetMotion() == CMotionPlayer::MOTIONTYPE_RUN)
			{
				// ���n���[�V����
				m_pMotionPlayer->SetMotion(CMotionPlayer::MOTIONTYPE_LANDING);
			}
		}

		m_nCntAir = 0;
		m_bAirControl = true;
		m_bJump = false;
		m_move.y = 0.0f;
	}

	// �Q�[���I���܂ő���\
	if (m_bSetGameClear == false && m_bSetGameOver == false)
	{
		ControlPlayer();
	}

	// ���[�V�����̐؂�ւ�
	if (m_move.x > MOVE_MOTION || m_move.z > MOVE_MOTION || m_move.x < -MOVE_MOTION || m_move.z < -MOVE_MOTION)
	{// �ړ��͂Ń��[�V�������ێ�
		if (m_bLandObj == true || m_bLandMesh == true)
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

//==============================================================================
// �v���C���[����
//==============================================================================
void CPlayer::ControlPlayer(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �J�����̎擾
	CCamera *pCamera = CManager::GetCamera();

	// �J�����̕���
	D3DXVECTOR3 rotCamera = pCamera->GetRotation();

	// �W�����v�F���n���Ă���
	if (keyboard->GetTrigger(CInput::KEYINFO_JUMP) == true ||
		gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		// ���n���Ă���Ƃ��̂݃W�����v
		if (m_bJump == false)
		{
			m_pMotionPlayer->SetMotion(CMotionPlayer::MOTIONTYPE_JUMP);		// �W�����v���[�V�����؂�ւ�
			m_move.y = 0.5f;												// �����W�����v�͂̐ݒ�
			m_pSound->Play(CSound::SOUND_LABEL_SE_JUMP);					// �W�����v��
		}

		// ���n����̉���
		m_bLandObj = false;
		m_bLandMesh = false;
	}
	if (keyboard->GetPress(CInput::KEYINFO_JUMP) == true ||
		gamepad->GetPress(CInput::KEYINFO_OK) == true)
	{
		// �؋���
		if (m_bJump == false && m_bLanding == false)
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
		}
	}
	
	// �W�����v�{�^���𗣂�
	if (keyboard->GetRelease(CInput::KEYINFO_JUMP) == true ||
		gamepad->GetRelease(CInput::KEYINFO_OK) == true)
	{
		m_nJumpCnt = 0;
		m_bJump = true;
	}

	if (m_bAirControl == true)
	{
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
	}

	if (CGame::GetGameEnd() == false)
	{
		// �ړ�
		m_pos += m_move;
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
		
		if (m_bLanding == true)
		{
			CEffectDetail::Create(CEffectDetail::EFFECTTYPE_SANDSMOKE, m_pos);
		}
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

	if (m_bAirControl == true)
	{
		// ������̌�������
		m_move.x += (0.0f - m_move.x) * SPEED_DOWN;
		m_move.z += (0.0f - m_move.z) * SPEED_DOWN;
	}

	// �W�����v�\���
	if (m_bLanding == true)
	{
		m_nJumpLimit = 0;
	}
	else
	{
		// �t���[���J�E���g���̉��Z
		m_nJumpLimit++;

		// ���t���[�������z����
		if (m_nJumpLimit > 10)
		{
			m_bJump = true;
		}
	}
}

//==============================================================================
// �����蔻��
//==============================================================================
void CPlayer::Collision(void)
{
	// UI
	CUi *pUi = CGame::GetUi();

	// ���b�V��
	CTerrain *pTerrain = CGame::GetTerrain();

	// �`�F�b�N�|�C���g���S
	CCheckpointLogo *pCheckPointLogo = pUi->GetCheckPointLogo();

	// ���S���胁�b�V���Ƃ̓����蔻��
	if (pTerrain != NULL)
	{
		if (pTerrain->FallCollider(this) == true)
		{
			if (pTerrain->GetType() == CTerrainInfo::TERRAIN_OCEAN || pTerrain->GetType() == CTerrainInfo::TERRAIN_VALLEY)
			{
				m_pSound->Play(CSound::SOUND_LABEL_SE_DIVE02);
				CEffectDetail::Create(CEffectDetail::EFFECTTYPE_DIVE_WATER, m_pos);
			}
			else if (pTerrain->GetType() == CTerrainInfo::TERRAIN_LAVA)
			{
				m_pSound->Play(CSound::SOUND_LABEL_SE_DIVE00);
				m_bIntoLava = true;
				m_posLava = m_pos;
			}

			// ���������Z
			pUi->GetFall()->GetFallCount()->AddFall(1);

			// ���Z�b�g�J�n
			ResetOn();
		}
	}

	// �X�e�[�W�O��������
	if (m_pos.y < -FALL_RETURN)
	{
		// ���Z�b�g�J�n
		ResetOn();

		// ������
		m_pSound->Play(CSound::SOUND_LABEL_SE_DIVE01);

		// ���������Z
		pUi->GetFall()->GetFallCount()->AddFall(1);
	}

	// ���I�u�W�F�N�g�Ƃ̓����蔻��
	CCollision *pCollision;
	pCollision = CManager::GetCollision(); // �����蔻��擾

	// �J�n���J�E���g
	CStartCntdown *pStartCntdown;
	pStartCntdown = pUi->GetStartCntdown();

	if (pCollision != NULL)
	{
		CScene *pScene = CScene::GetScene(PRIORITY_DEFAULT);
		CScene *pSceneNext = NULL;

		m_bLandObj = false;
		m_bLanding = false;

		while (pScene)
		{
			pSceneNext = CScene::GetSceneNext(pScene);

			if (pScene->GetObjType() == OBJTYPE_OBJECT)
			{
				CObject *pObject = (CObject*)pScene;

				// ���f���|�C���^
				CModel *pModel = NULL;

				// ���f�����̎擾
				pModel = pObject->GetModel();

				if (pObject->GetObjAttribute() != CObject::OBJATTRIBUTE_PHANTOM)
				{
					if (pCollision->Collision3D(this, pModel) == true)
					{
						// �����G�t�F�N�g
						if (m_nCntSandEffect < 1)
						{
							CEffectDetail::Create(CEffectDetail::EFFECTTYPE_LANDING, m_pos);
							m_nCntSandEffect++;
						}

						// ����{�[�i�X
						if ((pObject->GetObjAttribute() == CObject::OBJATTRIBUTE_SCAFFORD ||
							pObject->GetObjAttribute() == CObject::OBJATTRIBUTE_SCAFFORD_NODROP) && pObject->GetBonus() == false)
						{
							// ��x���񂾔���
							pObject->SetBonus(true);

							pUi->GetBonus()->GetCount()->AddBonus(1);
						}
						
						m_bLandObj = true;	// �I�u�W�F�N�g�ւ̒��n����

						switch (pObject->GetObjAttribute())
						{
						case CObject::OBJATTRIBUTE_SAVE:	// ���Ԓn�_
							if (m_posSave != D3DXVECTOR3(pModel->GetPosition().x, m_posSave.y, pModel->GetPosition().z))
							{
								// �ꎞ�I�ۑ�����
								pUi->GetBonus()->GetCount()->SaveBonus(pUi->GetBonus()->GetCount()->GetNumber());
								m_posSave = D3DXVECTOR3(pModel->GetPosition().x, m_posSave.y, pModel->GetPosition().z);
								m_pSound->Play(CSound::SOUND_LABEL_SE_SAVEPOINT);
								pCheckPointLogo->MoveTypeNext();
							}
							break;

						case CObject::OBJATTRIBUTE_START:	// �X�^�[�g�n�_
															// ���C���X�^�[�g�|�C���g�̎擾�ƃ��X�|�[���n�_�̐ݒ�
							m_posSave = D3DXVECTOR3(
								pObject->GetModel()->GetPosition().x,
								m_posSave.y,
								pObject->GetModel()->GetPosition().z - 200.0f);

							pStartCntdown->SetStartCntdown(true);

							break;

						case CObject::OBJATTRIBUTE_GOAL:	// �S�[���n�_
															// ���U���g��
							if (m_bSetGameClear == false)
							{
								m_bSetGameClear = true;
								m_pSound->Stop();
								m_pSound->Play(CSound::SOUND_LABEL_SE_GOAL);
							}

							CGame::SetGameEnd(true);

							break;
						}

						if (pObject->GetObjAttribute() == CObject::OBJATTRIBUTE_SCAFFORD || pObject->GetObjAttribute() == CObject::OBJATTRIBUTE_SCAFFORD_TUTO)
						{
							pObject->SetDropOut(true);
						}

						//break;			// ����L���Ń��[�v���E�o
					}
				}
			}

			pScene = pSceneNext;
		}

		for (int nCntMesh = 0; nCntMesh < 1; nCntMesh++)
		{
			if (pCollision->CollisionMesh(this, CGame::GetMeshField(nCntMesh)) == true)
			{
				m_bLandMesh = true;
				break;
			}
			else
			{
				m_bLandMesh = false;
			}
		}
	}

	if (m_bLandMesh == true || m_bLandObj == true)
	{
		m_bLanding = true;
	}
	else
	{
		m_bLanding = false;
	}


	// ���n����
	if (m_bLanding == true)
	{
		m_nCntSandEffect++;
	}
	else
	{
		m_nCntSandEffect = 0;
	}
}

//==============================================================================
// �v���C���[�̕���
//==============================================================================
void CPlayer::ResetPlayer(void)
{
	switch (m_resetPhase)
	{
	case RESETPHASE_NONE:	// ���s�҂�

		//m_resetPhase = RESETPHASE_WAIT;	// �ҋ@��Ԃֈڍs
		
		break;

	case RESETPHASE_WAIT:	// �ꎞ�ҋ@

		m_nCntReset++;

		if (m_bIntoLava == true && m_nCntReset % 6 == 0)
		{
			CEffectDetail::Create(CEffectDetail::EFFECTTYPE_DIVE_LAVA, m_posLava);
		}

		if (m_nCntReset >= CNT_ONE_SECOND)
		{
			m_resetPhase = RESETPHASE_ON;
		}

		break;

	case RESETPHASE_ON:	// ���Z�b�g���s
		
		m_move = VECTOR3_NULL;
		m_pos = m_posSave;
		m_nDashCnt = 0;
		m_nCntReset = 0;
		m_resetPhase = RESETPHASE_NONE;

		if (m_bIntoLava == true)
		{
			m_bIntoLava = false;
		}

		// ����̕���
		CScene *pScene = CScene::GetScene(PRIORITY_DEFAULT);
		CScene *pSceneNext = NULL;

		while (pScene)
		{
			pSceneNext = CScene::GetSceneNext(pScene);

			if (pScene->GetObjType() == OBJTYPE_OBJECT)
			{
				CObject *pObject = (CObject*)pScene;

				pObject->ResetObject();
			}

			pScene = pSceneNext;
		}
		break;
	}
}

//==============================================================================
// �N���A���̃v���C���[���[�V����
//==============================================================================
void CPlayer::ClearMotion(void)
{
	m_move = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;

	// �N���A����
	CResult::SetEndState(CResult::ENDSTATE_CLEAR);
}
