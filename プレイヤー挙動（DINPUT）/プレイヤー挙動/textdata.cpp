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
#include "stdio.h"

// �ÓI�����o�ϐ��錾
char *CTextData::m_pFileName[TEXTDATA_MAX] =
{
	{ "data/TEXT/ranking.txt" },	// �����L���O
	{ "data/TEXT/systemdata.txt" },	// ���[���Ǘ�
	{ "data/TEXT/playermen.txt" },	// �v���C���[�f�[�^
	{ "data/TEXT/objectdata.txt" },	// 3D�I�u�W�F�N�g�f�[�^
};

CTextDataPlayer *CTextData::m_pDataPlayer = NULL;
CTextDataObject *CTextData::m_pDataObject = NULL;

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
	//m_pDataObject = CTextDataObject::Create();

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
		m_pDataPlayer->Uninit();
		m_pDataPlayer = NULL;
	}
	
	// �I�u�W�F�N�g�f�[�^�̔j��
	if (m_pDataObject != NULL)
	{
		m_pDataObject->Uninit();
		m_pDataObject = NULL;
	}
}