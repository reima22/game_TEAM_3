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
#include "model.h"
#include "input.h"
#include "gamepad.h"
#include "textdata_player.h"
#include "textdata_object.h"
#include "camera.h"
#include "shadow.h"
#include "collision.h"
#include "game.h"
#include "object.h"
#include "Terrain.h"

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
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�L�X�g�f�[�^�̎擾
	CTextDataPlayer *pDataPlayer = CTextDataPlayer::GetDataPlayer();

	// �p�[�c��
	m_nNumParts = pDataPlayer->GetPartsNum();

	// �����蔻��̒l
	m_fRadius = pDataPlayer->GetRadius();
	m_fHeight = pDataPlayer->GetHeight();
	
	// �L�[�J�E���g��
	m_nKeyCnt = 0;

	// ���f���̓��I�m��
	m_apModel = new CModel*[m_nNumParts];
	m_aIndexParent = new int[m_nNumParts];
	m_aOffset = new float*[m_nNumParts];
	m_posMemo = new D3DXVECTOR3[m_nNumParts];
	m_rotMemo = new D3DXVECTOR3[m_nNumParts];

	m_bLand = true;
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �I�u�W�F�N�g�^�C�v
	SetObjType(OBJTYPE_PLAYER);

	// �p�[�c���Ƃ̐ݒ�
	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		// �e�̃C���f�b�N�X���̎擾
		m_aIndexParent[nCnt] = pDataPlayer->GetParent(nCnt);

		// �e�p�����[�^���m��
		m_aOffset[nCnt] = new float[CTextDataPlayer::INFOMAX];

		for (int nCntOffset = 0; nCntOffset < CTextDataPlayer::INFOMAX; nCntOffset++)
		{
			// �I�t�Z�b�g���̎擾
			m_aOffset[nCnt][nCntOffset] = pDataPlayer->GetOffset(nCnt, nCntOffset);
		}

		// X�t�@�C�����擾
		char *pFileName = pDataPlayer->GetFileName(nCnt);

		// �p�[�c���Ƃ̃I�t�Z�b�g�ʒu
		D3DXVECTOR3 pos = D3DXVECTOR3(
			m_aOffset[nCnt][CTextDataPlayer::INFO_POS_X],
			m_aOffset[nCnt][CTextDataPlayer::INFO_POS_Y], 
			m_aOffset[nCnt][CTextDataPlayer::INFO_POS_Z]);

		// �p�[�c���Ƃ̃I�t�Z�b�g�p�x
		D3DXVECTOR3 rot = D3DXVECTOR3(
			m_aOffset[nCnt][CTextDataPlayer::INFO_ROT_X],
			m_aOffset[nCnt][CTextDataPlayer::INFO_ROT_Y],
			m_aOffset[nCnt][CTextDataPlayer::INFO_ROT_Z]);

		// ���f���̐���
		m_apModel[nCnt] = CModel::Create(pFileName, pos, rot);

		if (nCnt != 0)
		{
			m_apModel[nCnt]->SetParent(m_apModel[m_aIndexParent[nCnt]]);
		}		
	}

	// �L�[������
	for (int nCntMotion = 0; nCntMotion < MOTIONTYPE_MAX; nCntMotion++)
	{
		m_nNumKey[nCntMotion] = pDataPlayer->GetNumKey((MOTIONTYPE)nCntMotion);

		// �t���[�����̃��[�V�������̓��I�m��
		m_pFrame[nCntMotion] = new int[m_nNumKey[nCntMotion]];

		// �L�[�t���[�����̃��[�V�������Ƃ̊m��
		m_aKey[nCntMotion] = new float**[m_nNumKey[nCntMotion]];

		for (int nCntKey = 0; nCntKey < m_nNumKey[nCntMotion]; nCntKey++)
		{
			// �t���[�����̎擾
			m_pFrame[nCntMotion][nCntKey] = pDataPlayer->GetFrame((MOTIONTYPE)nCntMotion, nCntKey);
			
			// �L�[�t���[�����̃L�[�����Ƃ̊m��
			m_aKey[nCntMotion][nCntKey] = new float*[m_nNumParts];
			
			// �p�[�c������
			for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
			{
				// �L�[�t���[�����̃p�[�c���Ƃ̊m��
				m_aKey[nCntMotion][nCntKey][nCntParts] = new float[KEY_MAX];

				// �L�[���
				m_aKey[nCntMotion][nCntKey][nCntParts][KEY_POS_X] = pDataPlayer->GetKeyInfo((MOTIONTYPE)nCntMotion, nCntKey, nCntParts, KEY_POS_X);
				m_aKey[nCntMotion][nCntKey][nCntParts][KEY_POS_Y] = pDataPlayer->GetKeyInfo((MOTIONTYPE)nCntMotion, nCntKey, nCntParts, KEY_POS_Y);
				m_aKey[nCntMotion][nCntKey][nCntParts][KEY_POS_Z] = pDataPlayer->GetKeyInfo((MOTIONTYPE)nCntMotion, nCntKey, nCntParts, KEY_POS_Z);
				m_aKey[nCntMotion][nCntKey][nCntParts][KEY_ROT_X] = pDataPlayer->GetKeyInfo((MOTIONTYPE)nCntMotion, nCntKey, nCntParts, KEY_ROT_X);
				m_aKey[nCntMotion][nCntKey][nCntParts][KEY_ROT_Y] = pDataPlayer->GetKeyInfo((MOTIONTYPE)nCntMotion, nCntKey, nCntParts, KEY_ROT_Y);
				m_aKey[nCntMotion][nCntKey][nCntParts][KEY_ROT_Z] = pDataPlayer->GetKeyInfo((MOTIONTYPE)nCntMotion, nCntKey, nCntParts, KEY_ROT_Z);
			}
		}
	}

	// �v���C���[�̈ʒu�E�����̐ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �e�̃T�C�Y�ݒ�
	D3DXVECTOR2 shadowSize = D3DXVECTOR2(15.0f,15.0f);

	// �e�̐ݒ�
	m_pShadow = CShadow::Create(shadowSize);

	return S_OK;
}

