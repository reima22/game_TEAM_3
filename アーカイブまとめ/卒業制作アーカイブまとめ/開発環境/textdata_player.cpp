//==============================================================================
//
// �e�L�X�g�f�[�^�i�v���C���[�j�Ǘ��ktextdata_player.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "textdata.h"
#include "textdata_player.h"
#include "stdio.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTextDataPlayer::CTextDataPlayer()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTextDataPlayer::~CTextDataPlayer()
{

}

//==============================================================================
// �e�L�X�g�̓ǂݍ���
//==============================================================================
void CTextDataPlayer::LoadData(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	char aLoadText[TEXT_NUM];
	char *pLoadText = &aLoadText[0];

	// ���l�J�E���g
	m_nModelCnt = 0;
	m_nPartsCnt = 0;

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileName[TEXTDATA_PLAYER], "r");

	if (pFile != NULL)
	{ //�t�@�C���W�J�\

		// �X�N���v�g�ǂݍ��ݏI���܂�
		while (strcmp("END_SCRIPT", pLoadText) != 0)
		{
			// ���ړǂݍ���
			fscanf(pFile, "%s", pLoadText);

			// ���f����
			if (strcmp("NUM_MODEL", pLoadText) == 0)
			{
				fscanf(pFile, "%s %d" , &aLoadText[0],&m_nNumModel);

				// ���f�������A���I�m��
				m_pFileModelName = new char*[m_nNumModel];

				m_pFileModelNameLoad = new char*[m_nNumModel];
				
				// 2�����z��̊m��
				for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
				{
					m_pFileModelNameLoad[nCnt] = new char[TEXT_NUM];

					// �擪�A�h���X�̐ݒ�
					m_pFileModelName[nCnt] = &m_pFileModelNameLoad[nCnt][0];
				}
			}

			// ���f���t�@�C����
			if (strcmp("MODEL_FILENAME", pLoadText) == 0)
			{			
				// ���f����
				fscanf(pFile, "%s %s", &aLoadText[0], &m_pFileModelNameLoad[m_nModelCnt][0]);

				// �J�E���g����
				m_nModelCnt++;
			}

			// �v���C���[���
			if (strcmp("PLAYERSET", pLoadText) == 0)
			{
				// ���[�J���ϐ��錾
				char aPlayerText[TEXT_NUM] = {};
				char *pPlayerText = &aPlayerText[0];

				while (strcmp("END_PLAYERSET", pPlayerText) != 0)
				{
					fscanf(pFile, "%s", &aPlayerText[0]);

					// ���ڂɑΉ������ϐ��ւ̊i�[
					if (strcmp("POS", pPlayerText) == 0)
					{// �ʒu
						fscanf(pFile, "%s %f %f %f", 
							&aPlayerText[0],
							&m_posPlayer.x,
							&m_posPlayer.y,
							&m_posPlayer.z);
					}

					if (strcmp("ROT", pPlayerText) == 0)
					{// �p�x
						fscanf(pFile, "%s %f %f %f",
							&aPlayerText[0],
							&m_rotPlayer.x,
							&m_rotPlayer.y,
							&m_rotPlayer.z);
					}

					if (strcmp("SHADOW", pPlayerText) == 0)
					{// �e�̑傫��
						fscanf(pFile, "%s %f %f",
							&aPlayerText[0],
							&m_shadowSize.x,
							&m_shadowSize.y);
					}

					if (strcmp("RADIUS", pPlayerText) == 0)
					{// �����蔻�蔼�a
						fscanf(pFile, "%s %f", &aPlayerText[0], &m_fRadius);
					}

					if (strcmp("HEIGHT", pPlayerText) == 0)
					{// �����蔻�荂��
						fscanf(pFile, "%s %f", &aPlayerText[0], &m_fHeight);
					}
				}
			}

			// �L�����N�^�[���ǂݍ���
			if (strcmp("CHARACTERSET", pLoadText) == 0)
			{
				// ���[�J���ϐ��錾
				char aCharaText[TEXT_NUM] = {};
				char *pCharaText = &aCharaText[0];

				while (strcmp("END_CHARACTERSET", pCharaText) != 0)
				{
					// �ǂݍ���
					fscanf(pFile, "%s", &aCharaText[0]);

					// ���ڂɑΉ������ϐ��ւ̊i�[
					if (strcmp("NUM_PARTS", pCharaText) == 0)
					{// ���f���̐�
						fscanf(pFile, "%s %d", &aCharaText[0], &m_nNumParts);

						// ���f���p�[�c���|�C���^�̓��I�m��
						m_pIdx = new int[m_nNumParts];			// �C���f�b�N�X���
						m_pParentIdx = new int[m_nNumParts];	// �e���
						m_pOffset = new float*[m_nNumParts];	// �I�t�Z�b�g���
					}



					// �p�[�c���ǂݍ���
					if (strcmp("PARTSSET", pCharaText) == 0)
					{
						// ���[�J���ϐ��錾
						char aPartsText[TEXT_NUM] = {};
						char *pPartsText = &aPartsText[0];

						// 2�����̊m��
						m_pOffset[m_nPartsCnt] = new float[INFOMAX];

						while (strcmp("END_PARTSSET", pPartsText) != 0)
						{
							// ���ړǂݍ���
							fscanf(pFile, "%s", pPartsText);

							// �C���f�b�N�X���
							if (strcmp("INDEX", pPartsText) == 0)
							{
								fscanf(pFile, "%s %d", &aPartsText[0], &m_pIdx[m_nPartsCnt]);
							}

							// �e�̃C���f�b�N�X
							if (strcmp("PARENT", pPartsText) == 0)
							{
								fscanf(pFile, "%s %d", &aPartsText[0], &m_pParentIdx[m_nPartsCnt]);
							}

							// �I�t�Z�b�g�ʒu
							if (strcmp("POS", pPartsText) == 0)
							{
								fscanf(pFile, "%s %f %f %f",
									&aPartsText[0],
									&m_pOffset[m_nPartsCnt][INFO_POS_X],
									&m_pOffset[m_nPartsCnt][INFO_POS_Y],
									&m_pOffset[m_nPartsCnt][INFO_POS_Z]);
							}

							// �I�t�Z�b�g�p�x
							if (strcmp("ROT", pPartsText) == 0)
							{
								fscanf(pFile, "%s %f %f %f",
									&aPartsText[0],
									&m_pOffset[m_nPartsCnt][INFO_ROT_X],
									&m_pOffset[m_nPartsCnt][INFO_ROT_Y],
									&m_pOffset[m_nPartsCnt][INFO_ROT_Z]);
							}
						}

						m_nPartsCnt++;
					}
				}
			}

			// ���[�V�������̓ǂݍ���
			if (strcmp("MOTIONSET", pLoadText) == 0)
			{
				// �L�[�̃J�E���g������
				m_nKeyCnt = 0;

				// ���[�J���ϐ��錾
				char aMotionText[TEXT_NUM] = {};
				char *pMotionText = &aMotionText[0];

				while (strcmp("END_MOTIONSET", pMotionText) != 0)
				{// �I���܂Ń��[�v
					fscanf(pFile, "%s", &aMotionText[0]);

					// ���[�v�̗L��
					if (strcmp("LOOP", pMotionText) == 0)
					{
						int nLoop = 0;
						fscanf(pFile, "%s %d", &aMotionText[0], &nLoop);
						
						if (nLoop != 0)
						{
							m_bLoop[m_nMotionCnt] = true;
						}
					}

					// �L�[��
					if (strcmp("NUM_KEY", pMotionText) == 0)
					{
						// �L�[���̓ǂݍ���
						fscanf(pFile, "%s %d", &aMotionText[0], &m_nNumKey[m_nMotionCnt]);

						// �t���[�����̓��I�m��
						m_pFrame[m_nMotionCnt] = new int[m_nNumKey[m_nMotionCnt]];

						// �L�[�̐������̓��I�m��
						m_pKey[m_nMotionCnt] = new float**[m_nNumKey[m_nMotionCnt]];

						for (int nCntModel = 0; nCntModel < m_nNumKey[m_nMotionCnt]; nCntModel++)
						{
							// �p�[�c�������m��
							m_pKey[m_nMotionCnt][nCntModel] = new float*[m_nNumParts];

							for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
							{
								// �L�[�v�f�������m��
								m_pKey[m_nMotionCnt][nCntModel][nCnt] = new float[CMotionPlayer::KEY_MAX];
							}
						}				
					}

					// �L�[���
					if (strcmp("KEYSET", pMotionText) == 0)
					{
						// ���f���J�E���g������
						m_nPartsCnt = 0;

						// ���[�J���ϐ��錾
						char aKeyText[TEXT_NUM] = {};
						char *pKeyText = &aKeyText[0];

						while (strcmp("END_KEYSET", pKeyText) != 0)
						{
							// �L�[���̓ǂݍ���
							fscanf(pFile, "%s", &aKeyText[0]);

							// �t���[�����̓ǂݍ���
							if (strcmp("FRAME", pKeyText) == 0)
							{
								fscanf(pFile, "%s %d", &aKeyText[0], &m_pFrame[m_nMotionCnt][m_nKeyCnt]);
							}

							// �L�[�v�f�̓ǂݍ���
							if (strcmp("KEY", pKeyText) == 0)
							{
								// ���[�J���ϐ��錾
								char aKeyInfoText[TEXT_NUM] = {};
								char *pKeyInfoText = &aKeyInfoText[0];

								while (strcmp("END_KEY", pKeyInfoText) != 0)
								{
									fscanf(pFile, "%s", &aKeyInfoText[0]);

									// �R�����g���̗�O
									if (strcmp(":",pKeyInfoText) == 0)
									{
										m_nPartsCnt--;
										break;
									}

									// �ʒu
									if (strcmp("POS", pKeyInfoText) == 0)
									{
										fscanf(pFile, "%s %f %f %f",
											&aKeyInfoText[0],
											&m_pKey[m_nMotionCnt][m_nKeyCnt][m_nPartsCnt][CMotionPlayer::KEY_POS_X],
											&m_pKey[m_nMotionCnt][m_nKeyCnt][m_nPartsCnt][CMotionPlayer::KEY_POS_Y],
											&m_pKey[m_nMotionCnt][m_nKeyCnt][m_nPartsCnt][CMotionPlayer::KEY_POS_Z]);

										m_pKey[m_nMotionCnt][m_nKeyCnt][m_nPartsCnt][CMotionPlayer::KEY_POS_X] += m_pOffset[m_nPartsCnt][CMotionPlayer::KEY_POS_X];
										m_pKey[m_nMotionCnt][m_nKeyCnt][m_nPartsCnt][CMotionPlayer::KEY_POS_Y] += m_pOffset[m_nPartsCnt][CMotionPlayer::KEY_POS_Y];
										m_pKey[m_nMotionCnt][m_nKeyCnt][m_nPartsCnt][CMotionPlayer::KEY_POS_Z] += m_pOffset[m_nPartsCnt][CMotionPlayer::KEY_POS_Z];
									}												 

									// �p�x
									if (strcmp("ROT", pKeyInfoText) == 0)
									{
										fscanf(pFile, "%s %f %f %f",
											&aKeyInfoText[0],
											&m_pKey[m_nMotionCnt][m_nKeyCnt][m_nPartsCnt][CMotionPlayer::KEY_ROT_X],
											&m_pKey[m_nMotionCnt][m_nKeyCnt][m_nPartsCnt][CMotionPlayer::KEY_ROT_Y],
											&m_pKey[m_nMotionCnt][m_nKeyCnt][m_nPartsCnt][CMotionPlayer::KEY_ROT_Z]);

										m_pKey[m_nMotionCnt][m_nKeyCnt][m_nPartsCnt][CMotionPlayer::KEY_ROT_X] += m_pOffset[m_nPartsCnt][CMotionPlayer::KEY_ROT_X];
										m_pKey[m_nMotionCnt][m_nKeyCnt][m_nPartsCnt][CMotionPlayer::KEY_ROT_Y] += m_pOffset[m_nPartsCnt][CMotionPlayer::KEY_ROT_Y];
										m_pKey[m_nMotionCnt][m_nKeyCnt][m_nPartsCnt][CMotionPlayer::KEY_ROT_Z] += m_pOffset[m_nPartsCnt][CMotionPlayer::KEY_ROT_Z];
									}
								}

								// ���f���̃J�E���g
								m_nPartsCnt++;
							}
						}

						// �L�[���̃J�E���g
						m_nKeyCnt++;
					}
				}

				// ���[�V�������̃J�E���g
				m_nMotionCnt++;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
		return;
	}
}

//==============================================================================
// �f�[�^�̔j��
//==============================================================================
void CTextDataPlayer::Unload(void)
{
	// �e�L�X�g�f�[�^�̔j��
	if (m_pFileModelName != NULL)
	{
		delete[] m_pFileModelName;
		m_pFileModelName = NULL;
	}

	if (m_pFileModelNameLoad != NULL)
	{
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			delete[] m_pFileModelNameLoad[nCnt];
		}

		delete[] m_pFileModelNameLoad;
		m_pFileModelNameLoad = NULL;
	}

	// �C���f�b�N�X�̔j��
	if (m_pIdx != NULL)
	{
		delete[] m_pIdx;
		m_pIdx = NULL;
	}

	// �e�C���f�b�N�X�̔j��
	if (m_pParentIdx != NULL)
	{
		delete[] m_pParentIdx;
		m_pParentIdx = NULL;
	}

	// �I�t�Z�b�g�̔j��
	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_pOffset != NULL)
		{
			delete[] m_pOffset[nCnt];
			m_pOffset = NULL;
		}
	}

	// �L�[���̔j��
	for (int nCntMotion = 0; nCntMotion < CMotionPlayer::MOTIONTYPE_MAX; nCntMotion++)
	{
		if (m_pKey[nCntMotion] != NULL)
		{
			for (int nCntKey = 0; nCntKey < m_nNumKey[nCntMotion]; nCntKey++)
			{
				for (int nCntParts = 0; nCntParts < CMotionPlayer::KEY_MAX; nCntParts++)
				{
					delete[] m_pKey[nCntMotion][nCntKey][nCntParts];
				}

				delete[] m_pKey[nCntMotion][nCntKey];
			}

			delete[] m_pKey[nCntMotion];
			m_pKey[nCntMotion] = NULL;
		}
	}
}

//==============================================================================
// �v���C���[�f�[�^�̐���
//==============================================================================
CTextDataPlayer *CTextDataPlayer::Create(void)
{
	// �v���C���[�f�[�^�̓ǂݍ���
	CTextDataPlayer *pDataPlayer;
	pDataPlayer = new CTextDataPlayer;

	// �f�[�^�̃��[�h
	if (pDataPlayer != NULL)
	{
		pDataPlayer->LoadData();
	}

	return pDataPlayer;
}