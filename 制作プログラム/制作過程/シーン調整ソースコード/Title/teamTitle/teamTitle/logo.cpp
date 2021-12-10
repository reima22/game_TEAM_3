//=============================================================================
//
// ���C������ [bg.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "logo.h"
#include "scene2D.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLogo::m_apTexture[MAX_LOGO] = {};			// �e�N�X�`��

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CLogo::CLogo(int nPriority) :CScene(nPriority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CLogo::~CLogo()
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CLogo *CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, LOGOTYPE LogoType)
{
	// ���I�m��
	CLogo* pLogo;
	pLogo = new CLogo;

	// �����̌Ăяo��
	pLogo->Init(pos, scale);

	// ���S���̌Ăяo��
	pLogo->SetInfoType(LogoType);

	// �l��Ԃ�
	return pLogo;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// �傫��
	m_scale = scale;

	// �ړ��l
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Enter�����������ǂ���
	m_bEnter = false;

	// �`���[�g���A����ʂɈړ��������ǂ���
	m_bTutorial = false;

	// �W�����v����
	m_bJump = false;

	// ����_�Ŏ���
	m_nTimeColor = 0;

	// �ҋ@�_�ŃJ�E���g
	m_nCntColor = 0;

	// �^�C�}�[
	m_nTimer = 0;

	// �W�����v�J�E���g
	m_nJumpCnt = 0;

	// �o���J�E���g
	m_nAppearanceCnt = 0;

	// �ړ����x
	m_fSpd = 0.0f;

	// ���
	SetObjType(OBJTYPE_LOGO);

	// �w�i�̐؂�ւ�
	switch (CManager::GetMode())
	{
		// �^�C�g����ʂ������ꍇ
		case CManager::MODE_TITLE:

			for (int nCnt = 0; nCnt <3; nCnt++)
			{
				if (m_apScene2D[nCnt] == NULL)
				{
					m_apScene2D[nCnt] = new CScene2D;
					m_apScene2D[nCnt]->Init(pos,scale);
					m_apScene2D[nCnt]->BindTexture(m_apTexture[m_LogoType]);
				}
			}

		break;
	}

	// �l��Ԃ�
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CLogo::Uninit(void)
{

	// �w�i�̐؂�ւ�
	switch (CManager::GetMode())
	{
		// �^�C�g����ʂ������ꍇ
	case CManager::MODE_TITLE:

		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			if (m_apScene2D[nCnt] == NULL)
			{
				m_apScene2D[nCnt] = new CScene2D;
				m_apScene2D[nCnt]->Uninit();
				m_apScene2D[nCnt]->BindTexture(m_apTexture[m_LogoType]);
			}
		}

		break;

	}

	Release();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CLogo::Update(void)
{
	// ���͏��
	CInputKeyBoard *pKeyBoard;
	pKeyBoard = CManager::GetInputKeyBoard();

	//// �T�E���h�̃|�C���^
	//CSound *pSound = CManager::GetSound();

	// �ʒu�̎擾
	D3DXVECTOR3 pos;
	pos = m_apScene2D[0]->GetPosition();

	// �w�i�̐؂�ւ�
	switch (CManager::GetMode())
	{
		// �^�C�g����ʂ������ꍇ
	case CManager::MODE_TITLE:

		// �^�C�}�[
		m_nTimer++;


			// ���S�^�C�v��STATE�̏ꍇ
			if (m_LogoType == LOGOTYPE_START)
			{

				// �e�N�X�`��
				m_apScene2D[0]->BindTexture(m_apTexture[0]);

				// ���肪true�̏ꍇ
				if (m_bEnter == true && pKeyBoard->GetTrigger(DIK_RETURN) == true)
				{
					// �����true�ɕς���
					m_bTutorial = true;

					////SE
					//pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON);
				}
				else if (m_bEnter == false)
				{// ���肪false�̏ꍇ

					// �G���^�[�L�[���������ꍇ
					if (pKeyBoard->GetTrigger(DIK_RETURN) == true)
					{
						// �����true�ɕς���
						m_bEnter = true;

						// �J�E���g�̒l��0�ɂ���
						m_nTimeColor = 0;

					}

				}

				// ���肪�ǂ����true�̏ꍇ
				if (m_bEnter == true && m_bTutorial == true)
				{
					// �J�E���g���Z
					m_nTimeColor++;

					// �J�E���g��5�Ŋ����0�ɂȂ�ꍇ
					if (m_nTimeColor % 5 == 0)
					{
						// �F
						m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}
					else
					{
						// �F
						m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					}

					// �J�E���g��50�𒴂����ꍇ
					if (m_nTimeColor >= TIME_COLOR)
					{
						// �t�F�[�h
						CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE);

						// �����false�ɕς���
						m_bEnter = false;

						// �����false�ɕς���
						m_bTutorial = false;

						// �^�C�}�[��0�ɂ���
						m_nTimer = 0;
					}
				}

				// �ʒu�������������ʒu�ɂ��邩���肪false�̏ꍇ
				if (pos.y > POS_START_Y && m_bEnter == false)
				{
					// �ړ��l
					m_move.y = MOVE_START_Y;

					// �F
					m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				}
				else
				{
					// �ʒu��^����
					pos.y = POS_START_Y;

					// �ړ��l
					m_move.y = 0.0f;

					// �����true�ɕς���
					m_bEnter = true;

					//�ҋ@�_�ŃJ�E���g
					m_nCntColor++;
				}

				// ���肪true�ł͂Ȃ��ꍇ
				if (m_bTutorial != true)
				{
					// �J�E���g���w��l���Ⴂ�ꍇ�ꍇ
					if (m_nCntColor <= 50)
					{
						// �F
						m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, (1.0f / ((float)m_nCntColor *0.75f)));
					}
					
					if (m_nCntColor > 50 && m_nCntColor <= 100)
					{// �J�E���g���w��l�͈͓̔��̏ꍇ

						// �F
						m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, (0.0001f * ((float)m_nCntColor * 100.0f)));
					}
					else if (m_nCntColor > 150)
					{ //�J�E���g���w��l�𒴂��Ă���ꍇ

						//�J�E���g��0�ɂ���
						m_nCntColor = 0;
					}
				}

			}

		// ���S�^�C�v��TITLENAME�̏ꍇ
		if (m_LogoType == LOGOTYPE_TITLENAME)
		{
			// �e�N�X�`��
			m_apScene2D[0]->BindTexture(m_apTexture[1]);

			// �F
			m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// Enter���������A�ʒu���w��l���E�������ꍇ
			if (pKeyBoard->GetTrigger(DIK_RETURN) == true || pos.x > POS_TITLE_X)
			{
				// �ړ��l
				m_move.x = 0.0f;
				m_move.y = 0.0f;

				// �ʒu��^����
				pos.x = POS_TITLE_X;
				pos.y = POS_TITLE_Y;

				//	�J�E���g
				m_nAppearanceCnt = 1;
				
			}
			else  if(pos.x < POS_TITLE_X)
			{// �ʒu���w��l��荶�������ꍇ

				// �d��
				float fGravity = GRAVITY;
				
				// �J�E���g�l�����l��������Ă���ꍇ
				if (m_nJumpCnt <= 0)
				{
					// ���x
					m_fSpd = MOVE_SPEED;
				}

				// ���x�ɏd�͂���
				m_fSpd += fGravity;

				// �ʒu���w��l���������ꍇ
				if (pos.y > POS_TITLE_Y)
				{
					// ���x�ɑ��
					m_fSpd = -m_fSpd;

					// �J�E���g���Z
					m_nJumpCnt++;
				}	

				// �ړ��l
				m_move.x += MOVE_TITLE_X;
				m_move.y = m_fSpd + (m_nJumpCnt / 1.2f);
			}
		}

		break;
	}

	// �ړ��l���ʒu���W�ɑ���
	pos += m_move;

	// �ʒu����^����
	m_apScene2D[0]->SetPosition(pos, m_scale);

	// �F
	m_apScene2D[0]->SetColor(m_Color);

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CLogo::Draw(void)
{
}

//*****************************************************************************
// �e�N�X�`���ǂݍ��ݏ���
//*****************************************************************************
HRESULT CLogo::Load(void)
{
	//�f�o�C�X�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\TitleLogo02.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\TitleLogo01.png", &m_apTexture[1]);

	return S_OK;
}

//*****************************************************************************
// �e�N�X�`���j������
//*****************************************************************************
void CLogo::Unload(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_LOGO; nCnt++)
	{
		//�e�N�X�`���̊J��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}