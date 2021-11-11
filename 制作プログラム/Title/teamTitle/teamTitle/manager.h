//--------------------------------------------------------------------------------
//
// ゲーム制作[manager.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//前方宣言
//--------------------------------------------------------------------------------
class CRenderer;
class CInputKeyBoard;
class CFade;
class CBg;
class CTitle;
class CTutorial;
class CSound;
class CLight;
class CCamera;

//================================================================================
//オブジェクトクラス
//================================================================================
class CManager
{

public:

	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,													//チュートリアルモード
		MODE_MAX
	}Mode;

	CManager();															//コンストラクタ
	~CManager();														//デストラクタ

	HRESULT Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow);			//初期化処理
	void Uninit(void);													//終了処理
	void Update(void);													//更新処理
	void Draw(void);													//描画処理

	static CRenderer *GetRenderer(void);								//Rendererクラスの情報
	static CInputKeyBoard*GetInputKeyBoard(void);						//入力情報
	static CFade*GetFade(void) { return m_pFade; }						//フェード情報

	static void SetMode(Mode mode);
	static Mode GetMode(void) { return m_Mode; }						//モードの取得

	static void SetSound(CSound*sound) { m_pSound = sound; }			//サウンドの取得
	static CSound*GetSound(void) { return m_pSound; }					//サウンドの情報

	static CCamera*GetCamera(void) { return m_pCamera; }				//カメラの情報

private:

	static CTitle*m_pTitle;												// タイトルのポインタ
	static CTutorial*m_pTutorial;										// チュートリアルのポインタ
	static Mode m_Mode;													// モードのポインタ
	static CFade*m_pFade;												// フェードのポインタ
	static CRenderer*m_pRenderer;										// Renererのポインタ
	static CInputKeyBoard*m_pInputKeyBoard;								// キーボードのポインタ
	static CSound*m_pSound;												// BGMのポインタ
	static CLight*m_pLight;												// ライトのポインタ
	static CCamera*m_pCamera;											// カメラのポインタ

};

//--------------------------------------------------------------------------------
//プロトタイプ宣言
//--------------------------------------------------------------------------------
#endif
