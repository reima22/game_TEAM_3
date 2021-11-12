#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
//
// �X�e�[�W�Z���N�g [select.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "select.h"
#include "Manager.h"
#include "Input.h"
#include "Resource.h"
#include "fade.h"

//*****************************************************************************
// �X�e�[�W�Z���N�g�N���X ( �p���� [CScene] )
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStageSelect::CStageSelect()
{
	m_currentStage = STAGE_SELECT_1;
	m_bSelected = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStageSelect::~CStageSelect()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CStageSelect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// �w�i�I�u�W�F�N�g
	m_apScene[SELECT_IDX_BG] = CScene2D::Create(SELECT_BG_POSITION, VECTOR3_ZERO, SELECT_BG_SIZE);
	m_apScene[SELECT_IDX_BG]->BindTexture(CManager::GetResourceManager()->m_Texture_Map["TexTest01"]);
	m_apScene[SELECT_IDX_BG]->SetTextureUV(
		D3DXVECTOR2(0.0f, SCREEN_HEIGHT / m_apScene[SELECT_IDX_BG]->GetSize().y),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(SCREEN_WIDTH / m_apScene[SELECT_IDX_BG]->GetSize().x, SCREEN_HEIGHT / m_apScene[SELECT_IDX_BG]->GetSize().y),
		D3DXVECTOR2(SCREEN_WIDTH / m_apScene[SELECT_IDX_BG]->GetSize().x, 0.0f));
	m_apScene[SELECT_IDX_BG]->SetPriority(0);

	// �e�L�X�g��
	m_apScene[SELECT_IDX_TEXT] = CScene2D::Create(SELECT_TEXT_POSITION, VECTOR3_ZERO, SELECT_TEXT_SIZE);
	m_apScene[SELECT_IDX_TEXT]->BindTexture(CManager::GetResourceManager()->m_Texture_Map["StageText"]);

	// ���
	m_apScene[SELECT_IDX_ARROW] = CScene2D::Create(SELECT_MAP1_POSITION + SELECT_MAP_ARROW_OFFSET, VECTOR3_ZERO, SELECT_MAP_ARROW_SIZE);
	m_apScene[SELECT_IDX_ARROW]->BindTexture(CManager::GetResourceManager()->m_Texture_Map["Arrow"]);

	// �}�b�v1 (��)
	m_apScene[SELECT_IDX_MAP1] = CScene2D::Create(SELECT_MAP1_POSITION, VECTOR3_ZERO, SELECT_MAP_SIZE);
	m_apScene[SELECT_IDX_MAP1]->BindTexture(CManager::GetResourceManager()->m_Texture_Map["Stage1"]);

	// �}�b�v2 (�^��)
	m_apScene[SELECT_IDX_MAP2] = CScene2D::Create(SELECT_MAP2_POSITION, VECTOR3_ZERO, SELECT_MAP_SIZE);
	m_apScene[SELECT_IDX_MAP2]->BindTexture(CManager::GetResourceManager()->m_Texture_Map["Stage2"]);

	// �}�b�v3 (�E)
	m_apScene[SELECT_IDX_MAP3] = CScene2D::Create(SELECT_MAP3_POSITION, VECTOR3_ZERO, SELECT_MAP_SIZE);
	m_apScene[SELECT_IDX_MAP3]->BindTexture(CManager::GetResourceManager()->m_Texture_Map["Stage3"]);


	// �����I��
	SelectStage(STAGE_SELECT_1);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CStageSelect::Uninit(void)
{
	// �J��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CStageSelect::Update(void)
{
	CInputKeyboard *pKey = CManager::GetInputKeyboard();

	if (!m_bSelected) {
		// ����
		if (pKey->GetTrigger(DIK_RETURN)) {
			CManager::GetFade()->FadeOUT(CManager::MODE_GAME);
			m_bSelected = true;
		}

		// �I���X�e�[�W��ύX
		if (pKey->GetTrigger(DIK_D) || pKey->GetTrigger(DIK_RIGHT)) {
			m_currentStage = (STAGE_SELECT)(m_currentStage + 1);
		}
		else if (pKey->GetTrigger(DIK_A) || pKey->GetTrigger(DIK_LEFT)) {
			m_currentStage = (STAGE_SELECT)(m_currentStage - 1);
		}

		// �]����v�Z���ČJ��Ԃ��悤�ɂ���
		m_currentStage = (STAGE_SELECT)(m_currentStage % 3);
		if (m_currentStage == (STAGE_SELECT)-1) m_currentStage = STAGE_SELECT_3;

		// �I���X�e�[�W���g�k������
		StageScale(m_currentStage);

		// ���̈ʒu��ݒ�
		m_apScene[SELECT_IDX_ARROW]->SetPos(m_apScene[ToIdx(m_currentStage)]->GetPos() + SELECT_MAP_ARROW_OFFSET);
		WaveArrow();

	}
	else {
		// �I����͓_�ł�����
		StageBlink(m_currentStage);
	}
	
	// �w�i���X�N���[��
	static float fScroll;
	fScroll -= 0.001f;
	m_apScene[SELECT_IDX_BG]->SetTextureUV(
		D3DXVECTOR2(fScroll, SCREEN_HEIGHT / m_apScene[SELECT_IDX_BG]->GetSize().y + fScroll),
		D3DXVECTOR2(fScroll, fScroll),
		D3DXVECTOR2(SCREEN_WIDTH / m_apScene[SELECT_IDX_BG]->GetSize().x + fScroll, SCREEN_HEIGHT / m_apScene[SELECT_IDX_BG]->GetSize().y + fScroll),
		D3DXVECTOR2(SCREEN_WIDTH / m_apScene[SELECT_IDX_BG]->GetSize().x + fScroll, fScroll));
}

//=============================================================================
// �`�揈��
//=============================================================================
void CStageSelect::Draw(void)
{

}

//=============================================================================
// �X�e�[�W��I��
//=============================================================================
void CStageSelect::SelectStage(STAGE_SELECT stage)
{
	// �Y�����̃C���f�b�N�X�ɒ���
	SELECT_IDX stageIdx = ToIdx(stage);

	// �Y���I�u�W�F�N�g�̓T�C�Y�ƐF��ς���
	for (int nCnt = 0; nCnt < SELECT_IDX_MAX; nCnt++) {
		if (nCnt == stageIdx) {
			m_apScene[nCnt]->SetSize(SELECT_MAP_SIZE_SELECTED);
			m_apScene[nCnt]->SetColor(D3DXCOLOR(1, 1, 1, 1));
		}
		else {
			if (nCnt == SELECT_IDX_MAP1 || nCnt == SELECT_IDX_MAP2 || nCnt == SELECT_IDX_MAP3) {
				m_apScene[nCnt]->SetSize(SELECT_MAP_SIZE);
				m_apScene[nCnt]->SetColor(D3DXCOLOR(1, 1, 1, 0.5f));
			}
		}
			m_apScene[nCnt]->Update();
	}
}

//=============================================================================
// �T�C�Y���g��k������
//=============================================================================
void CStageSelect::StageScale(STAGE_SELECT stage)
{
	// �Y�����̃C���f�b�N�X�ɒ���
	SELECT_IDX stageIdx = ToIdx(stage);

	// �Y���I�u�W�F�N�g��sin�E�F�[�u���g���Ċg��k�����J��Ԃ�
	for (int nCnt = 0; nCnt < SELECT_IDX_MAX; nCnt++) {
		if (nCnt == stageIdx) {
			D3DXVECTOR3 size = m_apScene[nCnt]->GetSize();
			float fWave = sinf((float)timeGetTime() * SELECT_MAP_SIZE_FREQUENCY) * SELECT_MAP_SIZE_AMPLITUDE;
			size.x = SELECT_MAP_SIZE_SELECTED.x + fWave;
			size.y = SELECT_MAP_SIZE_SELECTED.y + fWave;
			m_apScene[nCnt]->SetSize(size);
			m_apScene[nCnt]->SetColor(D3DXCOLOR(1, 1, 1, 1));
		}
		else if (nCnt == SELECT_IDX_MAP1 || nCnt == SELECT_IDX_MAP2 || nCnt == SELECT_IDX_MAP3) {
			m_apScene[nCnt]->SetSize(SELECT_MAP_SIZE);
			m_apScene[nCnt]->SetColor(D3DXCOLOR(1, 1, 1, 0.5f));
		}
		m_apScene[nCnt]->Update();
	}

}

//=============================================================================
// �|���S����_�ł�����
//=============================================================================
void CStageSelect::StageBlink(STAGE_SELECT stage)
{
	// �Y�����ɒ���
	SELECT_IDX stageIdx = ToIdx(stage);

	// sin�E�F�[�u�ɂ������l��ݒ肵�ē_�ł�����
	for (int nCnt = 0; nCnt < SELECT_IDX_MAX; nCnt++) {
		if (nCnt == stageIdx) {
			float fWave = sinf((float)timeGetTime() * SELECT_MAP_BLINK_FREQUENCY);
			if (fWave > 0) {
				m_apScene[nCnt]->SetColor(D3DXCOLOR(1, 1, 1, 1));
			}
			else {
				m_apScene[nCnt]->SetColor(D3DXCOLOR(1, 1, 1, 0));
			}
		}
	}
}

//=============================================================================
// ����h�ꂳ����
//=============================================================================
void CStageSelect::WaveArrow(void)
{
	// sin�E�F�[�u�g���ėh�ꂳ����
	D3DXVECTOR3 arrowPos = m_apScene[SELECT_IDX_ARROW]->GetPos();

	float fWave = sinf((float)timeGetTime() * SELECT_MAP_ARROW_FREQUENCY) * SELECT_MAP_ARROW_AMPLITUDE;
	m_apScene[SELECT_IDX_ARROW]->SetPos(D3DXVECTOR3(arrowPos.x, arrowPos.y + fWave, arrowPos.z));
}

//=============================================================================
// �Y�����̃C���f�b�N�X�ɒ���
//=============================================================================
CStageSelect::SELECT_IDX CStageSelect::ToIdx(STAGE_SELECT stage)
{
	SELECT_IDX stageIdx;
	if (stage == STAGE_SELECT_1) {
		stageIdx = SELECT_IDX_MAP1;
	}
	else if (stage == STAGE_SELECT_2) {
		stageIdx = SELECT_IDX_MAP2;
	}
	else if (stage == STAGE_SELECT_3) {
		stageIdx = SELECT_IDX_MAP3;
	}

	return stageIdx;
}
