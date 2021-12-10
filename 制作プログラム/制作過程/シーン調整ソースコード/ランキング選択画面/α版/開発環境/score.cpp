//==============================================================================
//
// �X�R�A�`�揈���kscore.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "score.h"
#include "number.h"
#include "mode.h"

// �ÓI�����o�ϐ��錾
int CScore::m_nResultScore = 0;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		// �e�i���o�[�̏�����
		m_apNumber[nCnt] = NULL;
	}
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CScore::~CScore()
{
}

//==============================================================================
// �X�R�A�̏���������
//==============================================================================
HRESULT CScore::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{
			m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(m_posBase.x + (nCnt * (m_size.x * 2)), m_posBase.y, 0.0f), m_size);
		}
	}

	m_nScore = 0;

	return S_OK;
}

//==============================================================================
// �X�R�A�̏I������
//==============================================================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// NULL�`�F�b�N��ɔj��
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;
		}
	}

	Release();	// CScore�C���X�^���X�̃f���[�g
}

//==============================================================================
// �X�R�A�̍X�V����
//==============================================================================
void CScore::Update(void)
{
	if (m_nScore < 0)
	{
		m_nScore = 0;
	}

	// �X�R�A�̐ݒ�
	SetScore(m_nScore);
}

//==============================================================================
// �X�R�A�̕`�揈��
//==============================================================================
void CScore::Draw(void)
{
	// �i���o�[�̕`��
	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		if (m_apNumber != NULL)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//==============================================================================
// �X�R�A�̐�������
//==============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// CScore�̃C���X�^���X����
	CScore *pScore;
	pScore = new CScore;

	// CScore�̏�����
	if (pScore != NULL)
	{
		pScore->SetPosition(pos);
		pScore->SetSize(size);
		pScore->Init();
	}

	return pScore;
}

//==============================================================================
// �X�R�A�ݒ�
//==============================================================================
void CScore::SetScore(int nScore)
{
	// �X�R�A�̐ݒ�
	m_nScore = nScore;

	int nData = (int)pow(10, (NUM_MAX - 1));

	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		// �e���̎Z�o
		int nNumber;
		nNumber = (m_nScore / nData) % 10;
		nData /= 10;

		// ���̐ݒ�
		m_apNumber[nCnt]->SetNumber(nNumber);
	}
}