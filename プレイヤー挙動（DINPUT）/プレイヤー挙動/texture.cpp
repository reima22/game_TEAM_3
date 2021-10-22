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

// �ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CTexture::m_pTexture[TEXTYPE_MAX] = {};
char *CTexture::m_pFileName[TEXTYPE_MAX] = 
{
	{""},										// �e�N�X�`������
	{ "data\\TEXTURE\\player_cloth00.jpg" },	// �v���C���[�e�N�X�`��
	{ "data\\TEXTURE\\player_cloth01.jpg" },	// �v���C���[�e�N�X�`��
	{ "data\\TEXTURE\\block.jpg"},				// �u���b�N
	{ "data\\TEXTURE\\title_bg.png" },			// �^�C�g���w�i
	{ "data\\TEXTURE\\title000.png" },			// �^�C�g�����S
	{ "data\\TEXTURE\\press_enter.png" },		// �^�C�g���G���^�[�T�C��
	{ "data\\TEXTURE\\result_bg.png" },			// ���U���g�w�i
	{ "data\\TEXTURE\\result_logo000.png" },	// ���U���g���S
	{ "data\\TEXTURE\\ranking_bg.png" },		// �����L���O�w�i
	{ "data\\TEXTURE\\ranking_logo.png" },		// �����L���O���S	
	{ "data\\TEXTURE\\ranking_rank.png" },		// �����L���O����
	{ "data\\TEXTURE\\yourscore.png" },			// �����L���O��ʂ̃��U���g�X�R�A���S
	{ "data\\TEXTURE\\life000.png" },			// ���C�t
	{ "data\\TEXTURE\\item000.png" },			// �A�C�e��0(�g�`�e)
	{ "data\\TEXTURE\\item001.png" },			// �A�C�e��1(�~�T�C��)
	{ "data\\TEXTURE\\item002.png" },			// �A�C�e��2(�t�g�`�e)
	{ "data\\TEXTURE\\item003.png" },			// �A�C�e��3(��)
	{ "data\\TEXTURE\\number000.png" },		// �i���o�[
	{ "data\\TEXTURE\\explosion000.png" },	// ����
	{ "data\\TEXTURE\\effect000.jpg" },		// �G�t�F�N�g
	{ "data\\TEXTURE\\safetyline000.png" },	// �{�[�_�[���C��
	{ "data\\TEXTURE\\pause_BS.png" },		// �|�[�Y�x�[�X
	{ "data\\TEXTURE\\continue_logo.png" },	// �|�[�Y�R���e�j���[
	{ "data\\TEXTURE\\retry_logo.png" },		// �|�[�Y���g���C
	{ "data\\TEXTURE\\quit_logo.png" },		// �|�[�Y�I�� 
	{ "data\\TEXTURE\\tutorial00.jpg" },		// �`���[�g���A��0 
	{ "data\\TEXTURE\\tutorial01.jpg" },		// �`���[�g���A��1
	{ "data\\TEXTURE\\tutorial02.jpg" },		// �`���[�g���A��2
	{ "data\\TEXTURE\\message_window.png" },	// ���b�Z�[�W�E�B���h�E
	{ "data\\TEXTURE\\message_text.png" },	// ���b�Z�[�W�e�L�X�g
	{ "data\\TEXTURE\\warning.png" },			// �x�����
	{ "data\\TEXTURE\\window_effect.png" },	// ��ʃG�t�F�N�g
	{ "data\\TEXTURE\\easy.png" },			// easy
	{ "data\\TEXTURE\\normal.png" },			// normal
	{ "data\\TEXTURE\\hard.png" },			// hard
	{ "data\\TEXTURE\\meteor.jpg"},			// 覐΃��f���̃e�N�X�`��
	{ "data\\TEXTURE\\panel.jpg" },			// �p�l�����f���̃e�N�X�`��
};

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

	for (int nCnt = 1; nCnt < TEXTYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			pDevice,
			m_pFileName[nCnt],
			&m_pTexture[nCnt]);
	}

	return S_OK;
}

//==============================================================================
// �e�N�X�`���f�[�^�̑S�j��
//==============================================================================
void CTexture::UnloadAll(void)
{
	for (int nCnt = 0; nCnt < TEXTYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}

		if (m_pFileName[nCnt] != NULL)
		{
			m_pFileName[nCnt] = NULL;
		}
	}
}

//==============================================================================
// 3D���f���ւ̊��蓖��
//==============================================================================
LPDIRECT3DTEXTURE9 CTexture::BindTex3D(char *pTexFilename)
{
	for (int nCntTex = 0; nCntTex < TEXTYPE_MAX; nCntTex++)
	{
		// �Y������e�N�X�`���̊��o��
		if (strcmp(m_pFileName[nCntTex] ,pTexFilename) == 0)
		{
			// �e�N�X�`������Ԃ�
			return m_pTexture[nCntTex];
		}
	}

	return NULL;
}