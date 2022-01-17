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
#include "scene2D.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CEffect::CEffect(int nPriority) : CScene(nPriority)
{

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
	m_col.a -= m_fAlphaDown;
	m_pos += m_move;
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

	// �t�H�O�𖳌���
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// ���Z�����ɂ��A���t�@�u�����f�B���O
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Z�e�X�g�̍X�V
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���C�g���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

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

	// �t�H�O�𖳌���
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
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
//void CEffect::SetEffect(void)
//{
//	// ���[�J���ϐ��錾
//	CTexture *pTexture = CManager::GetTexture();
//
//	switch (m_effectType)
//	{
//	case EFFECTTYPE_SANDSMOKE:	// ����
//
//		m_pTexture = pTexture->GetAddress("EFFECT");
//		SetColor(D3DXCOLOR(0.34f, 0.47f, 0.21f, 1.0f));
//
//		break;
//	}
//}

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
CEffectDetail::CEffectDetail(int nPriority) : CEffect(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CEffectDetail::~CEffectDetail()
{

}

//==============================================================================
// �r���{�[�h�̏���������
//==============================================================================
HRESULT CEffectDetail::Init(void)
{
	// ������
	switch (m_effectType)
	{
	case EFFECTTYPE_SANDSMOKE:

		m_nNumEffect = 1;

		break;

	case EFFECTTYPE_LANDING:
		
		m_nNumEffect = 20;

		break;

	case EFFECTTYPE_DIVE_WATER:
		
		m_nNumEffect = 20;

		break;

	case EFFECTTYPE_DIVE_LAVA:

		m_nNumEffect = 1;

		break;
	}

	// ���I�m��
	if (m_ppEffect == NULL)
	{
		m_ppEffect = new CEffect*[m_nNumEffect];
	}

	D3DXVECTOR3 move = VECTOR3_NULL;

	// �G�t�F�N�g����
	switch (m_effectType)
	{
	case EFFECTTYPE_SANDSMOKE:

		m_ppEffect[0] = CEffect::Create();
		m_ppEffect[0]->SetPosition(m_posMain);
		m_ppEffect[0]->SetMove(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		m_ppEffect[0]->SetSize(D3DXVECTOR2(1.0f, 1.0f));
		m_ppEffect[0]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_ppEffect[0]->SetTexture("SMOKE");
		m_ppEffect[0]->SetAlphaDown(0.02f);

		break;

	case EFFECTTYPE_LANDING:

		// �G�t�F�N�g����
		for (int nCntEffect = 0; nCntEffect < m_nNumEffect; nCntEffect++)
		{
			m_ppEffect[nCntEffect] = CEffect::Create();
			m_ppEffect[nCntEffect]->SetPosition(m_posMain);

			move.x = sinf((D3DX_PI * 2.0f / m_nNumEffect) * nCntEffect) * 1.0f;
			move.z = cosf((D3DX_PI * 2.0f / m_nNumEffect) * nCntEffect) * 1.0f;

			m_ppEffect[nCntEffect]->SetMove(move);
			m_ppEffect[nCntEffect]->SetSize(D3DXVECTOR2(1.0f, 1.0f));
			m_ppEffect[nCntEffect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_ppEffect[nCntEffect]->SetTexture("SMOKE");
			m_ppEffect[nCntEffect]->SetAlphaDown(0.02f);
		}

		break;

	case EFFECTTYPE_DIVE_WATER:
		// �G�t�F�N�g����
		for (int nCntEffect = 0; nCntEffect < m_nNumEffect; nCntEffect++)
		{
			m_ppEffect[nCntEffect] = CEffect::Create();
			m_ppEffect[nCntEffect]->SetPosition(m_posMain);

			move.x = sinf((D3DX_PI * 2.0f / m_nNumEffect) * nCntEffect) * (rand() % 5 + 1);
			move.z = cosf((D3DX_PI * 2.0f / m_nNumEffect) * nCntEffect) * (rand() % 5 + 1);

			move.y = (float)(rand() % 50 + 1) / 10.0f;

			m_ppEffect[nCntEffect]->SetMove(move);
			m_ppEffect[nCntEffect]->SetSize(D3DXVECTOR2(10.0f, 10.0f));
			m_ppEffect[nCntEffect]->SetColor(D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f));
			m_ppEffect[nCntEffect]->SetTexture("EFFECT");
			m_ppEffect[nCntEffect]->SetAlphaDown(0.03f);
		}
		break;

	case EFFECTTYPE_DIVE_LAVA:
		
		// �G�t�F�N�g����
		m_ppEffect[0] = CEffect::Create();
		m_ppEffect[0]->SetPosition(m_posMain);
		m_ppEffect[0]->SetMove(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		m_ppEffect[0]->SetSize(D3DXVECTOR2(20.0f, 20.0f));
		m_ppEffect[0]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		m_ppEffect[0]->SetTexture("SMOKE");
		m_ppEffect[0]->SetAlphaDown(0.01f);

		break;

	case EFFECTTYPE_GAMECLEAR:
		m_pClearEffect = CScene2D::Create();
		float fX = (float)(rand() % 1200 + 40);

		m_pClearEffect->SetPosition(D3DXVECTOR3(fX, -50.0f, 0.0f));
		m_pClearEffect->SetSize(D3DXVECTOR2(30.0f, 30.0f));
		m_pClearEffect->BindTexture("EFFECT");
		m_pClearEffect->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
		m_pClearEffect->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		m_pClearEffect->AlphaBlend();
		m_pClearEffect->ZbuffBlend();

		break;
	}

	return S_OK;
}

//==============================================================================
// �G�t�F�N�g�ڍׂ̏I������
//==============================================================================
void CEffectDetail::Uninit(void)
{
	// �G�t�F�N�g�̔j���E�J��
	for (int nCntEffect = 0; nCntEffect < m_nNumEffect; nCntEffect++)
	{
		if (m_ppEffect[nCntEffect] != NULL)
		{
			m_ppEffect[nCntEffect]->Uninit();
		}
	}

	// �m�ۂ̊J��
	if (m_nNumEffect > 1)
	{
		delete[] m_ppEffect;
	}
	else
	{
		delete m_ppEffect;
	}

	// �j��
	m_ppEffect = NULL;

	// �N���A�G�t�F�N�g
	if (m_pClearEffect != NULL)
	{
		m_pClearEffect->Uninit();
		m_pClearEffect = NULL;
	}

	Release();
}

//==============================================================================
// �G�t�F�N�g�ڍׂ̍X�V����
//==============================================================================
void CEffectDetail::Update(void)
{
	// �N���A�G�t�F�N�g�̔j��
	if (m_pClearEffect != NULL && m_effectType == EFFECTTYPE_GAMECLEAR)
	{
		D3DXVECTOR3 pos = m_pClearEffect->GetPosition();
		pos += D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		m_pClearEffect->SetPosition(pos);

		if (m_pClearEffect->GetPosition().y >= SCREEN_HEIGHT)
		{
			Uninit();
		}
	}

	// �j������
	for (int nCntEffect = 0; nCntEffect < m_nNumEffect; nCntEffect++)
	{
		if (m_ppEffect[nCntEffect] != NULL)
		{
			// �j������
			if (m_ppEffect[nCntEffect]->GetColor().a <= 0.0f)
			{
				Uninit();
				return;
			}
		}
	}

	// �e�G�t�F�N�g�̎d�l
	if (m_effectType == EFFECTTYPE_DIVE_WATER)
	{
		D3DXVECTOR3 move = VECTOR3_NULL;

		for (int nCntEffect = 0; nCntEffect < m_nNumEffect; nCntEffect++)
		{
			if (m_ppEffect[nCntEffect] != NULL)
			{
				move = m_ppEffect[nCntEffect]->GetMove();

				move.y -= 0.2f;

				m_ppEffect[nCntEffect]->SetMove(move);
			}
		}
	}
	else if(m_effectType == EFFECTTYPE_LANDING || m_effectType == EFFECTTYPE_SANDSMOKE)
	{
		D3DXVECTOR2 size = VECTOR2_NULL;

		for (int nCntEffect = 0; nCntEffect < m_nNumEffect; nCntEffect++)
		{
			if (m_ppEffect[nCntEffect] != NULL)
			{
				size = m_ppEffect[nCntEffect]->GetSize();

				size += D3DXVECTOR2(0.5f, 0.5f);

				m_ppEffect[nCntEffect]->SetSize(size);
			}
		}
	}
	else if (m_effectType == EFFECTTYPE_DIVE_LAVA)
	{
		D3DXVECTOR2 size = VECTOR2_NULL;

		size = m_ppEffect[0]->GetSize();

		size += D3DXVECTOR2(0.5f, 0.5f);

		m_ppEffect[0]->SetSize(size);
	}
}

//==============================================================================
// �|���S���`��̕`�揈��
//==============================================================================
void CEffectDetail::Draw(void)
{
}

//==============================================================================
// �G�t�F�N�g�̐���
//==============================================================================
CEffectDetail *CEffectDetail::Create(EFFECTTYPE effectType, D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	CEffectDetail *pEffectDetail;
	pEffectDetail = new CEffectDetail;

	// ������
	if (pEffectDetail != NULL)
	{
		pEffectDetail->SetType(effectType);
		pEffectDetail->SetPositionMain(D3DXVECTOR3(pos.x,pos.y + 10.0f,pos.z));
		pEffectDetail->Init();
	}

	// �Ԃ��l
	return pEffectDetail;
}