//==============================================================================
// �v���C���[�̏I������
//==============================================================================
void CPlayer::Uninit(void)
{
	// ���f�����̔j��
	if (m_apModel != NULL)
	{
		delete m_apModel;
		m_apModel = NULL;
	}

	// �e���̔j��
	if (m_aIndexParent != NULL)
	{
		delete m_aIndexParent;
		m_aIndexParent = NULL;
	}

	// �ߋ��̈ʒu���̔j��
	if (m_posMemo != NULL)
	{
		delete m_posMemo;
		m_posMemo = NULL;
	}

	// �ߋ��̌��������̔j��
	if (m_rotMemo != NULL)
	{
		delete m_rotMemo;
		m_rotMemo = NULL;
	}

	// �t���[���̔j��
	for (int nCntMotion = 0; nCntMotion < MOTIONTYPE_MAX; nCntMotion++)
	{
		if (m_pFrame[nCntMotion] != NULL)
		{
			delete m_pFrame[nCntMotion];
			m_pFrame[nCntMotion] = NULL;
		}
	}

	// �I�t�Z�b�g���̔j��
	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_aOffset[nCnt] != NULL)
		{
			delete[] m_aOffset[nCnt];
		}
	}
	if (m_aOffset != NULL)
	{
		delete m_aOffset;
		m_aOffset = NULL;
	}

	// �L�[���̔j��
	for (int nCntMotion = 0; nCntMotion < MOTIONTYPE_MAX; nCntMotion++)
	{
		if (m_aKey[nCntMotion] != NULL)
		{
			for (int nCntKey = 0; nCntKey < m_nNumKey[nCntMotion]; nCntKey++)
			{
				for (int nCntParts = 0; nCntParts < KEY_MAX; nCntParts++)
				{
					delete[] m_aKey[nCntMotion][nCntKey][nCntParts];
				}

				delete[] m_aKey[nCntMotion][nCntKey];
			}

			delete[] m_aKey[nCntMotion];
			m_aKey[nCntMotion] = NULL;
		}
	}
}

//==============================================================================
// �v���C���[�̍X�V����
//==============================================================================
void CPlayer::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �ړ�����
	MovePlayer();

	// �f�o�b�O�p���[�V�����Ǘ�
	if (keyboard->GetTrigger(CInput::KEYINFO_MINUS_MOTION) == true)
	{
		m_motionType = (MOTIONTYPE)(m_motionType - 1);

		if (m_motionType < 0)
		{
			// ���ڂ�1��
			m_motionType = (MOTIONTYPE)(MOTIONTYPE_MAX - 1);
		}
	}

	if (keyboard->GetTrigger(CInput::KEYINFO_PLUS_MOTION) == true)
	{
		m_motionType = (MOTIONTYPE)(m_motionType + 1);

		if (m_motionType == MOTIONTYPE_MAX)
		{
			// ���ڂ�1��
			m_motionType = (MOTIONTYPE)0;
		}
	}

	// ���[�V�����̍X�V(���p�j���[�g����)
	UpdateMotion(m_motionType);

	// �e�̒Ǐ]
	if (m_pShadow != NULL)
	{
		CCollision *pCollision;
		pCollision = CManager::GetCollision();

		if (pCollision->GetOnObject() == false)
		{
			m_pShadow->SetPosition(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z));
		}		
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
	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Draw();
		}
	}
}

