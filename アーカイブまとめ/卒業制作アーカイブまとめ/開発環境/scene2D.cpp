//==============================================================================
//
// 2D�|���S���`�揈���kscene2D.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "fade.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "texture.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_size = VECTOR2_NULL;
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_bZbuff = false;
	m_bAlphaBlend = false;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CScene2D::~CScene2D()
{

}

//==============================================================================
// �|���S���`��̏���������
//==============================================================================
HRESULT CScene2D::Init(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_����ݒ�
	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �v���C���[�̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(
		m_pos.x + sinf(-m_fAngle) * m_fLength,
		m_pos.y + cosf(-m_fAngle) * m_fLength,
		0.0f);
	pVtx[1].pos = D3DXVECTOR3(
		m_pos.x + sinf(m_fAngle - D3DX_PI) * m_fLength,
		m_pos.y + cosf(m_fAngle - D3DX_PI) * m_fLength,
		0.0f);
	pVtx[2].pos = D3DXVECTOR3(
		m_pos.x + sinf(m_fAngle) * m_fLength,
		m_pos.y + cosf(m_fAngle) * m_fLength,
		0.0f);
	pVtx[3].pos = D3DXVECTOR3(
		m_pos.x + sinf(-m_fAngle + D3DX_PI) * m_fLength,
		m_pos.y + cosf(-m_fAngle + D3DX_PI) * m_fLength,
		0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �e���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================================================
// �|���S���`��̏I������
//==============================================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//==============================================================================
// �|���S���`��̍X�V����
//==============================================================================
void CScene2D::Update(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// ���_���̍X�V
	if (m_pVtxBuff != NULL)
	{
		// ���_�o�b�t�@�����b�N����
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �|���S���̒��_���W�̍X�V
		pVtx[0].pos = D3DXVECTOR3(
			m_pos.x + sinf(-m_fAngle + m_rot.z) * m_fLength,
			m_pos.y + cosf(-m_fAngle + m_rot.z) * m_fLength,
			0.0f);
		pVtx[1].pos = D3DXVECTOR3(
			m_pos.x + sinf(m_fAngle - D3DX_PI + m_rot.z) * m_fLength,
			m_pos.y + cosf(m_fAngle - D3DX_PI + m_rot.z) * m_fLength,
			0.0f);
		pVtx[2].pos = D3DXVECTOR3(
			m_pos.x + sinf(m_fAngle + m_rot.z) * m_fLength,
			m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength,
			0.0f);
		pVtx[3].pos = D3DXVECTOR3(
			m_pos.x + sinf(-m_fAngle + D3DX_PI + m_rot.z) * m_fLength,
			m_pos.y + cosf(-m_fAngle + D3DX_PI + m_rot.z) * m_fLength,
			0.0f);

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}

	// �V�[���N���X�ւ̏��
	SetPosition(m_pos);
	SetRotation(m_rot);
}

//==============================================================================
// �|���S���`��̕`�揈��
//==============================================================================
void CScene2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	if (m_bZbuff == true)
	{
		// Z�e�X�g�̍X�V
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}

	if (m_bAlphaBlend == true)
	{
		// ���Z�����ɂ��A���t�@�u�����f�B���O
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		2);						// �`�悷��v���~�e�B�u��

	if (m_bZbuff == true)
	{
		// ���ɖ߂�
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

	if (m_bAlphaBlend == true)
	{
		// �ʏ�̃A���t�@�u�����f�B���O
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//==============================================================================
// 2D�̐���
//==============================================================================
CScene2D *CScene2D::Create(void)
{
	// ���[�J���ϐ��錾
	CScene2D *pScene2D;
	pScene2D = new CScene2D;

	// ������
	if (pScene2D != NULL)
	{
		pScene2D->Init();
	}

	return pScene2D;
}

//==============================================================================
// �e�N�X�`���̊��蓖��
//==============================================================================
void CScene2D::BindTexture(char *pTypeCheck)
{
	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture;
	pTexture = CManager::GetTexture();

	m_pTexture = pTexture->GetAddress(pTypeCheck);
}

//==============================================================================
// �e�N�X�`���̊��蓖��(���l)
//==============================================================================
void CScene2D::BindTextureNum(int nTexNum)
{
	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture;
	pTexture = CManager::GetTexture();

	m_pTexture = pTexture->GetAddressNum(nTexNum);
}

//==============================================================================
// �|���S���̃T�C�Y�ݒ�
//==============================================================================
void CScene2D::SetSize(D3DXVECTOR2 size)
{
	m_size = size;

	// �Ίp���̐ݒ�
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y);
	m_fAngle = atan2f(m_size.x, m_size.y);
}

//==============================================================================
// �e�N�X�`�����W�̐ݒ�
//==============================================================================
void CScene2D::SetTex(int nCutX, int nCutY, int nPatternX, int nPatternY, float fTexX, float fTexY)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// ���_���̍X�V
	if (m_pVtxBuff != NULL)
	{
		// ���_�o�b�t�@�����b�N����
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(
			nPatternX * (1.0f / nCutX) + fTexX,
			nPatternY * (1.0f / nCutY) + (1.0f / nCutY) + fTexY);

		pVtx[1].tex = D3DXVECTOR2(
			nPatternX * (1.0f / nCutX) + fTexX, 
			nPatternY * (1.0f / nCutY) + fTexY);

		pVtx[2].tex = D3DXVECTOR2(
			nPatternX * (1.0f / nCutX) + (1.0f / nCutX) + fTexX, 
			nPatternY * (1.0f / nCutY) + (1.0f / nCutY) + fTexY);

		pVtx[3].tex = D3DXVECTOR2(
			nPatternX * (1.0f / nCutX) + (1.0f / nCutX) + fTexX,
			nPatternY * (1.0f / nCutY) + fTexY);

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//==============================================================================
// �e�N�X�`�����W�̐ݒ�
//==============================================================================
void CScene2D::SetTexUV(D3DXVECTOR2 Vertex_0, D3DXVECTOR2 Vertex_1, D3DXVECTOR2 Vertex_2, D3DXVECTOR2 Vertex_3)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	if (m_pVtxBuff != NULL)
	{
		// ���_�o�b�t�@�����b�N���ă|�C���^�擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����W�ݒ�
		pVtx[0].tex = Vertex_0;
		pVtx[1].tex = Vertex_1;
		pVtx[2].tex = Vertex_2;
		pVtx[3].tex = Vertex_3;

		// ���_�o�b�t�@�A�����b�N
		m_pVtxBuff->Unlock();
	}
}

//==============================================================================
// �F���̐ݒ�
//==============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// ���_���̍X�V
	if (m_pVtxBuff != NULL)
	{
		// ���_�o�b�t�@�����b�N����
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����_���̐ݒ�
		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;
		pVtx[3].col = col;

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}