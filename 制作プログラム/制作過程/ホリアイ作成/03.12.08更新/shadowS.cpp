//==============================================================================
//
// �e���f���`�揈���kshadowS.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene3D.h"
#include "renderer.h"
#include "manager.h"
#include "sceneX.h"
#include "texture.h"
#include "model.h"
#include "shadowS.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CShadowS::CShadowS()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CShadowS::~CShadowS()
{

}

//==============================================================================
// 3D���f���`��̏���������
//==============================================================================
HRESULT CShadowS::Init(D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���f���̐���
	m_pSceneX = CSceneX::Create(pos);

	// �ʒu�̐ݒ�
	SetPosition(pos);

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

	// �|���S���̔z�u
	m_posPolygon = SCREEN_CENTER;

	// �|���S���̑傫��
	m_sizePolygon = D3DXVECTOR2(640.0f, 360.0f);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���l�̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(m_posPolygon.x - m_sizePolygon.x, m_posPolygon.y + m_sizePolygon.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_posPolygon.x - m_sizePolygon.x, m_posPolygon.y - m_sizePolygon.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_posPolygon.x + m_sizePolygon.x, m_posPolygon.y + m_sizePolygon.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_posPolygon.x + m_sizePolygon.x, m_posPolygon.y - m_sizePolygon.y, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �e���_�J���[�̐ݒ�(��)
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================================================
// 3D���f���`��̏I������
//==============================================================================
void CShadowS::Uninit(void)
{
	//// ���b�V���|�C���^�̔j��
	//if (m_pMesh != NULL)
	//{
	//	m_pMesh->Release();
	//	m_pMesh = NULL;
	//}

	//// �}�e���A���o�b�t�@�̔j��
	//if (m_pBuffMat != NULL)
	//{
	//	m_pBuffMat->Release();
	//	m_pBuffMat = NULL;
	//}

	CScene3D::Uninit();
}

//==============================================================================
// 3D���f���`��̍X�V����
//==============================================================================
void CShadowS::Update(void)
{

}

//==============================================================================
// 3D���f���`��̕`�揈��
//==============================================================================
void CShadowS::Draw(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;										// �v�Z�p�}�g���b�N�X

	// �ʒu�ƌ���
	D3DXVECTOR3 pos = CScene3D::GetPosition();
	D3DXVECTOR3 rot = CScene3D::GetRotation();
	D3DXMATRIX mtx = m_pSceneX->GetMatrix();



	// �t�H�O��L����
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtx);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtx);


	// �X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// Z�o�b�t�@�̏������݂𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �J���[�o�b�t�@�ւ̏������݂𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);


	// �X�e���V���o�b�t�@�̔�r�p�����[�^�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_ALWAYS);

	// �X�e���V���e�X�g���i�EZ�e�X�g���i
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	// �X�e���V���e�X�g���i�EZ�e�X�g�s���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCRSAT);

	// �X�e���V���e�X�g�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_INCRSAT);

	// �\�ʂ��J�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	// �e���f���̕`��
	m_pSceneX->Draw();

	// �X�e���V���o�b�t�@�̎Q�ƒl��ݒ�i"1"�ɂ���j
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	// �X�e���V���o�b�t�@�̔�r�p�����[�^�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	// �X�e���V���e�X�g���i�EZ�e�X�g���i
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);

	// �X�e���V���e�X�g���i�EZ�e�X�g�s���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	// �X�e���V���e�X�g�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	// ���ʂ��J�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// �e���f���̕`��
	m_pSceneX->Draw();

	// �J���[�o�b�t�@�ւ̏������݂�L���ɂ���
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);

	// �X�e���V���o�b�t�@�̎Q�ƒl��ݒ�("2"�ɂ���)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

	// �X�e���V���o�b�t�@�̔�r�p�����[�^�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	// �X�e���V���e�X�g���i�EZ�e�X�g���i
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	// �X�e���V���e�X�g���i�EZ�e�X�g�s���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	// �X�e���V���e�X�g�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	// �|���S���̕\��
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		2);						// �`�悷��v���~�e�B�u��


	// ���ʂ��J�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// Z�o�b�t�@�̏������݂�L���ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �X�e���V���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// �t�H�O��L����
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//==============================================================================
// ��������
//==============================================================================
CShadowS *CShadowS::Create(D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	CShadowS *pShadowS;
	pShadowS = new CShadowS;	// �V�[��X�̃C���X�^���X

	// ������
	if (pShadowS != NULL)
	{
		pShadowS->Init(pos);
	}

	return pShadowS;
}

//==============================================================================
// �e�̒Ǐ]
//==============================================================================
void CShadowS::SetPosition(D3DXVECTOR3 pos)
{
	CScene3D *pScene3D;
	pScene3D = m_pSceneX->GetScene3D();

	if (pScene3D != NULL)
	{
		pScene3D->SetPosition3D(pos);
	}
}