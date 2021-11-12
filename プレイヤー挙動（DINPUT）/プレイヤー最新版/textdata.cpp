//==============================================================================
//
// �e�L�X�g�f�[�^�Ǘ��ktextdata.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "textdata.h"
#include "textdata_player.h"
#include "textdata_system.h"
#include "textdata_object.h"
#include "textdata_texture.h"
#include "textdata_pause.h"
#include "textdata_Terrain.h"
#include "stdio.h"

// �ÓI�����o�ϐ��錾
char *CTextData::m_pFileName[TEXTDATA_MAX] =
{
	{ "data/TEXT/ranking.txt" },	// �����L���O
	{ "data/TEXT/systemdata.txt" },	// ���[���Ǘ�
	{ "data/TEXT/playermen.txt" },	// �v���C���[�f�[�^
	{ "data/TEXT/objectdata.txt" },	// 3D�I�u�W�F�N�g�f�[�^
	{ "data/TEXT/texturedata.txt" },	// �e�N�X�`���f�[�^
	{ "data/TEXT/pausedata.txt" },		// �|�[�Y�|���S�����
	{ "data/TEXT/TerrainData.txt"},			
};

CTextDataPlayer *CTextData::m_pDataPlayer = NULL;
CTextDataObject *CTextData::m_pDataObject = NULL;
CTextDataTexture *CTextData::m_pDataTexture = NULL;
CTextDataPause *CTextData::m_pDataPause = NULL;
CTextDataTerrain *CTextData::m_pDataTerrain = NULL;
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
	m_pDataObject = CTextDataObject::Create();

	// �e�N�X�`���f�[�^�̐���
	m_pDataTexture = CTextDataTexture::Create();

	// �|�[�Y�f�[�^�̐���
	m_pDataPause = CTextDataPause::Create();

	// �n�`�f�[�^�̐���
	m_pDataTerrain = CTextDataTerrain::Create();

	// ���[���̃f�[�^�ǂݍ���
	CTextDataSystem::LoadData();
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
	if (m_pDataObject != NULL)
	{
		m_pDataObject->Unload();
		m_pDataObject = NULL;
	}
}