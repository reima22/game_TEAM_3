//==============================================================================
//
// ���U���g���[�h�����kresult.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "bg.h"
#include "fade.h"
#include "gamepad.h"
#include "input.h"
#include "result.h"
#include "result_bonuscount.h"
#include "result_fallcount.h"
#include "result_picture.h"
#include "result_score.h"
#include "result_score_extra.h"
#include "result_timer.h"
#include "scene2D.h"

//==============================================================================
// �ÓI�����o�ϐ��錾
//==============================================================================
CResultPicture		*CResult::m_pResultPicture[PICTYPE_MAX] = {};		// �\���摜
CResultTimer		*CResult::m_pResultTimer = NULL;					// ���U���g�^�C�}�[�|�C���^
CResultFallCount	*CResult::m_pResultFallCount = NULL;				// ���U���g�������|�C���^
CResultBonus		*CResult::m_pResultBonus = NULL;					// ���U���g�{�[�i�X�|�C���^
CResultScore		*CResult::m_pResultScore = NULL;					// ���U���g�X�R�A�|�C���^
CResultScoreEx		*CResult::m_pResultScoreEx[EXSCORETYPE_MAX] = {};	// �����ʃX�R�A�|�C���^
CResult::ENDSTATE	CResult::m_endState;								// �Q�[���I�����̏��

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CResult::CResult(int nPriority) : CMode(nPriority)
{
	// ������
	for (int nCntPicture = 0; nCntPicture < PICTYPE_MAX; nCntPicture++)
	{
		m_pResultPicture[nCntPicture] = NULL;
	}
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CResult::~CResult()
{

}

//==============================================================================
// ���U���g��ʂ̏���������
//==============================================================================
HRESULT CResult::Init(void)
{
	// �w�i�̐���
	m_pBg = CBg::Create();

	// ���S�̐���
	if (m_endState == ENDSTATE_CLEAR)
	{	// �N���A��
		m_pResultPicture[PICTYPE_MAIN] = CResultPicture::Create(R_PICT_POS, VECTOR3_NULL, R_PICT_SIZE, "RESULT_LOGO_CLEAR");	// �Q�[���N���A���S
	}
	else
	{
		m_pResultPicture[PICTYPE_MAIN] = CResultPicture::Create(R_PICT_POS, VECTOR3_NULL, R_PICT_SIZE, "RESULT_LOGO_OVER");		// �Q�[���I�[�o�[���S
	}

	// �z�u�|���S��
	m_pResultPicture[PICTYPE_YOURSCORE] = CResultPicture::Create(R_PICT_SCORE_POS, VECTOR3_NULL, R_PICT_SCORE_SIZE, "RANKING_YOURSCORE");	// �u����̃X�R�A�v���S
	m_pResultPicture[PICTYPE_TIMERLOGO] = CResultPicture::Create(R_PICT_TIMER_POS, VECTOR3_NULL, R_PICT_TIMER_SIZE, "TIMER_LOGO");			// �^�C�}�[���S
	m_pResultPicture[PICTYPE_COUNTLOGO] = CResultPicture::Create(R_PICT_COUNT_POS, VECTOR3_NULL, R_PICT_COUNT_SIZE, "FALL_LOGO");			// ���������S
	m_pResultPicture[PICTYPE_BONUSLOGO] = CResultPicture::Create(R_PICT_BONUS_POS, VECTOR3_NULL, R_PICT_BONUS_SIZE, "BONUS_LOGO");			// �{�[�i�X���S

	// �Z�p�L��
	m_pResultPicture[PICTYPE_TIMERMARK_0] = CResultPicture::Create(R_PICT_TIMER_MARK_POS_0, VECTOR3_NULL, R_PICT_MARK_SIZE, "MULTI");	// ��Z
	m_pResultPicture[PICTYPE_TIMERMARK_1] = CResultPicture::Create(R_PICT_TIMER_MARK_POS_1, VECTOR3_NULL, R_PICT_MARK_SIZE, "PLUS");	// ���Z
	m_pResultPicture[PICTYPE_TIMERMARK_2] = CResultPicture::Create(R_PICT_TIMER_MARK_POS_2, VECTOR3_NULL, R_PICT_MARK_SIZE, "EQUAL");	// ����

	m_pResultPicture[PICTYPE_COUNTMARK_0] = CResultPicture::Create(R_PICT_COUNT_MARK_POS_0, VECTOR3_NULL, R_PICT_MARK_SIZE, "MULTI");	// ��Z
	m_pResultPicture[PICTYPE_COUNTMARK_1] = CResultPicture::Create(R_PICT_COUNT_MARK_POS_1, VECTOR3_NULL, R_PICT_MARK_SIZE, "MINUS");	// ���Z
	m_pResultPicture[PICTYPE_COUNTMARK_2] = CResultPicture::Create(R_PICT_COUNT_MARK_POS_2, VECTOR3_NULL, R_PICT_MARK_SIZE, "EQUAL");	// ����

	m_pResultPicture[PICTYPE_BONUSMARK_0] = CResultPicture::Create(R_PICT_BONUS_MARK_POS_0, VECTOR3_NULL, R_PICT_MARK_SIZE, "MULTI");	// ��Z
	m_pResultPicture[PICTYPE_BONUSMARK_1] = CResultPicture::Create(R_PICT_BONUS_MARK_POS_1, VECTOR3_NULL, R_PICT_MARK_SIZE, "PLUS");	// ���Z
	m_pResultPicture[PICTYPE_BONUSMARK_2] = CResultPicture::Create(R_PICT_BONUS_MARK_POS_2, VECTOR3_NULL, R_PICT_MARK_SIZE, "EQUAL");	// ����

	// ���U���g�X�R�A�̐���
	m_pResultScore = CResultScore::Create(RESULT_SCORE_POS);

	// ���U���g�^�C�}�[����
	m_pResultTimer = CResultTimer::Create();

	// ���U���g�̗����J�E���g����
	m_pResultFallCount = CResultFallCount::Create();

	// ���U���g�̃{�[�i�X�J�E���g����
	m_pResultBonus = CResultBonus::Create();

	// �����U���g�X�R�A�̐���
	// �^�C�}�[
	m_pResultScoreEx[EXSCORETYPE_TIMER] = CResultScoreEx::Create(EXSCORE_TIMER_POS, EXSCORE_SIZE, EXSCORE_DIGIT, EXSCORE_TIMER);
	m_pResultScoreEx[EXSCORETYPE_TIMER_CALCU] = CResultScoreEx::Create(EXSCORE_TIMERCALCU_POS, EXSCORE_CALCU_SIZE, EXSCORE_CALCU_DIGIT, 0);

	m_pResultScoreEx[EXSCORETYPE_TIMER]->SetCol(D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f));

	// �J�E���g
	m_pResultScoreEx[EXSCORETYPE_COUNT] = CResultScoreEx::Create(EXSCORE_COUNT_POS, EXSCORE_SIZE, EXSCORE_DIGIT, EXSCORE_COUNT);
	m_pResultScoreEx[EXSCORETYPE_COUNT_CALCU] = CResultScoreEx::Create(EXSCORE_COUNTCALCU_POS, EXSCORE_CALCU_SIZE, EXSCORE_CALCU_DIGIT, 0);

	m_pResultScoreEx[EXSCORETYPE_COUNT]->SetCol(D3DXCOLOR(1.0f, 0.6f, 0.1f, 1.0f));

	// �{�[�i�X
	m_pResultScoreEx[EXSCORETYPE_BONUS] = CResultScoreEx::Create(EXSCORE_BONUS_POS, EXSCORE_SIZE, EXSCORE_DIGIT, EXSCORE_BONUS);
	m_pResultScoreEx[EXSCORETYPE_BONUS_CALCU] = CResultScoreEx::Create(EXSCORE_BONUSCALCU_POS, EXSCORE_CALCU_SIZE, EXSCORE_CALCU_DIGIT, 0);

	m_pResultScoreEx[EXSCORETYPE_BONUS]->SetCol(D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f));

	// BGM�̍Đ�
	if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_RESULT) == true)
	{
		m_pSound->Play(CSound::SOUND_LABEL_BGM005);
	}

	return S_OK;
}