//==============================================================================
// ��������
//==============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	CPlayer *pPlayer;
	pPlayer = new CPlayer;	// �C���X�^���X

	// ������
	if (pPlayer != NULL)
	{
		pPlayer->Init();
		pPlayer->SetPosition(pos);
	}

	return pPlayer;
}

//==============================================================================
// ���[�V�����̍X�V
//==============================================================================
void CPlayer::UpdateMotion(MOTIONTYPE motionType)
{
	// �e�L�X�g�f�[�^�̎擾
	CTextDataPlayer *pDataPlayer = CTextDataPlayer::GetDataPlayer();

	// �u�����h�p�t���[����
	int nBlendFrame = 10;

	// ���[�V�����ω��ɂ��J�E���g�̏�����
	if (m_motionTypeOld != motionType)
	{
		m_nKeyCnt = 0;
		m_nFrameCnt = 0;
		m_bBlendMotion = true;
	}

	// ���[�v���
	m_bLoop = pDataPlayer->GetLoop(motionType);

	// �t���[���̃J�E���g
	if (m_nFrameCnt < m_pFrame[motionType][m_nKeyCnt] || motionType != MOTIONTYPE_JUMP) 
	{
		m_nFrameCnt++;
	}

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		// �ʒu�E�p�x�̎擾
		D3DXVECTOR3 pos = m_apModel[nCnt]->GetPosition();
		D3DXVECTOR3 rot = m_apModel[nCnt]->GetRotation();

		if (m_bLoop == true && m_nKeyCnt == m_nNumKey[motionType] - 1)
		{// ���[�v����Ƃ��̐܂�Ԃ�
			pos.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X] + (m_aKey[motionType][0][nCnt][KEY_POS_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			pos.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y] + (m_aKey[motionType][0][nCnt][KEY_POS_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			pos.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z] + (m_aKey[motionType][0][nCnt][KEY_POS_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			rot.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X] + (m_aKey[motionType][0][nCnt][KEY_ROT_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			rot.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y] + (m_aKey[motionType][0][nCnt][KEY_ROT_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			rot.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z] + (m_aKey[motionType][0][nCnt][KEY_ROT_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);			
			m_posMemo[nCnt] = pos;
			m_rotMemo[nCnt] = rot;
		}
		else if (m_bLoop == false && m_nKeyCnt == m_nNumKey[motionType] - 1)
		{// ���[�v�����I�����鎞
			if (motionType == MOTIONTYPE_LANDING)
			{// �j���[�g������
				pos.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X] + (m_aKey[MOTIONTYPE_NEUTRAL][0][nCnt][KEY_POS_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
				pos.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y] + (m_aKey[MOTIONTYPE_NEUTRAL][0][nCnt][KEY_POS_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
				pos.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z] + (m_aKey[MOTIONTYPE_NEUTRAL][0][nCnt][KEY_POS_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
				rot.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X] + (m_aKey[MOTIONTYPE_NEUTRAL][0][nCnt][KEY_ROT_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
				rot.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y] + (m_aKey[MOTIONTYPE_NEUTRAL][0][nCnt][KEY_ROT_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
				rot.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z] + (m_aKey[MOTIONTYPE_NEUTRAL][0][nCnt][KEY_ROT_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
				m_posMemo[nCnt] = pos;
				m_rotMemo[nCnt] = rot;
			}
			//else if (motionType == MOTIONTYPE_DAMAGE)
			//{// ���n��
			//	pos.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X] + (m_aKey[MOTIONTYPE_STEP][0][nCnt][KEY_POS_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			//	pos.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y] + (m_aKey[MOTIONTYPE_STEP][0][nCnt][KEY_POS_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			//	pos.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z] + (m_aKey[MOTIONTYPE_STEP][0][nCnt][KEY_POS_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			//	rot.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X] + (m_aKey[MOTIONTYPE_STEP][0][nCnt][KEY_ROT_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			//	rot.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y] + (m_aKey[MOTIONTYPE_STEP][0][nCnt][KEY_ROT_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			//	rot.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z] + (m_aKey[MOTIONTYPE_STEP][0][nCnt][KEY_ROT_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			//	m_posMemo[nCnt] = pos;
			//	m_rotMemo[nCnt] = rot;
			//}
		}
		else if (m_bBlendMotion == true)
		{// ���[�V�������r���Ő؂�ւ��(���[�V�����u�����h)
			pos.x = m_posMemo[nCnt].x + (m_aKey[motionType][0][nCnt][KEY_POS_X] - m_posMemo[nCnt].x) * ((float)m_nFrameCnt / (float)nBlendFrame);
			pos.y = m_posMemo[nCnt].y + (m_aKey[motionType][0][nCnt][KEY_POS_Y] - m_posMemo[nCnt].y) * ((float)m_nFrameCnt / (float)nBlendFrame);
			pos.z = m_posMemo[nCnt].z + (m_aKey[motionType][0][nCnt][KEY_POS_Z] - m_posMemo[nCnt].z) * ((float)m_nFrameCnt / (float)nBlendFrame);
			rot.x = m_rotMemo[nCnt].x + (m_aKey[motionType][0][nCnt][KEY_ROT_X] - m_rotMemo[nCnt].x) * ((float)m_nFrameCnt / (float)nBlendFrame);
			rot.y = m_rotMemo[nCnt].y + (m_aKey[motionType][0][nCnt][KEY_ROT_Y] - m_rotMemo[nCnt].y) * ((float)m_nFrameCnt / (float)nBlendFrame);
			rot.z = m_rotMemo[nCnt].z + (m_aKey[motionType][0][nCnt][KEY_ROT_Z] - m_rotMemo[nCnt].z) * ((float)m_nFrameCnt / (float)nBlendFrame);
		}
		else
		{// �ʏ펞�̍Đ�
			pos.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X] + (m_aKey[motionType][m_nKeyCnt + 1][nCnt][KEY_POS_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			pos.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y] + (m_aKey[motionType][m_nKeyCnt + 1][nCnt][KEY_POS_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			pos.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z] + (m_aKey[motionType][m_nKeyCnt + 1][nCnt][KEY_POS_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			rot.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X] + (m_aKey[motionType][m_nKeyCnt + 1][nCnt][KEY_ROT_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			rot.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y] + (m_aKey[motionType][m_nKeyCnt + 1][nCnt][KEY_ROT_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			rot.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z] + (m_aKey[motionType][m_nKeyCnt + 1][nCnt][KEY_ROT_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			m_posMemo[nCnt] = pos;
			m_rotMemo[nCnt] = rot;
		}

		// �ʒu�E�p�x�̔��f
		m_apModel[nCnt]->SetPosition(pos);
		m_apModel[nCnt]->SetRotation(rot);
	}

	// ���[�V�����̕ς���
	if (m_bBlendMotion == false)
	{
		if (m_nFrameCnt >= m_pFrame[motionType][m_nKeyCnt] && motionType != MOTIONTYPE_JUMP)
		{
			m_nFrameCnt = 0;

			if (m_nKeyCnt < m_nNumKey[motionType] - 1)
			{// �J�E���g�̉��Z
				m_nKeyCnt++;
			}
			else
			{// �J�E���g�̃��Z�b�g
				if (m_bLoop == false)
				{
					if (motionType == MOTIONTYPE_LANDING)
					{// �A�N�V�����A���n�̎�
						m_motionType = MOTIONTYPE_NEUTRAL;
					}
				}
				else
				{
					m_nKeyCnt = 0;
				}
			}
		}
	}
	else
	{// �u�����h��
		if (m_nFrameCnt >= nBlendFrame)
		{
			m_nFrameCnt = 0;
			m_nKeyCnt = 0;

			// �u�����h�̏I��
			m_bBlendMotion = false;
		}
	}

	// �����[�V�����̕ۑ�
	m_motionTypeOld = motionType;
}

//==============================================================================
// ��������
//==============================================================================
void CPlayer::MovePlayer(void)
{
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

	// ���b�V���Ƃ̓����蔻��
	if (pTerrain != NULL)
	{
		if (pTerrain->FallCollider(this) == true && m_bLand == false)
		{
			m_pos.y = 0;
			m_bLand = true;
		}
	}

	// ���I�u�W�F�N�g�Ƃ̓����蔻��
	CCollision *pCollision;
	pCollision = CManager::GetCollision();

	if (pCollision != NULL)
	{
		CTextDataObject *pDataObject;
		pDataObject = CTextData::GetDataObject();

		int nNumObject = pDataObject->GetNumObject();

		for (int nCntObject = 0; nCntObject < nNumObject; nCntObject++)
		{
			CModel *pModel = CGame::GetPointObject(nCntObject)->GetModel();

			if (pCollision->Collision3D(this, pModel) == true && m_bLand == false)
			{
				m_bLand = true;
			}
		}
	}

	// �ߋ��ʒu�̍X�V
	m_posOld = m_pos;

	// �d�͂̔���
	if (m_pos.y > 0.0f && m_bLand == false)
	{
		m_move.y -= GRAVITY_SCALE;
	}

	// �v���C���[�̒��n����
	if (m_bLand == false)
	{
		//if (m_pos.y < 0.0f)
		//{// �ł��Ⴂ�ʒu
		//	m_bLand = true;
		//	//m_nKeyCnt = 0;
		//	//m_nFrameCnt = 0;
		//}
	}
	else if (m_bLand == true)
	{// ���n���
		//if (m_pos.y < 0.0f)
		//{
		//	m_pos.y = 0.0f;
		//}

		if (m_bJump == true)
		{
			if (m_motionType == MOTIONTYPE_JUMP || m_motionType == MOTIONTYPE_RUN)
			{
				m_motionType = MOTIONTYPE_LANDING;
			}
		}

		m_bJump = false;
		m_move.y = 0.0f;
	}

	// �W�����v�F���n���Ă���
	if (keyboard->GetTrigger(CInput::KEYINFO_JUMP) == true ||
		gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		if (m_bLand == true)
		{
			m_nKeyCnt = 0;
			m_nFrameCnt = 0;
			m_motionType = MOTIONTYPE_JUMP;
		}

		m_bLand = false;
	}
	if (keyboard->GetPress(CInput::KEYINFO_JUMP) == true ||
		gamepad->GetPress(CInput::KEYINFO_OK) == true)
	{
		if (m_bJump == false)
		{
			if (m_nJumpCnt == 1)
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
	if (keyboard->GetRelease(CInput::KEYINFO_JUMP) == true ||
		gamepad->GetRelease(CInput::KEYINFO_OK) == true)
	{
		m_nJumpCnt = 0;
		m_bJump = true;
	}

	// �ړ�
	m_pos += m_move;

	// �ړ�����
	// ����
	if (keyboard->GetPress(CInput::KEYINFO_WALK_UP) == true ||
		keyboard->GetPress(CInput::KEYINFO_WALK_DOWN) == true ||
		keyboard->GetPress(CInput::KEYINFO_WALK_LEFT) == true ||
		keyboard->GetPress(CInput::KEYINFO_WALK_RIGHT) == true ||
		gamepad->GetPress(CInput::KEYINFO_WALK_UP) == true ||
		gamepad->GetPress(CInput::KEYINFO_WALK_DOWN) == true ||
		gamepad->GetPress(CInput::KEYINFO_WALK_LEFT) == true ||
		gamepad->GetPress(CInput::KEYINFO_WALK_RIGHT) == true)
	{
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

	// ����
	if (keyboard->GetPress(CInput::KEYINFO_UP) == true ||
		keyboard->GetPress(CInput::KEYINFO_DOWN) == true ||
		keyboard->GetPress(CInput::KEYINFO_LEFT) == true ||
		keyboard->GetPress(CInput::KEYINFO_RIGHT) == true ||
		gamepad->GetPress(CInput::KEYINFO_UP) == true ||
		gamepad->GetPress(CInput::KEYINFO_DOWN) == true ||
		gamepad->GetPress(CInput::KEYINFO_LEFT) == true ||
		gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
	{
		m_nDashCnt++;

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
		m_nDashCnt = 0;
		m_fDashPower = 0.0f;
	}

	if (m_nDashCnt < 60)
	{
		m_fDashPower = 1.0f;
	}
	else if (m_nDashCnt < 120)
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
				SetMotion(MOTIONTYPE_RUN);
			}
			else
			{
				// �������[�V����
				SetMotion(MOTIONTYPE_WALK);
			}		
		}		
	}
	else if(m_motionType == MOTIONTYPE_RUN || m_motionType == MOTIONTYPE_WALK)
	{
		SetMotion(MOTIONTYPE_NEUTRAL);
	}
}