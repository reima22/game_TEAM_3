//===================================================================
//HeaderFile: ResourceManager.h
//Author : Yo jitaku
//===================================================================
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_
#include "main.h"
//#include "Sound.h"
#define KEY_NUM_MAX 10
#define MODEL_PARTS_MAX 10

//*******************************************************************
//先方宣言
//*******************************************************************
class CRenderer;
//*******************************************************************
//SoundのDataクラス
//*******************************************************************
//class CSoundData
//{
//public:
//	CSoundData() : m_pSourceVoice(nullptr), m_pDataAudio(nullptr), m_SizeAudio(NULL) {};
//	IXAudio2SourceVoice* m_pSourceVoice;
//	BYTE* m_pDataAudio;
//	DWORD m_SizeAudio;
//};

//*******************************************************************
//ModelのDataクラス
//*******************************************************************
class CModelData
{
public:
	CModelData() :
		Xfile_Mesh(nullptr),
		Xfile_Materials(nullptr),
		Xfile_MaterialNum(0),
		m_nPartIndex(0),
		m_nPartParent(0),
		m_sName(""),
		m_nPartPos(D3DXVECTOR3(0, 0, 0)),
		m_nPartRot(D3DXVECTOR3(0, 0, 0)) {}

	LPD3DXMESH Xfile_Mesh;						//mesh
	LPD3DXBUFFER Xfile_Materials;				//材質buffer
	DWORD Xfile_MaterialNum;					//材質num
	LPDIRECT3DTEXTURE9 g_Textures[10] = {};		//UV画像

												//MODEL_PLUS
	int m_nPartIndex;							//パーツの番号
	int m_nPartParent;							//親パーツの番号
	char m_sName[128];							//パーツの名前
	D3DXVECTOR3 m_nPartPos;						//パーツの相対座標
	D3DXVECTOR3 m_nPartRot;						//パーツの相対角度
	D3DXMATRIX m_MtxWorldParts;					//パーツの世界マトリックス
};

//*******************************************************************
//MotionのDataクラス
//*******************************************************************
class CMotionData
{
public:
	typedef struct
	{
		//位置
		float fPosX;
		float fPosY;
		float fPosZ;
		//向き
		float fRotX;
		float fRotY;
		float fRotZ;
	}KEY;								//キーの構造体

	typedef struct
	{
		int nFrameSpeed;				//motion速度
		KEY akey[MODEL_PARTS_MAX];		//パーツ数
	}KEY_INFO;							//キーフレーム

	bool m_bLoop;						//Motion循環再生
	int m_nNumKey;						//キーフレームの番号
	int m_nMaxKey;						//キーフレームの総数
	KEY_INFO m_aKeyInfo[KEY_NUM_MAX];	//キー情報を保存している配列
};

//*******************************************************************
//ModelPlusのDataクラス (Motionつけのmodel)
//*******************************************************************
class CModelDataPlus
{
public:
	CModelDataPlus() :
		m_nParts(0) {}
	CModelData m_PartsData;							//パーツのモード情報
	CMotionData m_MotionData;						//パーツのモーション情報
	int m_nParts;									//パーツの総数
	unordered_map<int, CModelData> m_Parts_Map;		//パーツのモード情報を保存しているmap
	unordered_map<string, CMotionData> m_Motion_Map;//パーツのモーション情報を保存しているmap
};

//*******************************************************************
//ResourceManagerクラスの宣言
//*******************************************************************
class CResourceManager
{
public:
	static CResourceManager* GetInstance()			//singletonインタフェース
	{
		static CResourceManager Instance;
		return &Instance;
	}
	HRESULT Init();									//初期化
	HRESULT Uninit();								//解放
	HRESULT TextureLoader(string filename);			//Textureを外部ファイルから読み込と初期化の関数
	//HRESULT SoundLoader(string filename);			//Soundを外部ファイルから読み込と初期化の関数
	HRESULT ModelLoader(string filename);			//3DModelを外部ファイルから読み込と初期化の関数
	HRESULT ModelLoaderPlus(string filename);		//階層有りXFileの読み込初期化の関数

													//初期化した変数のpointerを保存するMapコンテナ
	unordered_map<string, LPDIRECT3DTEXTURE9> m_Texture_Map;//画像を保存しているmap
	//unordered_map<string, CSoundData*> m_Sound_Map;			//音声を保存しているmap
	unordered_map<string, CModelData*> m_Model_Map;			//モードを保存しているmap
	unordered_map<string, CModelDataPlus*> m_PartsModel_Map;//モーションつけモードを保存しているmap
private:
	CResourceManager() {};
	~CResourceManager() {};

	CRenderer* m_pRender;
	LPDIRECT3DDEVICE9 m_pDevice;

	//当たり判定ボックスを作る
	//Sound処理初期化に関する関数
	//HRESULT CheckSoundChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	//HRESULT ReadSoundChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
};
#endif#pragma once
