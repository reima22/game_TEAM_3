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
	m_pDataTexture = CTextData::GetDataTexture();

	// �e�N�X�`���ő吔�̎擾
	m_nTexMax = m_pDataTexture->GetNumTexture();

	// �C���X�^���X����
	m_pTexture = (LPDIRECT3DTEXTURE9)new LPDIRECT3DTEXTURE9[m_nTexMax];

	// �p�X�̓��I�m��
	m_pFileName = new char*[m_nTexMax];

	for (int nCnt = 0; nCnt < m_nTexMax; nCnt++)
	{
		m_pFileName[nCnt] = m_pDataTexture->GetFileName(nCnt);

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

//==============================================================================
// �e�N�X�`���N���X�̐�������
//==============================================================================
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
// �e�N�X�`���̊��蓖��
//==============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(char *pTypeCheck)
{
	for (int nCntTex = 0; nCntTex < m_nTexMax; nCntTex++)
	{
		if (strcmp(pTypeCheck, m_pDataTexture->GetTypeCheck(nCntTex)) == 0)
		{// �Y������e�N�X�`��
			return *(LPDIRECT3DTEXTURE9*)&m_pTexture[nCntTex];
		}
	}

	return NULL;
}

//==============================================================================
// �e�N�X�`���̊��蓖��(���l)
//==============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddressNum(int nTexNum)
{
	if (&m_pTexture[nTexNum] != NULL)
	{
		return *(LPDIRECT3DTEXTURE9*)&m_pTexture[nTexNum];
	}

	return NULL;
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