//==============================================================================
//
// �����L���O�I���������kranking_select.cpp�l
// Author : Tatsuki Matsuda
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "ranking_select.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "sound.h"
#include "textdata.h"
#include "textdata_rankingselect.h"

// �ÓI�����o�ϐ��錾
CScene2D *CRankingSelect::m_apScene2D[RANKING_MAX] = {};
CRankingSelect::RANKING CRankingSelect::m_ranking;			// �I�𒆂̃J�[�\��
D3DXCOLOR CRankingSelect::m_col;							// �I�𒆃J�[�\���̐F

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CRankingSelect::CRankingSelect(int nPriority) : CRanking(nPriority)
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CRankingSelect::~CRankingSelect()
{
}

//==============================================================================
//�����L���O�I���̏���������
//==============================================================================
HRESULT CRankingSelect::Init(void)
{
	// �e�L�X�g�f�[�^�̎擾
	CTextDataRankingSelect *pDataRankingSelect;
	pDataRankingSelect = CTextData::GetDataSelectRanking();

	for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
	{
		// �f�[�^�̎擾
		D3DXVECTOR3 pos = pDataRankingSelect->GetPosition(CTextDataRankingSelect::RANKINGPOLY_RETRY + nCnt);
		D3DXVECTOR2 size = pDataRankingSelect->GetSize(CTextDataRankingSelect::RANKINGPOLY_RETRY + nCnt);
		int nTexIdx = pDataRankingSelect->GetTexIdx(CTextDataRankingSelect::RANKINGPOLY_RETRY) + nCnt;

		// 2D�|���S���̐���
		m_apScene2D[nCnt] = CScene2D::Create();
		m_apScene2D[nCnt]->SetPosition(pos);
		m_apScene2D[nCnt]->SetSize(size);
		m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	m_apScene2D[RANKING_RETRY]->BindTexture("RANKING_RETRY");
	m_apScene2D[RANKING_QUIT]->BindTexture("RANKING_QUIT");

	// ������
	m_ranking = RANKING_RETRY;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bAlphaDown = true;
	m_bSelect = false;
	m_bOK = false;
	m_nCntTime = 0;

	return S_OK;
}

//==============================================================================
// �����L���O�I���̏I������
//==============================================================================
void CRankingSelect::Uninit(void)
{
	for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			delete m_apScene2D[nCnt];
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �����L���O�I���̍X�V����
//==============================================================================
void CRankingSelect::Update(void)
{
	// �I�����[�h�̐ݒ�
	SetMode();

	for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
	{
		// �F��Ԃ̐ݒ�
	//	m_apScene2D[nCnt]->SetCol(m_col);
		m_apScene2D[nCnt]->Update();
	}
}

//==============================================================================
// �����L���O�I���̕`�揈��
//==============================================================================
void CRankingSelect::Draw(void)
{
	for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Draw();
		}
	}
}

//==============================================================================
// �����L���O�I���̐�������
//==============================================================================
CRankingSelect *CRankingSelect::Create(void)
{
	// �C���X�^���X����
	CRankingSelect *pRankingSelect;
	pRankingSelect = new CRankingSelect;

	// ������
	if(pRankingSelect != NULL)
	{ 
		pRankingSelect->Init();
	}

	return pRankingSelect;
}

//==============================================================================
// �I����Ԃ��Ƃ̐ݒ�
//==============================================================================
void CRankingSelect::SetMode(void)
{
	// �t�F�[�h���̎擾
	CFade *pFade;
	pFade = CManager::GetFade();
	CFade::FADE fade = pFade->GetFade();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �J�[�\���̖���
	for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
	{
		if (nCnt == m_ranking)
		{// �I��
			if (m_bAlphaDown == true)
			{
				m_col.a -= 0.03f;
	
				// �_�ł̐܂�Ԃ�
				if (m_col.a <= 0.0f)
				{
					m_col.a = 0.0f;
					m_bAlphaDown = false;
				}
			}
			else
			{
				m_col.a += 0.03f;

				// �_�ł̐܂�Ԃ�
				if (m_col.a >= 1.0f)
				{
					m_col.a = 1.0f;


					m_bAlphaDown = true;
				}
			}

			m_apScene2D[nCnt]->SetTex(1, 2, 0, 0, 0.0f, 0.0f);
			m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_col.a));

		}
		else
		{// ����ȊO
			m_apScene2D[nCnt]->SetTex(1, 2, 0, 1, 0.0f, 0.0f);
			m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
		}
	}

	//	�I�������Ƃ̏���
	if (m_bOK == false)
	{
		// �J�[�\���̈ړ�
		if (keyboard->GetTrigger(CInput::KEYINFO_DOWN) == true || gamepad->GetTrigger(CInput::KEYINFO_DOWN) == true)
		{
			CSound::Play(CSound::SOUND_LABEL_SE_SELECT);
			m_ranking = (RANKING)(m_ranking + 1);
		}
		else if (keyboard->GetTrigger(CInput::KEYINFO_UP) == true || gamepad->GetTrigger(CInput::KEYINFO_UP) == true)
		{
			CSound::Play(CSound::SOUND_LABEL_SE_SELECT);
			m_ranking = (RANKING)(m_ranking - 1);
		}
	}

	// �J�[�\���̕␳
	if (m_ranking < 0)
	{
		m_ranking = (RANKING)(RANKING_MAX - 1);

	}
	else if (m_ranking >(RANKING_MAX - 1))
	{
		m_ranking = RANKING_RETRY;

	}

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		// ���菈��
		if (pFade->GetFade() == CFade::FADE_NONE && (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true))
		{
			// ���ʉ��̍Đ�
			CSound::Play(CSound::SOUND_LABEL_SE_DECIDE);

			m_bOK = true;
		}
	}

	//	�I�������Ƃ̏���
	if (m_bOK == true)
	{
		// �J�E���g���Z
		m_nCntTime++;

		if (m_ranking == RANKING_RETRY)
		{
			m_bSelect = true;

			if (m_bSelect == true)
			{
				// �J�E���g��5�Ŋ����0�ɂȂ�ꍇ
				if (m_nCntTime % 5 == 0)
				{
					// �F
					m_col.a = 1.0f;
				}
				else
				{

					// �F
					m_col.a = 0.5f;
				}

				// �J�E���g���w��l�𒴂����ꍇ
				if (m_nCntTime >= 50)
				{
					// �Q�[���̂�蒼��
					pFade->SetFade(CFade::FADE_OUT, CMode::MODE_GAME);
				}
			}
		}

		if (m_ranking == RANKING_QUIT)
		{
			if (m_bSelect == false)
			{
				// �J�E���g��5�Ŋ����0�ɂȂ�ꍇ
				if (m_nCntTime % 5 == 0)
				{
					// �F
					m_col.a = 1.0f;
				}
				else
				{
					// �F
					m_col.a = 0.5f;
				}

				// �J�E���g���w��l�𒴂����ꍇ
				if (m_nCntTime >= 50)
				{
					// �^�C�g���֖߂�
					pFade->SetFade(CFade::FADE_OUT, CMode::MODE_TITLE);
				}
			}
		}

	}

	if (fade == CFade::FADE_IN && (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true))
	{
		// �t�F�[�h�C���̃J�b�g
		pFade->FadeInCancel();
	}
}