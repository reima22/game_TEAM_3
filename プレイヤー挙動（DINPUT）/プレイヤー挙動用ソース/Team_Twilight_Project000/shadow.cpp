//==============================================================================
//
// �e�̕`��kshadow.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "shadow.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	// �o�b�t�@�ւ̃|�C���^
//LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;			// �e�N�X�`���ւ̃|�C���^
//Shadow g_aShadow[MAX_SHADOW];						// �e�̍\����

// �R���X�g���N�^
CShadow::CShadow() 
{

}

// �f�X�g���N�^
CShadow::~CShadow()
{

}

//==============================================================================
// ����������
//==============================================================================
HRESULT CShadow::Init(D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/shadow000.jpg",
		&m_pTexture);

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
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y, m_pos.z - m_fDepth);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y, m_pos.z + m_fDepth);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y, m_pos.z - m_fDepth);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y, m_pos.z + m_fDepth);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// �e���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.85f);
	pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.85f);
	pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.85f);
	pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.85f);

	// �e�N�X�`�����_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CShadow::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void CShadow::Update(void)
{

}

//==============================================================================
// �`�揈��
//==============================================================================
void CShadow::Draw(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���Z�����̐���
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	m_mtxWorld._11 = m_fWidth;
	m_mtxWorld._33 = m_fDepth;

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

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

	// �ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


// �e�̐���
CShadow *CShadow::Create(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	// ���[�J���ϐ��錾
	CShadow *pShadow;
	pShadow = new CShadow;

	if (pShadow != NULL)
	{
		pShadow->SetWidth(fWidth);
		pShadow->SetDepth(fDepth);
		pShadow->Init(pos);
	}

	return pShadow;
}

//==============================================================================
// �e�̐ݒ�
//==============================================================================
//int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth)
//{
//	// ���[�J���ϐ��錾
//	Shadow *pShadow;
//	pShadow = &g_aShadow[0];
//	int nIdx = -1;
//
//	// �e�̐ݒ�
//	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++, pShadow++)
//	{
//		if (pShadow->bUse == false)
//		{
//			pShadow->pos = pos;			// �ʒu�̐ݒ�
//
//			pShadow->fWidth = fWidth;	// ���̐ݒ�
//
//			pShadow->fDepth = fDepth;	// ���s�̐ݒ�
//
//			pShadow->bUse = true;		// �g�p��Ԃւ̈ڍs
//
//			nIdx = nCnt;				// �C���f�b�N�X�ւ̑��
//
//			break;
//		}
//	}
//
//	return nIdx;	// nIdx�ԖڂƂ��ĕԂ�
//}

////==============================================================================
//// �e�̒Ǐ]
////==============================================================================
//void SetPositionShadow(int nIdx, D3DXVECTOR3 pos)
//{
//	m_pos = pos;
//}