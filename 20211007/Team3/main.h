//===================================================================
//HeaderFile: main.h
//Author : Yo jitaku
//===================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*******************************************************************
// ヘッダファイルのインクルード
//*******************************************************************
#include <Windows.h>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <list>
#include <unordered_map>
#include <string>
#include <thread>
#include <memory>
#include "d3dx9.h"
#include "d3dx9math.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "xaudio2.h"


//*******************************************************************
//名前空間
//*******************************************************************
using namespace std;

//*******************************************************************
// ライブラリファイルのリンク
//*******************************************************************
#pragma comment(lib, "d3d9.lib")	// 描画処理に必要
#pragma comment(lib, "d3dx9.lib")	// 拡張ライブラリ
#pragma comment(lib, "dxguid.lib")	// コンポーネント使用に必要
#pragma comment(lib, "dinput8.lib")	// 入力処理に必要
#pragma comment(lib, "winmm.lib")

//******************************************************************
// マクロ定義
//******************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				// 頂点フォーマット
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// 頂点フォーマット3D
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define WINDOW_POS_X (1)			// ウィンドウ左上X座標
#define WINDOW_POS_Y (1)			// ウィンドウ左上Y座標
#define VECTOR3_ZERO (D3DXVECTOR3(0,0,0))

//******************************************************************
// プロトタイプ宣言
//******************************************************************
#ifdef _DEBUG	
int GetFps();
#endif

#endif