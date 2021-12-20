//==============================================================================
//
// �r���{�[�h�`�揈���ksceneBillboard.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene3D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "fade.h"
#include "effect.h"

int CEffect::m_nNum = 0;
//==============================================================================
// �R���X�g���N�^
//==============================================================================
CEffect::CEffect(int nPriority) : CScene(nPriority)
{
	//m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nIdx = m_nNum;
	m_nNum++;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CEffect::~CEffect()
{

}

//==============================================================================
// �r���{�[�h�̏���������
//==============================================================================
HRESULT CEffect::Init(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// �e���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �e�N�X�`�����_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �G�t�F�N�g���̐ݒ�
	SetEffect();

	return S_OK;
}

//==============================================================================
// �|���S���`��̏I������
//==============================================================================
void CEffect::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �e�N�X�`���̊J��
	//if (m_pTexture != NULL)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = NULL;
	//}

	m_nNum--;

	Release();
}

//==============================================================================
// �|���S���`��̍X�V����
//==============================================================================
void CEffect::Update(void)
{  
	// ���_���̐ݒ�
	SetVertex();

	// �G�t�F�N�g�̋���
	EffectMove();
}

//==============================================================================
// �|���S���`��̕`�揈��
//==============================================================================
void CEffect::Draw(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���C�g���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�e�X�g�̍X�V
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���Z�����ɂ��A���t�@�u�����f�B���O
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �r���[�}�g���b�N�X�̎擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		2);						// �`�悷��v���~�e�B�u��

	// �ʏ�̃A���t�@�u�����f�B���O
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���C�g���I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==============================================================================
// �r���{�[�h�̐���
//==============================================================================
CEffect *CEffect::Create(void)
{
	// ���[�J���ϐ��錾
	CEffect *pEffect;
	pEffect = new CEffect;

	// ������
	if (pEffect != NULL)
	{
		pEffect->Init();
	}

	// �Ԃ��l
	return pEffect;
}

//==============================================================================
// �G�t�F�N�g�̐ݒ�
//==============================================================================
void CEffect::SetEffect(void)
{
	// ���[�J���ϐ��錾
	CTexture *pTexture = CManager::GetTexture();

	switch (m_effectType)
	{
	case EFFECTTYPE_SANDSMOKE:	// ����

		m_pTexture = pTexture->GetAddress("EFFECT");
		SetColor(D3DXCOLOR(0.34f, 0.47f, 0.21f, 1.0f));

		break;
	}
}

//==============================================================================
// ���_���̐ݒ�
//==============================================================================
void CEffect::SetVertex(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(-m_size.x, +m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(+m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, +m_size.y, 0.0f);

	// �e���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================================================
// �G�t�F�N�g�̋���
//==============================================================================
void CEffect::EffectMove(void)
{
	switch (m_effectType)
	{
	case EFFECTTYPE_SANDSMOKE:
		m_move = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
		m_size += D3DXVECTOR2(0.5f, 0.5f);
		m_fAlphaDown = 0.01f;

		break;
	}

	// �����x�̒ቺ
	m_col.a -= m_fAlphaDown;

	m_pos += m_move;
}

//==============================================================================
// �e�N�X�`���̏��ݒ�
//==============================================================================
void CEffect::SetTexture(char *pText)
{
	// ���[�J���ϐ��錾
	CTexture *pTexture = CManager::GetTexture();

	// �e�N�X�`���̊��蓖��
	m_pTexture = pTexture->GetAddress(pText);
}


/*�����G�t�F�N�g*/

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CEffectSand::CEffectSand()
{
	//m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CEffectSand::~CEffectSand()
{

}

//==============================================================================
// �r���{�[�h�̏���������
//==============================================================================
HRESULT CEffectSand::Init(D3DXVECTOR3 pos)
{
	if (m_pEffect == NULL)
	{
		m_pEffect = CEffect::Create();
		m_pEffect->SetPosition(pos);
		m_pEffect->SetMove(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		m_pEffect->SetSize(D3DXVECTOR2(1.0f, 1.0f));
		m_pEffect->SetColor(D3DXCOLOR(0.34f, 0.23f, 0.13f, 1.0f));
		m_pEffect->SetTexture("EFFECT");
		m_pEffect->SetType(EFFECTTYPE_SANDSMOKE);
		m_pEffect->SetAlphaDown(0.01f);
	}

	return S_OK;
}

//==============================================================================
// �|���S���`��̏I������
//==============================================================================
void CEffectSand::Uninit(void)
{
	if (m_pEffect != NULL)
	{
		m_pEffect->Uninit();
		m_pEffect = NULL;
	}

	Release();
}

//==============================================================================
// �|���S���`��̍X�V����
//==============================================================================
void CEffectSand::Update(void)
{
	if (m_pEffect != NULL)
	{
		// �j������
		if (m_pEffect->GetColor().a <= 0.0f)
		{
			Uninit();
			return;
		}
	}
}

//==============================================================================
// �|���S���`��̕`�揈��
//==============================================================================
void CEffectSand::Draw(void)
{
}

//==============================================================================
// �G�t�F�N�g�̐���
//==============================================================================
CEffectSand *CEffectSand::Create(D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	CEffectSand *pEffectSand;
	pEffectSand = new CEffectSand;

	// ������
	if (pEffectSand != NULL)
	{
		pEffectSand->Init(pos);
	}

	// �Ԃ��l
	return pEffectSand;
}