//==============================================================================
//
// �e�N�X�`���Ǘ��ktexture.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "textdata_texture.h"

// �ÓI�����o�ϐ��錾
//LPDIRECT3DTEXTURE9 CTexture::m_pTexture[TEXTYPE_MAX] = {};
//char *CTexture::m_pFileName[TEXTYPE_MAX] = 
//{
	//{""},										// �e�N�X�`������
	//{ "data\\TEXTURE\\player_cloth00.jpg" },	// �v���C���[�e�N�X�`��
	//{ "data\\TEXTURE\\player_cloth01.jpg" },	// �v���C���[�e�N�X�`��
	//{ "data\\TEXTURE\\block.jpg"},				// �u���b�N
	//{ "data\\TEXTURE\\title_bg.png" },			// �^�C�g���w�i
	//{ "data\\TEXTURE\\title000.png" },			// �^�C�g�����S
	//{ "data\\TEXTURE\\press_enter.png" },		// �^�C�g���G���^�[�T�C��
	//{ "data\\TEXTURE\\result_bg.png" },			// ���U���g�w�i
	//{ "data\\TEXTURE\\result_logo000.png" },	// ���U���g���S
	//{ "data\\TEXTURE\\ranking_bg.png" },		// �����L���O�w�i
	//{ "data\\TEXTURE\\ranking_logo.png" },		// �����L���O���S	
	//{ "data\\TEXTURE\\ranking_rank.png" },		// �����L���O����
	//{ "data\\TEXTURE\\yourscore.png" },			// �����L���O��ʂ̃��U���g�X�R�A���S
	//{ "data\\TEXTURE\\number000.png" },			// �i���o�[
	//{ "data\\TEXTURE\\explosion000.png" },		// ����
	//{ "data\\TEXTURE\\effect000.jpg" },			// �G�t�F�N�g
	//{ "data\\TEXTURE\\pause_BS.png" },			// �|�[�Y�x�[�X
	//{ "data\\TEXTURE\\continue_logo.png" },		// �|�[�Y�R���e�j���[
	//{ "data\\TEXTURE\\retry_logo.png" },		// �|�[�Y���g���C
	//{ "data\\TEXTURE\\quit_logo.png" },			// �|�[�Y�I�� 
	//{ "data\\TEXTURE\\tutorial00.jpg" },		// �`���[�g���A��0 
	//{ "data\\TEXTURE\\tutorial01.jpg" },		// �`���[�g���A��1
	//{ "data\\TEXTURE\\tutorial02.jpg" },		// �`���[�g���A��2
	//{ "data\\TEXTURE\\window_effect.png" },		// ��ʃG�t�F�N�g
	//{ "data\\TEXTURE\\easy.png" },				// easy
	//{ "data\\TEXTURE\\normal.png" },			// normal
	//{ "data\\TEXTURE\\hard.png" },				// hard
	//{ "data\\TEXTURE\\meteor.jpg"},				// 覐΃��f���̃e�N�X�`��
	//{ "data\\TEXTURE\\panel.jpg" },				// �p�l�����f���̃e�N�X�`��
//};

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTexture::CTexture()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTexture::~CTexture()
{

}

//==============================================================================
// �e�N�X�`���f�[�^�̑S�ǂݍ���
//==============================================================================
HRESULT CTexture::LoadAll(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���f�[�^�̎擾
	CTextDataTexture *pDataTexture;
	pDataTexture = CTextData::GetDataTexture();

	// �e�N�X�`���ő吔�̎擾
	m_nTexMax = pDataTexture->GetNumTexture();

	// �C���X�^���X����
	m_pTexture = (LPDIRECT3DTEXTURE9)new LPDIRECT3DTEXTURE9[m_nTexMax];

	m_pFileName = new char*[m_nTexMax];

	for (int nCnt = 0; nCnt < m_nTexMax; nCnt++)
	{
		m_pFileName[nCnt] = pDataTexture->GetFileName(nCnt);

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			pDevice,
			m_pFileName[nCnt],
			(LPDIRECT3DTEXTURE9*)&m_pTexture[nCnt]);
	}

	return S_OK;
}

//==============================================================================
// �e�N�X�`���f�[�^�̑S�j��
//==============================================================================
void CTexture::UnloadAll(void)
{
	for (int nCnt = 0; nCnt < m_nTexMax; nCnt++)
	{
		// �S�Ẵe�N�X�`���̔j��
		if (*(LPDIRECT3DTEXTURE9*)&m_pTexture[nCnt] != NULL)
		{
			(*(LPDIRECT3DTEXTURE9*)&m_pTexture[nCnt])->Release();
			*(LPDIRECT3DTEXTURE9*)&m_pTexture[nCnt] = NULL;
		}

		// �t�@�C�����̔j��
		if (m_pFileName[nCnt] != NULL)
		{
			m_pFileName[nCnt] = NULL;
		}
	}

	// �������̔j��
	delete[] m_pTexture;
	m_pTexture = NULL;

	delete[] m_pFileName;
	m_pFileName = NULL;
}

// �e�N�X�`���N���X�̐�������
CTexture *CTexture::Create(void)
{
	// ���[�J���ϐ��錾
	CTexture *pTexture;
	pTexture = new CTexture;

	if (pTexture != NULL)
	{
		pTexture->LoadAll();
	}

	return pTexture;
}

//==============================================================================
// 3D���f���ւ̊��蓖��
//==============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress3D(char *pTexFilename)
{
	for (int nCntTex = 0; nCntTex < m_nTexMax; nCntTex++)
	{
		// �Y������e�N�X�`���̊��o��
		if (strcmp(m_pFileName[nCntTex], pTexFilename) == 0)
		{
			// �e�N�X�`������Ԃ�
			return *(LPDIRECT3DTEXTURE9*)&m_pTexture[nCntTex];
		}
	}

	return NULL;
}