//==============================================================================
// ���U���g��ʂ̏I������
//==============================================================================
void CResult::Uninit(void)
{
	// BGM�̒�~
	if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_RESULT) == true)
	{
		m_pSound->Stop();
	}

	// �\������}�̊J��
	for (int nCntType = 0; nCntType < PICTYPE_MAX; nCntType++)
	{
		if (m_pResultPicture[nCntType] != NULL)
		{
			m_pResultPicture[nCntType]->Uninit();
			m_pResultPicture[nCntType] = NULL;
		}
	}

	// ���U���g�X�R�A�̊J��
	if (m_pResultScore != NULL)
	{
		m_pResultScore->Uninit();
		m_pResultScore = NULL;
	}

	// ���U���g�^�C�}�[�̊J��
	if (m_pResultTimer != NULL)
	{
		m_pResultTimer->Uninit();
		m_pResultTimer = NULL;
	}

	// ���U���g�J�E���g�̊J��
	if (m_pResultFallCount != NULL)
	{
		m_pResultFallCount->Uninit();
		m_pResultFallCount = NULL;
	}

	// �����U���g�X�R�A�̊J��
	for (int nCntScore = 0; nCntScore < EXSCORETYPE_MAX; nCntScore++)
	{
		if (m_pResultScoreEx[nCntScore] != NULL)
		{
			m_pResultScoreEx[nCntScore]->Uninit();
			m_pResultScoreEx[nCntScore] = NULL;
		}
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// ���U���g��ʂ̍X�V����
//==============================================================================
void CResult::Update(void)
{
	// �X�R�A�\�L�̍X�V
	UpdateScore();

	// ���ʃ|�C���^
	UpdateBg();
}

//==============================================================================
// ���U���g��ʂ̕`�揈��
//==============================================================================
void CResult::Draw(void)
{
}

//==============================================================================
// ���U���g���[�h�̐�������
//==============================================================================
CResult *CResult::Create(void)
{
	// �C���X�^���X����
	CResult *pResult;
	pResult = new CResult;

	// ������
	pResult->Init();

	return pResult;
}

//==============================================================================
// �X�R�A�\�L�̍X�V
//==============================================================================
void CResult::UpdateScore(void)
{
	// �t�F�[�h���̎擾
	CFade *pFade;
	pFade = CManager::GetFade();
	CFade::FADE fade = pFade->GetFade();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �V�[���J��
	if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		if (fade == CFade::FADE_NONE && CResultScore::GetShuffleCnt() >= (RESULT_SHUFFLE + CNT_ONE_SECOND * (CResultScore::SCORETYPE_MAX - 1)))
		{
			pFade->SetFade(CFade::FADE_OUT, CMode::MODE_RANKING);
		}
		else if (fade == CFade::FADE_IN)
		{// �t�F�[�h�C���̃J�b�g
			pFade->FadeInCancel();
		}

		if (CResultScore::GetShuffleCnt() < (RESULT_SHUFFLE + CNT_ONE_SECOND * (CResultScore::SCORETYPE_MAX - 1)) && fade == CFade::FADE_NONE)
		{// �J�E���g�̒Z�k
			CResultScore::SetShuffleCnt((RESULT_SHUFFLE + CNT_ONE_SECOND * (CResultScore::SCORETYPE_MAX - 1)));
		}
	}

	// �V���b�t��
	m_pResultScoreEx[EXSCORETYPE_TIMER_CALCU]->ShffleNum(EXSCORETYPE_TIMER_CALCU);
	m_pResultScoreEx[EXSCORETYPE_COUNT_CALCU]->ShffleNum(EXSCORETYPE_COUNT_CALCU);
	m_pResultScoreEx[EXSCORETYPE_BONUS_CALCU]->ShffleNum(EXSCORETYPE_BONUS_CALCU);

	// �V���b�t���������̏��
	for (int nCnt = 0; nCnt < CResultScore::SCORETYPE_MAX; nCnt++)
	{
		if (m_pResultScore->GetEnd(nCnt) == true)
		{
			switch (nCnt)
			{
			case CResultScore::SCORETYPE_TIMER:	// �^�C�}�[

				m_pResultScoreEx[EXSCORETYPE_TIMER_CALCU]->SetCol(D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f));

				break;

			case CResultScore::SCORETYPE_FALL:	// �����J�E���g

				m_pResultScoreEx[EXSCORETYPE_COUNT_CALCU]->SetCol(D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f));

				break;

			case CResultScore::SCORETYPE_BONUS:	// �{�[�i�X

				m_pResultScoreEx[EXSCORETYPE_BONUS_CALCU]->SetCol(D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f));

				break;

			case CResultScore::SCORETYPE_MAIN:	// ���C���X�R�A

				m_pResultScore->GetScorePoint()->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.1f, 1.0f));

				break;
			}
		}
	}
}

//==============================================================================
// �w�i�̍X�V
//==============================================================================
void CResult::UpdateBg(void)
{
	// ���[�J���ϐ��錾
	static float fTexX;
	static float fTexY;

	// ����
	fTexX += 0.001f;
	fTexY -= 0.001f;

	// �w�i�X�N���[��
	m_pBg->GetScene2D()->SetTex(1, 1, 0, 0, fTexX, fTexY);
}