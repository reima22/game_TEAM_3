//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "fade.h"
#include "Manager.h"

//*****************************************************************************
// �t�F�[�h�N���X
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade::CFade()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pVertex = NULL;
	m_fAlpha = 1.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CFade::Init(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(CScene2D::VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���ă|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVertex, 0);

	// ���_����ݒ�
	// �ʒu
	m_pVertex[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0);
	m_pVertex[1].pos = D3DXVECTOR3(0, 0, 0);
	m_pVertex[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	m_pVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0);

	// rhw
	m_pVertex[0].rhw = 1.0f;
	m_pVertex[1].rhw = 1.0f;
	m_pVertex[2].rhw = 1.0f;
	m_pVertex[3].rhw = 1.0f;

	// �F
	m_pVertex[0].col = D3DXCOLOR(0, 1.0f, 0, m_fAlpha);
	m_pVertex[1].col = D3DXCOLOR(0, 1.0f, 0, m_fAlpha);
	m_pVertex[2].col = D3DXCOLOR(0, 1.0f, 0, m_fAlpha);
	m_pVertex[3].col = D3DXCOLOR(0, 1.0f, 0, m_fAlpha);

	// �e�N�X�`��
	m_pVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	m_pVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	m_pVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	m_pVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�o�b�t�@�A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CFade::Uninit(void)
{
	// ���_�o�b�t�@���J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �e�N�X�`���J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �X�V
//=============================================================================
void CFade::Update(void)
{
	// �����x�Ə�Ԃ̊Ǘ�
	switch (m_fadeState)
	{
	case CFade::FADE_IN:
		m_fAlpha -= FADE_SPEED;
		if (m_fAlpha < 0.0f)
		{
			m_fAlpha = 0.0f;
			m_fadeState = CFade::FADE_NONE;
		}
		break;

	case CFade::FADE_OUT:
		m_fAlpha += FADE_SPEED;
		if (m_fAlpha > 1.0f)
		{
			m_fAlpha = 1.0f;
			m_fadeState = CFade::FADE_IN;
			CManager::SetMode(m_modeNext);
		}
		break;

	default:
		break;
	}

	// �J���[�̍X�V
	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVertex, 0);

	//���_�J���[�̐ݒ�
	m_pVertex[0].col = D3DXCOLOR(0, 0, 0, m_fAlpha);
	m_pVertex[1].col = D3DXCOLOR(0, 0, 0, m_fAlpha);
	m_pVertex[2].col = D3DXCOLOR(0, 0, 0, m_fAlpha);
	m_pVertex[3].col = D3DXCOLOR(0, 0, 0, m_fAlpha);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`��
//=============================================================================
void CFade::Draw(void)
{
	if (m_fadeState != CFade::FADE_NONE)
	{
		// �f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CScene2D::VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->SetTexture(0, m_pTexture);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=============================================================================
// �t�F�[�h�C��
//=============================================================================
void CFade::FadeIN(void)
{
	if (m_fadeState != FADE_IN)
	{
		m_fAlpha = 1.0f;
		m_fadeState = CFade::FADE_IN;
	}
}

//=============================================================================
// �t�F�[�h�A�E�g
//=============================================================================
void CFade::FadeOUT(CManager::MODE modeNext)
{
	if (m_fadeState != FADE_OUT)
	{
		m_fAlpha = 0.0f;
		m_fadeState = CFade::FADE_OUT;
		m_modeNext = modeNext;
	}
}