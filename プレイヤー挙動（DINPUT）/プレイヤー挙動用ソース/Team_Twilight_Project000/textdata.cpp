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
// テクスチャデータの全読み込み
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