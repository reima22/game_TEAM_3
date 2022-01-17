//==============================================================================
//
// �v���C���[���[�V�����Ǘ��kmotion_player.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "model.h"
#include "motion.h"
#include "motion_player.h"
#include "textdata_player.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CMotionPlayer::CMotionPlayer()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CMotionPlayer::~CMotionPlayer()
{

}

//==============================================================================
// �v���C���[���[�V�����̏�����
//==============================================================================
HRESULT CMotionPlayer::Init(void)
{
	// �e�L�X�g�f�[�^�̎擾
	CTextDataPlayer *pDataPlayer = CTextDataPlayer::GetDataPlayer();

	// �p�[�c��
	m_nNumParts = pDataPlayer->GetPartsNum();

	// ���f���̓��I�m��
	m_apModel = new CModel*[m_nNumParts];
	m_aIndexParent = new int[m_nNumParts];
	m_aOffset = new float*[m_nNumParts];
	m_posMemo = new D3DXVECTOR3[m_nNumParts];
	m_rotMemo = new D3DXVECTOR3[m_nNumParts];

	// ���[�V�������̓��I�m��
	m_aKey = new float***[MOTIONTYPE_MAX];	// �L�[���
	m_nNumKey = new int[MOTIONTYPE_MAX];	// �L�[�̐�
	m_pFrame = new int*[MOTIONTYPE_MAX];	// �t���[����

	// �L�[�J�E���g��
	m_nKeyCnt = 0;

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

	return S_OK;
}

//==============================================================================
// �v���C���[���[�V�����̏I��
//==============================================================================
void CMotionPlayer::Uninit(void)
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
// �v���C���[���[�V�����̍X�V
//==============================================================================
void CMotionPlayer::Update(MOTIONTYPE motionType)
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
// �`��
//==============================================================================
void CMotionPlayer::Draw(void)
{
	for (int nCntModel = 0; nCntModel < m_nNumParts; nCntModel++)
	{
		if (m_apModel[nCntModel] != NULL)
		{
			// ���f���̕`��
			m_apModel[nCntModel]->Draw();
		}
	}
}

//==============================================================================
// �v���C���[���[�V�����̐���
//==============================================================================
CMotionPlayer *CMotionPlayer::Create(void)
{
	// ���[�J���ϐ��錾
	CMotionPlayer *pMotionPlayer;
	pMotionPlayer = new CMotionPlayer;

	// ������
	if (pMotionPlayer != NULL)
	{
		pMotionPlayer->Init();
	}

	return pMotionPlayer;
}