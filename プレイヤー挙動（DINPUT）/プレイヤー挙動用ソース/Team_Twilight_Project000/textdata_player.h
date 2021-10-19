//=============================================================================
//
// テキストデータ（プレイヤー）管理 [textdata_player.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_PLAYER_H_
#define _TEXTDATA_PLAYER_H_

#include "main.h"
#include "player.h"
#include "textdata.h"

//==============================================================================
// テキスト管理（プレイヤー）クラス
//==============================================================================
class CTextDataPlayer : public CTextData
{
public:
	// プレイヤーデータの種類
	typedef enum
	{
		PLAYERDATA_MAX
	}PLAYERDATA;

	typedef enum
	{
		INFO_POS_X = 0, // posX
		INFO_POS_Y,		// posY
		INFO_POS_Z,		// posZ
		INFO_ROT_X,		// rotX
		INFO_ROT_Y,		// rotY
		INFO_ROT_Z,		// rotZ
		INFOMAX
	}INFO;

	CTextDataPlayer();
	~CTextDataPlayer();

	// テキストの読み込み
	void LoadData(void);
	void Uninit(void);
	
	// プレイヤーデータの生成
	static CTextDataPlayer *Create(void);

	// 読み込んだ値の取得
	char *GetFileName(int nIdx) { return m_pFileModelName[nIdx]; }			// ファイル名
	int GetPartsNum(void) { return m_nNumParts; }							// パーツ数
	int GetIndex(int nIdx) { return m_pIdx[nIdx]; }							// インデックス
	int GetParent(int nIdx) { return m_pParentIdx[nIdx]; }					// 親のインデックス
	float GetOffset(int nIdx, int nInfo) { return m_pOffset[nIdx][nInfo]; }	// オフセット情報

	// モーション情報
	bool GetLoop(CPlayer::MOTIONTYPE motionType) { return m_bLoop[motionType]; }
	int GetNumKey(CPlayer::MOTIONTYPE motionType) { return m_nNumKey[motionType]; }
	
	float GetKeyInfo(CPlayer::MOTIONTYPE motionType,
		int nKey, int nParts, CPlayer::KEY keyInfo) { return m_pKey[motionType][nKey][nParts][keyInfo]; }
	
	int GetFrame(CPlayer::MOTIONTYPE motionType,int nKey) { return m_pFrame[motionType][nKey]; }

private:
	int m_nNumModel;			// モデル数
	
	char **m_pFileModelName;	// Xファイル名ポインタ
	char **m_aFileName;			// ファイル名変数

	int m_nNumParts;			// パーツ数

	int *m_pIdx;				// インデックス
	int *m_pParentIdx;			// 親のインデックス
	float **m_pOffset;			// オフセット情報

	int m_nModelCnt;			// モデルファイル名カウンタ
	int m_nPartsCnt;			// 読み込んだパーツの数カウンタ

	// モーション情報
	int m_nNumKey[CPlayer::MOTIONTYPE_MAX];		// キー数
	float ***m_pKey[CPlayer::MOTIONTYPE_MAX];		// キー要素
	bool m_bLoop[CPlayer::MOTIONTYPE_MAX];		// モーションがループするか
	int *m_pFrame[CPlayer::MOTIONTYPE_MAX];		// モーションフレーム		
												
	int m_nKeyCnt;								// 読み取るキー数カウント
	int m_nMotionCnt;							// 読み取るモーションカウント
};

#endif
