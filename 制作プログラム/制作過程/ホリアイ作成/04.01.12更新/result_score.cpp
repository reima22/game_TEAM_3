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
#include "result_score_extra.h"
//#include "ranking_rank.h"
//#include "ranking_score.h"
//#include "stdio.h"

// �ÓI�����o�ϐ��錾
int CResultScore::m_nScore;
int CResultScore::m_nShuffleCnt;
bool CResultScore::m_bCntEventEnd[SCORETYPE_MAX] = {};

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CResultScore::CResultScore(int nPriority) : CResult(nPriority)
{
	m_nScore = 0;
	m_nShuffleCnt = 0;
	m_nShaffleIdx = 0;
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
	m_nScore = 0;

	// �J�E���g�̃��Z�b�g
	m_nShuffleCnt = 0;

	// �t���O�̃��Z�b�g
	for (int nCnt = 0; nCnt < SCORETYPE_MAX; nCnt++)
	{
		m_bCntEventEnd[nCnt] = false;
	}

	// ���U���g�X�R�A�̐���
	m_pScore = CScore::Create(pos, RESULT_SCORE_SIZE);

	// �X�R�A�ݒ�
	m_pScore->SetScore(m_nScore);

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
// ���U���g�X�R�A�̍X�V����
//==============================================================================
void CResultScore::Update(void)
{
	// �t�F�[�h���̎擾
	CFade::FADE fade = CManager::GetFade()->GetFade();

	if (fade == CFade::FADE_NONE && m_nShuffleCnt <= (RESULT_SHUFFLE + CNT_ONE_SECOND * (SCORETYPE_MAX - 1)))
	{
		// �V���b�t���J�E���g�̉��Z
		m_nShuffleCnt++;

		if (m_nShuffleCnt >= RESULT_SHUFFLE + (CNT_ONE_SECOND * (SCORETYPE_MAX - 1)) && m_bCntEventEnd[SCORETYPE_MAX - 1] == false)
		{// ��2�b
			m_nScore = CScore::GetResultScore() + 
				CResult::GetScoreExPoint(CResult::EXSCORETYPE_TIMER_CALCU)->GetScoreEx() - 
				CResult::GetScoreExPoint(CResult::EXSCORETYPE_COUNT_CALCU)->GetScoreEx() + 
				CResult::GetScoreExPoint(CResult::EXSCORETYPE_BONUS_CALCU)->GetScoreEx();

			m_pSound->Play(CSound::SOUND_LABEL_SE_DECIDE);
		}
		else if(m_nShuffleCnt < RESULT_SHUFFLE  + (CNT_ONE_SECOND * (SCORETYPE_MAX - 1)) && m_nShuffleCnt % 2 == 0 && m_nShuffleCnt >= RESULT_SHUFFLE_START)
		{
			// 0~99999999
			m_nScore = (rand() % 10000) * 10000 + (rand() % 10000);

			m_pSound->Play(CSound::SOUND_LABEL_SE_COUNT);
		}
	}

	if (m_nShuffleCnt > RESULT_SHUFFLE + (CNT_ONE_SECOND * m_nShaffleIdx))
	{
		m_bCntEventEnd[m_nShaffleIdx] = true;
		m_nShaffleIdx++;
	}

	//if (m_nShuffleCnt > RESULT_SHUFFLE)
	//{
	//	m_bCntEventEnd[0] = true;
	//}
	//if (m_nShuffleCnt > 210)
	//{
	//	m_bCntEventEnd[1] = true;
	//}
	//if (m_nShuffleCnt > 270)
	//{
	//	m_bCntEventEnd[2] = true;
	//}

	//if ()
	//{
	//	m_bCntEventEnd[3] = true;
	//}

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
	if (pResultScore != NULL)
	{
		pResultScore->Init(pos);
	}

	return pResultScore;
}