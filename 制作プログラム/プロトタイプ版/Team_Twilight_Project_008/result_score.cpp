//==============================================================================
//
// ���U���g�X�R�A�̕`�揈���kresult_score.cpp�l
// Author : Mare Horiai
//
//==============================================================================
//#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "title.h"
#include "result_score.h"
#include "fade.h"
#include "score.h"
//#include "ranking_rank.h"
//#include "ranking_score.h"
//#include "stdio.h"

// �ÓI�����o�ϐ��錾
int CResultScore::m_nScore;
int CResultScore::m_nShuffleCnt;
bool CResultScore::m_bCntEventEnd;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CResultScore::CResultScore(int nPriority) : CScene2D(nPriority)
{
	m_nScore = 0;
	m_nShuffleCnt = 0;
	m_bCntEventEnd = false;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CResultScore::~CResultScore()
{
}

//==============================================================================
// ���U���g�X�R�A�̏���������
//==============================================================================
HRESULT CResultScore::Init(D3DXVECTOR3 pos)
{
	// �X�R�A�̎擾
	//m_nScore = CScore::GetScore();

	// ���U���g�X�R�A�̐���
	//m_pScore = CScore::Create(pos, RESULT_SCORE_SIZEX, RESULT_SCORE_SIZEY);

	//m_pScore->SetScore(m_nScore);

	return S_OK;
}

//==============================================================================
// ���U���g�X�R�A�̏I������
//==============================================================================
void CResultScore::Uninit(void)
{
	if (m_pScore != NULL)
	{// NULL�`�F�b�N��ɔj��
		m_pScore->Uninit();
		m_pScore = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �����L���O�X�R�A�̍X�V����
//==============================================================================
void CResultScore::Update(void)
{
	// �t�F�[�h���̎擾
	CFade::FADE fade = CManager::GetFade()->GetFade();

	if (fade == CFade::FADE_NONE)
	{
		m_nShuffleCnt++;

		if (m_nShuffleCnt >= 150 && m_bCntEventEnd == false)
		{// ��2�b
			m_nScore = CScore::GetResultScore();

			CSound::Play(CSound::SOUND_LABEL_SE_COUNT);

			m_bCntEventEnd = true;
		}
		else if(m_nShuffleCnt < 150 && m_nShuffleCnt % 2 == 0 && m_nShuffleCnt >= 30)
		{
			// 0~99999999
			m_nScore = (rand() % 10000) * 10000 + (rand() % 10000);

			CSound::Play(CSound::SOUND_LABEL_SE_COUNT);
		}
	}

	// �X�R�A�̐ݒ�
	m_pScore->SetScore(m_nScore);
}

//==============================================================================
// ���U���g�X�R�A�̕`�揈��
//==============================================================================
void CResultScore::Draw(void)
{
	// �����L���O�X�R�A�̕`��
	if (m_pScore != NULL)
	{
		m_pScore->Draw();
	}
}

//==============================================================================
// ���U���g�X�R�A�̐�������
//==============================================================================
CResultScore *CResultScore::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CResultScore *pResultScore;
	pResultScore = new CResultScore;

	// ������
	pResultScore->Init(pos);

	return pResultScore;
}

//==============================================================================
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CResultScore::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CResultScore::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}