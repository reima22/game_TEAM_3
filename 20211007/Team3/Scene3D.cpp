//=============================================================================
//
// 3D�|���S�� [scene3D.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Scene3D.h"
#include "Manager.h"
#include "Input.h"

//*****************************************************************************
// �|���S���N���X (�h�����F�I�u�W�F�N�g�N���X�j
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene3D::CScene3D(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pVertex = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// ��������ݒ�
	SetPos(pos);
	SetRot(rot);
	SetSize(size);

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���ă|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVertex, 0);

	// ���_����ݒ�
	// �ʒu
	m_pVertex[0].pos = D3DXVECTOR3(-size.x, 0.0f, -size.z);
	m_pVertex[1].pos = D3DXVECTOR3(-size.x, 0.0f, size.z);
	m_pVertex[2].pos = D3DXVECTOR3(size.x, 0.0f, -size.z);
	m_pVertex[3].pos = D3DXVECTOR3(size.x, 0.0f, size.z);

	// �@��
	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
		m_pVertex[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// �F
	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
		m_pVertex[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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
// �I������
//=============================================================================
void CScene3D::Uninit(void)
{
	// ���_�o�b�t�@���J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �C���X�^���X�j��
	this->Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3D::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// Device
	D3DXMATRIX mtxRot, mtxTrans;	// Temporary matrices

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXVECTOR3 rot = GetRot();
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXVECTOR3 pos = GetPos();
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->SetTexture(0, m_pTexture);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �e�N�X�`���̃o�C���h
//=============================================================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void CScene3D::SetTextureUV(D3DXVECTOR2 Vertex_0, D3DXVECTOR2 Vertex_1, D3DXVECTOR2 Vertex_2, D3DXVECTOR2 Vertex_3)
{
	// ���_�o�b�t�@�����b�N���ă|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVertex, 0);

	// �e�N�X�`�����W�ݒ�
	m_pVertex[0].tex = Vertex_0;
	m_pVertex[1].tex = Vertex_1;
	m_pVertex[2].tex = Vertex_2;
	m_pVertex[3].tex = Vertex_3;

	// ���_�o�b�t�@�A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �J���[�̐ݒ�
//=============================================================================
void CScene3D::SetColor(D3DXCOLOR col)
{
	// ���_�o�b�t�@�����b�N���ă|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVertex, 0);

	// �F�̐ݒ�
	m_pVertex[0].col = col;
	m_pVertex[1].col = col;
	m_pVertex[2].col = col;
	m_pVertex[3].col = col;

	// ���_�o�b�t�@�A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �����֐�
//=============================================================================
CScene3D *CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CScene3D *pScene3D;
	pScene3D = new CScene3D;
	if (pScene3D != NULL)
	{
		pScene3D->Init(pos, rot, size);
	}

	return pScene3D;
}