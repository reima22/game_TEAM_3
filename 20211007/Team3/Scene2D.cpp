//=============================================================================
//
// 2D�|���S�� [scene2D.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "scene2D.h"
#include "manager.h"
#include "input.h"

//*****************************************************************************
// �|���S���N���X (�h�����F�I�u�W�F�N�g�N���X�j
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pVertex = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// ��������ݒ�
	SetPos(pos);
	SetRot(rot);
	SetSize(size);

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���ă|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVertex, 0);

	// ���_����ݒ�
	// �ʒu
	m_pVertex[0].pos = D3DXVECTOR3(-size.x + pos.x, size.y + pos.y, 0.0f);
	m_pVertex[1].pos = D3DXVECTOR3(-size.x + pos.x, -size.y + pos.y, 0.0f);
	m_pVertex[2].pos = D3DXVECTOR3(size.x + pos.x, size.y + pos.y, 0.0f);
	m_pVertex[3].pos = D3DXVECTOR3(size.x + pos.x, -size.y + pos.y, 0.0f);

	// rhw
	m_pVertex[0].rhw = 1.0f;
	m_pVertex[1].rhw = 1.0f;
	m_pVertex[2].rhw = 1.0f;
	m_pVertex[3].rhw = 1.0f;

	// �F
	m_pVertex[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pVertex[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pVertex[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pVertex[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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
void CScene2D::Uninit(void)
{
	//// �e�N�X�`�����J��
	//if (m_pTexture != NULL) {
	//	m_pTexture->Release();
	//	m_pTexture = NULL;
	//}

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
void CScene2D::Update(void)
{
	// ���_�o�b�t�@�����b�N���ă|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVertex, 0);

	// �ʒu
	m_pVertex[0].pos = D3DXVECTOR3(-GetSize().x + GetPos().x, GetSize().y + GetPos().y, 0.0f);
	m_pVertex[1].pos = D3DXVECTOR3(-GetSize().x + GetPos().x, -GetSize().y + GetPos().y, 0.0f);
	m_pVertex[2].pos = D3DXVECTOR3(GetSize().x + GetPos().x, GetSize().y + GetPos().y, 0.0f);
	m_pVertex[3].pos = D3DXVECTOR3(GetSize().x + GetPos().x, -GetSize().y + GetPos().y, 0.0f);

	// ���_�o�b�t�@�A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	pDevice->SetTexture(0, m_pTexture);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �e�N�X�`���̃o�C���h
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void CScene2D::SetTextureUV(D3DXVECTOR2 Vertex_0, D3DXVECTOR2 Vertex_1, D3DXVECTOR2 Vertex_2, D3DXVECTOR2 Vertex_3)
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
void CScene2D::SetColor(D3DXCOLOR col)
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
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D;
	if (pScene2D != NULL)
	{
		pScene2D->Init(pos, rot, size);
	}

	return pScene2D;
}