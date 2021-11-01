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

#define SELECT_MAP_SIZE (D3DXVECTOR3(250, 250, 0))	// ステージのサイズ
#define SELECT_MAP_OFFSET (600)						// 中央から左右までのオフセット

#define SELECT_MAP1_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2 - SELECT_MAP_OFFSET, SCREEN_HEIGHT / 2, 0))	// ステージ１位置
#define SELECT_MAP2_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0))						// ステージ２位置
#define SELECT_MAP3_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2 + SELECT_MAP_OFFSET, SCREEN_HEIGHT / 2, 0))	// ステージ３位置

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

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	typedef enum {	// 配列の添え字用インデックス
		SELECT_IDX_BG = 0,
		SELECT_IDX_MAP1,
		SELECT_IDX_MAP2,
		SELECT_IDX_MAP3,

		SELECT_IDX_MAX,
	} SELECT_IDX;

	void SelectStage(STAGE_SELECT stage);

	CScene2D *m_apScene[SELECT_IDX_MAX];	// 2Dオブジェクト
	STAGE_SELECT m_currentStage;				// 現在選択しているステージ
	int m_nStage;
};

#endif


