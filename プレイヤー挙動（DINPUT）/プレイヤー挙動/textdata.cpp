//==============================================================================
//
// テキストデータ管理〔textdata.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "textdata.h"
#include "textdata_player.h"
#include "textdata_system.h"
#include "textdata_object.h"
#include "stdio.h"

// 静的メンバ変数宣言
char *CTextData::m_pFileName[TEXTDATA_MAX] =
{
	{ "data/TEXT/ranking.txt" },	// ランキング
	{ "data/TEXT/systemdata.txt" },	// ルール管理
	{ "data/TEXT/playermen.txt" },	// プレイヤーデータ
	{ "data/TEXT/objectdata.txt" },	// 3Dオブジェクトデータ
};

CTextDataPlayer *CTextData::m_pDataPlayer = NULL;
CTextDataObject *CTextData::m_pDataObject = NULL;

//==============================================================================
// コンストラクタ
//==============================================================================
CTextData::CTextData()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CTextData::~CTextData()
{

}

//==============================================================================
// 生成処理
//==============================================================================
CTextData *CTextData::Create(void)
{
	// ローカル変数宣言
	CTextData *pTextData;
	pTextData = new CTextData;	// インスタンス生成

	// テキストデータ
	if (pTextData != NULL)
	{
		// テキストデータの読み込み
		pTextData->LoadTextAll();
	}

	return pTextData;
}

//==============================================================================
// テキストデータの全読み込み
//==============================================================================
void CTextData::LoadTextAll(void)
{
	// プレイヤーデータの生成
	m_pDataPlayer = CTextDataPlayer::Create();
	
	// オブジェクトデータの生成
	//m_pDataObject = CTextDataObject::Create();

	// ルールのデータ読み込み
	CTextDataSystem::LoadData();
}

//==============================================================================
// テキストデータの全読み込み
//==============================================================================
void CTextData::UninitAll(void)
{
	// プレイヤーデータの破棄
	if (m_pDataPlayer != NULL)
	{
		m_pDataPlayer->Uninit();
		m_pDataPlayer = NULL;
	}
	
	// オブジェクトデータの破棄
	if (m_pDataObject != NULL)
	{
		m_pDataObject->Uninit();
		m_pDataObject = NULL;
	}
}