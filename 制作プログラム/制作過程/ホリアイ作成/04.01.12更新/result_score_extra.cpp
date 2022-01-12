//==============================================================================
//
// �����U���g�X�R�A�̕`�揈���kresult_score_extra.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "title.h"
#include "result_score_extra.h"
#include "fade.h"
#include "score.h"
#include "number.h"
#include "result_score.h"
#include "fall_count.h"
#include "timer_count.h"
#include "bonus_count.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CResultScoreEx::CResultScoreEx(int nPriority) : CResultScore(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CResultScoreEx::~CResultScoreEx()
{
}

//==============================================================================
// �����U���g�X�R�A�̏���������
//==============================================================================
HRESULT CResultScoreEx::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nDigit, int nScore)
{
	// �ϐ��ݒ�
	m_nDigit = nDigit;
	m_nScoreEx = nScore;

	// �����N���X�̓��I�m��
	m_pNumber = new CNumber*[m_nDigit];

	// ���̐ݒ�
	for (int nCntDigit = 0; nCntDigit < m_nDigit; nCntDigit++)
	{
		m_pNumber[nCntDigit] = CNumber::Create(
			D3DXVECTOR3(pos.x + (nCntDigit * (size.x * 2)), pos.y, 0.0f), size);
	}

	return S_OK;
}

//==============================================================================
// �����U���g�X�R�A�̏I������
//==============================================================================
void CResultScoreEx::Uninit(void)
{
	// �i���o�[�N���X�̊J��
	if (m_pNumber != NULL)
	{
		if (m_nDigit > 1)
		{
			delete[] m_pNumber;
		}
		else
		{
			delete m_pNumber;
		}

		m_pNumber = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �����U���g�X�R�A�̍X�V����
//==============================================================================
void CResultScoreEx::Update(void)
{
	//// �t�F�[�h���̎擾
	//CFade::FADE fade = CManager::GetFade()->GetFade();
	//if (fade == CFade::FADE_NONE)
	//{
	//	m_nShuffleCnt++;
	//	if (m_nShuffleCnt >= 150 && m_bCntEventEnd == false)
	//	{// ��2�b
	//		m_nScore = CScore::GetResultScore();
	//		m_pSound->Play(CSound::SOUND_LABEL_SE_COUNT);
	//		m_bCntEventEnd = true;
	//	}
	//	else if (m_nShuffleCnt < 150 && m_nShuffleCnt % 2 == 0 && m_nShuffleCnt >= 30)
	//	{
	//		// 0~99999999
	//		m_nScore = (rand() % 10000) * 10000 + (rand() % 10000);
	//		m_pSound->Play(CSound::SOUND_LABEL_SE_COUNT);
	//	}
	//}
	//// �X�R�A�̐ݒ�
	//m_pScore->SetScore(m_nScore);

	// �X�R�A�̐ݒ�
	SetScoreEx(m_nScoreEx);
}

//==============================================================================
// �����U���g�X�R�A�̕`�揈��
//==============================================================================
void CResultScoreEx::Draw(void)
{
	for (int nCntDigit = 0; nCntDigit < m_nDigit; nCntDigit++)
	{
		if (m_pNumber[nCntDigit] != NULL)
		{
			m_pNumber[nCntDigit]->Draw();
		}
	}
}

//==============================================================================
// �����U���g�X�R�A�̐�������
//==============================================================================
CResultScoreEx *CResultScoreEx::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nDigit,int nScore)
{
	// �C���X�^���X����
	CResultScoreEx *pResultScoreEx;
	pResultScoreEx = new CResultScoreEx;

	// ������
	if (pResultScoreEx != NULL)
	{
		pResultScoreEx->Init(pos, size, nDigit,nScore);
	}

	return pResultScoreEx;
}

//==============================================================================
// �����U���g�X�R�A�ݒ�
//==============================================================================
void CResultScoreEx::SetScoreEx(int nScore)
{
	// �X�R�A�̐ݒ�
	m_nScoreEx = nScore;

	int nData = (int)pow(10, (m_nDigit - 1));

	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		// �e���̎Z�o
		int nNumber;
		nNumber = (m_nScoreEx / nData) % 10;
		nData /= 10;

		// ���̐ݒ�
		m_pNumber[nCnt]->SetNumber(nNumber);
	}
}

