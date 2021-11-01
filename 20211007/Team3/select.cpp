//=============================================================================
//
// ステージセレクト [select.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "select.h"
#include "Manager.h"
#include "Input.h"

//*****************************************************************************
// ステージセレクトクラス ( 継承元 [CScene] )
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CStageSelect::CStageSelect()
{
	m_currentStage = STAGE_SELECT_1;
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
	// 2Dオブジェクト生成
	for (int nCnt = 0; nCnt < SELECT_IDX_MAX; nCnt++) {
		
		if (nCnt == SELECT_IDX_BG) {
			m_apScene[nCnt] = CScene2D::Create(SELECT_BG_POSITION, VECTOR3_ZERO, SELECT_BG_SIZE);
			m_apScene[SELECT_IDX_BG]->SetColor(D3DXCOLOR(0, 1, 0, 1));
			m_apScene[SELECT_IDX_BG]->SetPriority(0);
		}
		else if (nCnt == SELECT_IDX_MAP1){
			m_apScene[nCnt] = CScene2D::Create(SELECT_MAP1_POSITION, VECTOR3_ZERO, SELECT_MAP_SIZE);
		}
		else if (nCnt == SELECT_IDX_MAP2) {
			m_apScene[nCnt] = CScene2D::Create(SELECT_MAP2_POSITION, VECTOR3_ZERO, SELECT_MAP_SIZE);
		}
		else if (nCnt == SELECT_IDX_MAP3) {
			m_apScene[nCnt] = CScene2D::Create(SELECT_MAP3_POSITION, VECTOR3_ZERO, SELECT_MAP_SIZE);
		}
	}

	SelectStage(STAGE_SELECT_1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStageSelect::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CStageSelect::Update(void)
{
	CInputKeyboard *pKey = CManager::GetInputKeyboard();

	// 決定
	if (pKey->GetTrigger(DIK_RETURN)) {
		//m_currentStageのステージに遷移
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

	// 反映
	SelectStage(m_currentStage);
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
	//else {
	//	stageIdx = SELECT_IDX_MAP1;
	//}

	for (int nCnt = 0; nCnt < SELECT_IDX_MAX; nCnt++) {
		if (nCnt == stageIdx) {
			m_apScene[nCnt]->SetColor(D3DXCOLOR(1,1,1,1));
		}
		else {
			m_apScene[nCnt]->SetColor(D3DXCOLOR(1, 1, 1, 0.5f));
		}
	}
}