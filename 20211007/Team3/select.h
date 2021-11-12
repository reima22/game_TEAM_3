//=============================================================================
//
// ステージセレクト [select.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

//*****************************************************************************
// ヘッダのインクルード
//*****************************************************************************
#include "main.h"
#include "Scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SELECT_BG_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0))			// 背景位置
#define SELECT_BG_SIZE (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0))				// 背景サイズ

#define SELECT_TEXT_SIZE (D3DXVECTOR3(300, 80, 0))						// テキスト板ポリゴンのサイズ
#define SELECT_TEXT_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, 150, 0))	// 　　　　　　　　　　位置

#define SELECT_MAP_SIZE (D3DXVECTOR3(250, 250, 0))			// ステージのサイズ
#define SELECT_MAP_SIZE_SELECTED (D3DXVECTOR3(300, 300, 0))	// 選択時のサイズ
#define SELECT_MAP_SIZE_AMPLITUDE (10)						// 選択時のサイズの振れ幅
#define SELECT_MAP_SIZE_FREQUENCY (0.01f)					// サイズの変更する速度
#define SELECT_MAP_BLINK_FREQUENCY (1.0f)					// ポリゴン点滅の速度

#define SELECT_MAP_ARROW_SIZE (D3DXVECTOR3(40, 60, 0))		// 矢印のサイズ
#define SELECT_MAP_ARROW_OFFSET (D3DXVECTOR3(0, -380, 0))	// 矢印の位置オフセット
#define SELECT_MAP_ARROW_AMPLITUDE (10)						// 矢印の揺れの振れ幅
#define SELECT_MAP_ARROW_FREQUENCY (0.01f)					// 矢印の揺れの頻度

#define SELECT_MAP_OFFSET (D3DXVECTOR3(600, 150, 0))		// マップのポリゴン位置オフセット
#define SELECT_MAP1_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2 - SELECT_MAP_OFFSET.x, SCREEN_HEIGHT / 2 + SELECT_MAP_OFFSET.y, 0))	// ステージ１位置
#define SELECT_MAP2_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SELECT_MAP_OFFSET.y, 0))						// ステージ２位置
#define SELECT_MAP3_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2 + SELECT_MAP_OFFSET.x, SCREEN_HEIGHT / 2 + SELECT_MAP_OFFSET.y, 0))	// ステージ３位置

//*****************************************************************************
// ステージセレクトクラス
//*****************************************************************************
class CStageSelect : public CScene
{
public:
	// ステージの種類
	typedef enum {
		STAGE_SELECT_1 = 0,
		STAGE_SELECT_2,
		STAGE_SELECT_3,
		
		STAGE_SELECT_MAX,
	} STAGE_SELECT;

	CStageSelect();
	~CStageSelect();

	STAGE_SELECT GetSelectingStage(void) { return m_currentStage; }	// 選択しているステージを取得

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	typedef enum {	// 配列の添え字用インデックス
		SELECT_IDX_BG = 0,
		SELECT_IDX_TEXT,
		SELECT_IDX_MAP1,
		SELECT_IDX_MAP2,
		SELECT_IDX_MAP3,
		SELECT_IDX_ARROW,

		SELECT_IDX_MAX,
	} SELECT_IDX;

	void SelectStage(STAGE_SELECT stage);	// ステージ選択
	void StageScale(STAGE_SELECT stage);	// ステージの拡縮
	void StageBlink(STAGE_SELECT stage);	// ステージの点滅
	void WaveArrow(void);					// 矢印を揺れさせる

	SELECT_IDX ToIdx(STAGE_SELECT stage);

	CScene2D *m_apScene[SELECT_IDX_MAX];	// 2Dオブジェクト
	STAGE_SELECT m_currentStage;			// 現在選択しているステージ
	bool m_bSelected;
};

#endif