//==============================================================================
// ���l�̃V���b�t�����o
//==============================================================================s
void CResultScoreEx::ShffleNum(int nType)
{
	// ���[�J���ϐ��錾
	int nShuffleCnt = CResultScore::GetShuffleCnt();

	// �C�x���g�I���t���O
	bool bEndEvent[SCORETYPE_MAX];
	bEndEvent[0] = CResultScore::GetEnd(0);
	bEndEvent[1] = CResultScore::GetEnd(1);
	bEndEvent[2] = CResultScore::GetEnd(2);

	// �v�Z�p�̃^�C���A������
	int nTimer = CTimerCount::GetTimerNum();
	int nFallCount = CFallCount::GetFallNum();
	int nBonus = CBonusCount::GetBonusNum();

	// �t�F�[�h���̎擾
	CFade::FADE fade = CManager::GetFade()->GetFade();

	if (fade == CFade::FADE_NONE)
	{
		if (nType == CResult::EXSCORETYPE_TIMER_CALCU)
		{
			if (nShuffleCnt >= 150 && bEndEvent[0] == false)
			{// ��2�b
				m_nScoreEx = nTimer * EXSCORE_TIMER;

				m_pSound->Play(CSound::SOUND_LABEL_SE_DECIDE);
			}
			else if (nShuffleCnt < RESULT_SHUFFLE && nShuffleCnt % 2 == 0 && nShuffleCnt >= RESULT_SHUFFLE_START)
			{
				// 0~99999999
				m_nScoreEx = (rand() % 10000) * 10000 + (rand() % 10000);

				m_pSound->Play(CSound::SOUND_LABEL_SE_COUNT);
			}
		}
		else if (nType == CResult::EXSCORETYPE_COUNT_CALCU)
		{
			if (nShuffleCnt >= 210 && bEndEvent[1] == false)
			{// ��2�b
				m_nScoreEx = nFallCount * EXSCORE_COUNT;

				m_pSound->Play(CSound::SOUND_LABEL_SE_DECIDE);
			}
			else if (nShuffleCnt < 210 && nShuffleCnt % 2 == 0 && nShuffleCnt >= RESULT_SHUFFLE_START)
			{
				// 0~99999999
				m_nScoreEx = (rand() % 10000) * 10000 + (rand() % 10000);

				m_pSound->Play(CSound::SOUND_LABEL_SE_COUNT);
			}
		}
		else if(nType == CResult::EXSCORETYPE_BONUS_CALCU)
		{
			if (nShuffleCnt >= 270 && bEndEvent[2] == false)
			{// ��2�b
				m_nScoreEx = nBonus * EXSCORE_COUNT;

				m_pSound->Play(CSound::SOUND_LABEL_SE_DECIDE);
			}
			else if (nShuffleCnt < 270 && nShuffleCnt % 2 == 0 && nShuffleCnt >= RESULT_SHUFFLE_START)
			{
				// 0~99999999
				m_nScoreEx = (rand() % 10000) * 10000 + (rand() % 10000);

				m_pSound->Play(CSound::SOUND_LABEL_SE_COUNT);
			}
		}
	}
}

//==============================================================================
// �F�̐ݒ�
//==============================================================================
void CResultScoreEx::SetCol(D3DXCOLOR col)
{
	// �F�̔��f
	for (int nCntNumber = 0; nCntNumber < m_nDigit; nCntNumber++)
	{
		m_pNumber[nCntNumber]->SetCol(col);
	}
}