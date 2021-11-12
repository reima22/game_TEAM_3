#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
//
// ステージセレクト [select.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "select.h"
#include "Manager.h"
#include "Input.h"
#include "Resource.h"
#include "fade.h"

//*****************************************************************************
// ステージセレクトクラス ( 継承元 [CScene] )
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CStageSelect::CStageSelect()
{
	m_currentStage = STAGE_SELECT_1;
	m_bSelected = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CStageSelect::~CStageSelect()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStageSelect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// 背景オブジェクト
	m_apScene[SELECT_IDX_BG] = CScene2D::Create(SELECT_BG_POSITION, VECTOR3_ZERO, SELECT_BG_SIZE);
	m_apScene[SELECT_IDX_BG]->BindTexture(CManager::GetResourceManager()->m_Texture_Map["TexTest01"]);
	m_apScene[SELECT_IDX_BG]->SetTextureUV(
		D3DXVECTOR2(0.0f, SCREEN_HEIGHT / m_apScene[SELECT_IDX_BG]->GetSize().y),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(SCREEN_WIDTH / m_apScene[SELECT_IDX_BG]->GetSize().x, SCREEN_HEIGHT / m_apScene[SELECT_IDX_BG]->GetSize().y),
		D3DXVECTOR2(SCREEN_WIDTH / m_apScene[SELECT_IDX_BG]->GetSize().x, 0.0f));
	m_apScene[SELECT_IDX_BG]->SetPriority(0);

	// テキスト板
	m_apScene[SELECT_IDX_TEXT] = CScene2D::Create(SELECT_TEXT_POSITION, VECTOR3_ZERO, SELECT_TEXT_SIZE);
	m_apScene[SELECT_IDX_TEXT]->BindTexture(CManager::GetResourceManager()->m_Texture_Map["StageText"]);

	// 矢印
	m_apScene[SELECT_IDX_ARROW] = CScene2D::Create(SELECT_MAP1_POSITION + SELECT_MAP_ARROW_OFFSET, VECTOR3_ZERO, SELECT_MAP_ARROW_SIZE);
	m_apScene[SELECT_IDX_ARROW]->BindTexture(CManager::GetResourceManager()->m_Texture_Map["Arrow"]);

	// マップ1 (左)
	m_apScene[SELECT_IDX_MAP1] = CScene2D::Create(SELECT_MAP1_POSITION, VECTOR3_ZERO, SELECT_MAP_SIZE);
	m_apScene[SELECT_IDX_MAP1]->BindTexture(CManager::GetResourceManager()->m_Texture_Map["Stage1"]);

	// マップ2 (真ん中)
	m_apScene[SELECT_IDX_MAP2] = CScene2D::Create(SELECT_MAP2_POSITION, VECTOR3_ZERO, SELECT_MAP_SIZE);
	m_apScene[SELECT_IDX_MAP2]->BindTexture(CManager::GetResourceManager()->m_Texture_Map["Stage2"]);

	// マップ3 (右)
	m_apScene[SELECT_IDX_MAP3] = CScene2D::Create(SELECT_MAP3_POSITION, VECTOR3_ZERO, SELECT_MAP_SIZE);
	m_apScene[SELECT_IDX_MAP3]->BindTexture(CManager::GetResourceManager()->m_Texture_Map["Stage3"]);


	// 初期選択
	SelectStage(STAGE_SELECT_1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStageSelect::Uninit(void)
{
	// 開放
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CStageSelect::Update(void)
{
	CInputKeyboard *pKey = CManager::GetInputKeyboard();

	if (!m_bSelected) {
		// 決定
		if (pKey->GetTrigger(DIK_RETURN)) {
			CManager::GetFade()->FadeOUT(CManager::MODE_GAME);
			m_bSelected = true;
		}

		// 選択ステージを変更
		if (pKey->GetTrigger(DIK_D) || pKey->GetTrigger(DIK_RIGHT)) {
			m_currentStage = (STAGE_SELECT)(m_currentStage + 1);
		}
		else if (pKey->GetTrigger(DIK_A) || pKey->GetTrigger(DIK_LEFT)) {
			m_currentStage = (STAGE_SELECT)(m_currentStage - 1);
		}

		// 余りを計算して繰り返すようにする
		m_currentStage = (STAGE_SELECT)(m_currentStage % 3);
		if (m_currentStage == (STAGE_SELECT)-1) m_currentStage = STAGE_SELECT_3;

		// 選択ステージを拡縮させる
		StageScale(m_currentStage);

		// 矢印の位置を設定
		m_apScene[SELECT_IDX_ARROW]->SetPos(m_apScene[ToIdx(m_currentStage)]->GetPos() + SELECT_MAP_ARROW_OFFSET);
		WaveArrow();

	}
	else {
		// 選択後は点滅させる
		StageBlink(m_currentStage);
	}
	
	// 背景をスクロール
	static float fScroll;
	fScroll -= 0.001f;
	m_apScene[SELECT_IDX_BG]->SetTextureUV(
		D3DXVECTOR2(fScroll, SCREEN_HEIGHT / m_apScene[SELECT_IDX_BG]->GetSize().y + fScroll),
		D3DXVECTOR2(fScroll, fScroll),
		D3DXVECTOR2(SCREEN_WIDTH / m_apScene[SELECT_IDX_BG]->GetSize().x + fScroll, SCREEN_HEIGHT / m_apScene[SELECT_IDX_BG]->GetSize().y + fScroll),
		D3DXVECTOR2(SCREEN_WIDTH / m_apScene[SELECT_IDX_BG]->GetSize().x + fScroll, fScroll));
}

//=============================================================================
// 描画処理
//=============================================================================
void CStageSelect::Draw(void)
{

}

//=============================================================================
// ステージを選択
//=============================================================================
void CStageSelect::SelectStage(STAGE_SELECT stage)
{
	// 添え字のインデックスに直す
	SELECT_IDX stageIdx = ToIdx(stage);

	// 該当オブジェクトはサイズと色を変える
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
// サイズを拡大縮小する
//=============================================================================
void CStageSelect::StageScale(STAGE_SELECT stage)
{
	// 添え字のインデックスに直す
	SELECT_IDX stageIdx = ToIdx(stage);

	// 該当オブジェクトはsinウェーブを使って拡大縮小を繰り返す
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
// ポリゴンを点滅させる
//=============================================================================
void CStageSelect::StageBlink(STAGE_SELECT stage)
{
	// 添え字に直す
	SELECT_IDX stageIdx = ToIdx(stage);

	// sinウェーブにしきい値を設定して点滅させる
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
// 矢印を揺れさせる
//=============================================================================
void CStageSelect::WaveArrow(void)
{
	// sinウェーブ使って揺れさせる
	D3DXVECTOR3 arrowPos = m_apScene[SELECT_IDX_ARROW]->GetPos();

	float fWave = sinf((float)timeGetTime() * SELECT_MAP_ARROW_FREQUENCY) * SELECT_MAP_ARROW_AMPLITUDE;
	m_apScene[SELECT_IDX_ARROW]->SetPos(D3DXVECTOR3(arrowPos.x, arrowPos.y + fWave, arrowPos.z));
}

//=============================================================================
// 添え字のインデックスに直す
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
