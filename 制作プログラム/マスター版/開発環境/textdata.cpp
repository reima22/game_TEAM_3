//==============================================================================
//
// �e�L�X�g�f�[�^�Ǘ��ktextdata.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "textdata.h"
#include "textdata_meshfield.h"
#include "textdata_object.h"
#include "textdata_pause.h"
#include "textdata_player.h"
#include "textdata_rankingselect.h"
#include "textdata_Terrain.h"
#include "textdata_texture.h"
#include "stdio.h"

// �ÓI�����o�ϐ��錾
char *CTextData::m_pFileName[TEXTDATA_MAX] =
{
	{ "data/TEXT/systemdata.txt" },			// ���[���Ǘ�
	{ "data/TEXT/playermen.txt" },			// �v���C���[�f�[�^
	{ "data/TEXT/texturedata.txt" },		// �e�N�X�`���f�[�^
	{ "data/TEXT/pausedata.txt" },			// �|�[�Y�|���S�����
	{ "data/TEXT/ranking_selectdata.txt" },	// �����L���O�I���f�[�^���
	{ "data/TEXT/terraindata.txt" },		// ���b�V���n�`�f�[�^
	{ "data/TEXT/meshfielddata.txt" },		// �N���̂��郁�b�V���f�[�^
	{ "data/TEXT/sounddata.txt" },			// �T�E���h�f�[�^
};

char *CTextData::m_pFileNameObj[CTextDataObject::STAGEINFO_MAX] =
{
	{ "data/TEXT/StageObject/00_valley_objdata.txt" },		// �k�J�X�e�[�W�I�u�W�F�N�g�f�[�^
	{ "data/TEXT/StageObject/01_sea_objdata.txt" },			// �C�m�X�e�[�W�I�u�W�F�N�g�f�[�^
	{ "data/TEXT/StageObject/02_lava_objdata.txt" },		// �n��X�e�[�W�I�u�W�F�N�g�f�[�^
};

char *CTextData::m_pFileNameRanking[CTextDataObject::STAGEINFO_MAX] =
{
	{ "data/TEXT/RANKING/00_valley_ranking.txt" },		// �k�J�X�e�[�W�����L���O�f�[�^
	{ "data/TEXT/RANKING/01_ocean_ranking.txt" },		// �C�m�X�e�[�W�����L���O�f�[�^
	{ "data/TEXT/RANKING/02_lava_ranking.txt" },		// �n��X�e�[�W�����L���O�f�[�^
};

CTextDataPlayer *CTextData::m_pDataPlayer = NULL;					// �v���C���[�f�[�^�̃|�C���^
CTextDataObject *CTextData::m_pDataObject[STAGEINFO_MAX] = {};		// �X�e�[�W�I�u�W�F�N�g�f�[�^�̃|�C���^
CTextDataTexture *CTextData::m_pDataTexture = NULL;					// �e�N�X�`���f�[�^�̃|�C���^
CTextDataPause *CTextData::m_pDataPause = NULL;						// �|�[�Y�f�[�^�̃|�C���^
CTextDataTerrain *CTextData::m_pDataTerrain = NULL;					// ���S���胁�b�V���n�`�̃f�[�^�|�C���^
CTextDataMeshfield *CTextData::m_pDataMeshfield = NULL;				// �N���n�`�̃f�[�^�|�C���^
CTextDataRanking *CTextData::m_apDataRanking[STAGEINFO_MAX] = {};	// �����L���O�f�[�^
CTextDataRankingSelect *CTextData::m_pDataRankingSelect = NULL;		// �����L���O�I���f�[�^�̃|�C���^
CTextDataSound *CTextData::m_pDataSound = NULL;						// �T�E���h�f�[�^�|�C���^

																	//==============================================================================
																	// �R���X�g���N�^
																	//==============================================================================
CTextData::CTextData()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTextData::~CTextData()
{

}

//==============================================================================
// ��������
//==============================================================================
CTextData *CTextData::Create(void)
{
	// ���[�J���ϐ��錾
	CTextData *pTextData;
	pTextData = new CTextData;	// �C���X�^���X����

								// �e�L�X�g�f�[�^
	if (pTextData != NULL)
	{
		// �e�L�X�g�f�[�^�̓ǂݍ���
		pTextData->LoadTextAll();
	}

	return pTextData;
}

//==============================================================================
// �e�L�X�g�f�[�^�̑S�ǂݍ���
//==============================================================================
void CTextData::LoadTextAll(void)
{
	// �v���C���[�f�[�^�̐���
	m_pDataPlayer = CTextDataPlayer::Create();

	// �I�u�W�F�N�g�f�[�^�̐���
	for (int nCntStage = 0; nCntStage < CTextDataObject::STAGEINFO_MAX; nCntStage++)
	{
		m_pDataObject[nCntStage] = CTextDataObject::Create((STAGEINFO)nCntStage);
	}

	// �e�N�X�`���f�[�^�̐���
	m_pDataTexture = CTextDataTexture::Create();

	// �|�[�Y�f�[�^�̐���
	m_pDataPause = CTextDataPause::Create();

	// �����L���O�I���f�[�^�̐���
	m_pDataRankingSelect = CTextDataRankingSelect::Create();

	// �n�`�f�[�^�̐���
	m_pDataTerrain = CTextDataTerrain::Create();

	// ���b�V���f�[�^
	m_pDataMeshfield = CTextDataMeshfield::Create();
}

//==============================================================================
// �e�L�X�g�f�[�^�̑S�ǂݍ���
//==============================================================================
void CTextData::UninitAll(void)
{
	// �v���C���[�f�[�^�̔j��
	if (m_pDataPlayer != NULL)
	{
		m_pDataPlayer->Unload();
		m_pDataPlayer = NULL;
	}

	// �I�u�W�F�N�g�f�[�^�̔j��
	for (int nCntObj = 0; nCntObj < CTextDataObject::STAGEINFO_MAX; nCntObj++)
	{
		if (m_pDataObject[nCntObj] != NULL)
		{
			m_pDataObject[nCntObj]->Unload();
			m_pDataObject[nCntObj] = NULL;
		}
	}

	// �e�N�X�`���f�[�^�̔j��
	if (m_pDataTexture != NULL)
	{
		m_pDataTexture->Unload();
		m_pDataTexture = NULL;
	}

	// �|�[�Y�f�[�^�̔j��
	if (m_pDataPause != NULL)
	{
		m_pDataPause->Unload();
		m_pDataPause = NULL;
	}

	// �����L���O�I���f�[�^�̔j��
	if (m_pDataRankingSelect != NULL)
	{
		m_pDataRankingSelect->Unload();
		m_pDataRankingSelect = NULL;
	}

	// ���S����n�`�f�[�^�̔j��
	if (m_pDataTerrain != NULL)
	{
		m_pDataTerrain->Unload();
		m_pDataTerrain = NULL;
	}

	// �N���n�`�f�[�^�̔j��
	if (m_pDataMeshfield != NULL)
	{
		m_pDataMeshfield->Unload();
		m_pDataMeshfield = NULL;
	}
}