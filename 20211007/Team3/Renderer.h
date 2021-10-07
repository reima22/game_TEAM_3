//===================================================================
//HeaderFile: Renderer.h
//Author : Yo jitaku
//===================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"
#include "d3dx9.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")//D3DXCreateTextureFromFile

//*******************************************************************
//先方宣言
//*******************************************************************
class CSceneManager;
//*******************************************************************
//レンダリングスクリーンのクラス
//*******************************************************************
class CRenderer
{
public:
	static CRenderer* GetInstance() //singletonインタフェース
	{
		static CRenderer Instance;
		return &Instance;
	}
	HRESULT Init(HWND hWnd, bool bWindow);		//初期化
	HRESULT Uninit();							//解放
	void Draw();								//描画
	LPDIRECT3DDEVICE9 GetDevice() {
		return m_pD3DDevice;
	}											//デバイスを取る
private:
	CRenderer() {};
	~CRenderer() {};

	LPDIRECT3D9				  m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		  m_pD3DDevice;		// Deviceオブジェクト(描画に必要)											
	LPD3DXFONT				  m_pFont;			// フォントへのポインタ
	CSceneManager*			  m_pSceneManager;	// シーンマネージャーのポインタ
#ifdef _DEBUG
	void DrawDebugInfo();						// debugモード
#endif
};
#endif