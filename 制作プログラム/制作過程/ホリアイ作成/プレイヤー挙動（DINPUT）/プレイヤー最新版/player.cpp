//==============================================================================
//
// プレイヤー管理〔player.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "model.h"
#include "input.h"
#include "gamepad.h"
#include "textdata_player.h"
#include "textdata_object.h"
#include "camera.h"
#include "shadow.h"
#include "collision.h"
#include "game.h"
#include "object.h"
#include "Terrain.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CPlayer::CPlayer()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CPlayer::~CPlayer()
{

}

//==============================================================================
// プレイヤーの初期化処理
//==============================================================================
HRESULT CPlayer::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テキストデータの取得
	CTextDataPlayer *pDataPlayer = CTextDataPlayer::GetDataPlayer();

	// パーツ数
	m_nNumParts = pDataPlayer->GetPartsNum();

	// 当たり判定の値
	m_fRadius = pDataPlayer->GetRadius();
	m_fHeight = pDataPlayer->GetHeight();
	
	// キーカウント数
	m_nKeyCnt = 0;

	// モデルの動的確保
	m_apModel = new CModel*[m_nNumParts];
	m_aIndexParent = new int[m_nNumParts];
	m_aOffset = new float*[m_nNumParts];
	m_posMemo = new D3DXVECTOR3[m_nNumParts];
	m_rotMemo = new D3DXVECTOR3[m_nNumParts];

	m_bLand = true;
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// オブジェクトタイプ
	SetObjType(OBJTYPE_PLAYER);

	// パーツごとの設定
	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		// 親のインデックス情報の取得
		m_aIndexParent[nCnt] = pDataPlayer->GetParent(nCnt);

		// 各パラメータ分確保
		m_aOffset[nCnt] = new float[CTextDataPlayer::INFOMAX];

		for (int nCntOffset = 0; nCntOffset < CTextDataPlayer::INFOMAX; nCntOffset++)
		{
			// オフセット情報の取得
			m_aOffset[nCnt][nCntOffset] = pDataPlayer->GetOffset(nCnt, nCntOffset);
		}

		// Xファイル名取得
		char *pFileName = pDataPlayer->GetFileName(nCnt);

		// パーツごとのオフセット位置
		D3DXVECTOR3 pos = D3DXVECTOR3(
			m_aOffset[nCnt][CTextDataPlayer::INFO_POS_X],
			m_aOffset[nCnt][CTextDataPlayer::INFO_POS_Y], 
			m_aOffset[nCnt][CTextDataPlayer::INFO_POS_Z]);

		// パーツごとのオフセット角度
		D3DXVECTOR3 rot = D3DXVECTOR3(
			m_aOffset[nCnt][CTextDataPlayer::INFO_ROT_X],
			m_aOffset[nCnt][CTextDataPlayer::INFO_ROT_Y],
			m_aOffset[nCnt][CTextDataPlayer::INFO_ROT_Z]);

		// モデルの生成
		m_apModel[nCnt] = CModel::Create(pFileName, pos, rot);

		if (nCnt != 0)
		{
			m_apModel[nCnt]->SetParent(m_apModel[m_aIndexParent[nCnt]]);
		}		
	}

	// キー数ごと
	for (int nCntMotion = 0; nCntMotion < MOTIONTYPE_MAX; nCntMotion++)
	{
		m_nNumKey[nCntMotion] = pDataPlayer->GetNumKey((MOTIONTYPE)nCntMotion);

		// フレーム数のモーション毎の動的確保
		m_pFrame[nCntMotion] = new int[m_nNumKey[nCntMotion]];

		// キーフレーム情報のモーションごとの確保
		m_aKey[nCntMotion] = new float**[m_nNumKey[nCntMotion]];

		for (int nCntKey = 0; nCntKey < m_nNumKey[nCntMotion]; nCntKey++)
		{
			// フレーム数の取得
			m_pFrame[nCntMotion][nCntKey] = pDataPlayer->GetFrame((MOTIONTYPE)nCntMotion, nCntKey);
			
			// キーフレーム情報のキー数ごとの確保
			m_aKey[nCntMotion][nCntKey] = new float*[m_nNumParts];
			
			// パーツ数ごと
			for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
			{
				// キーフレーム情報のパーツごとの確保
				m_aKey[nCntMotion][nCntKey][nCntParts] = new float[KEY_MAX];

				// キー情報
				m_aKey[nCntMotion][nCntKey][nCntParts][KEY_POS_X] = pDataPlayer->GetKeyInfo((MOTIONTYPE)nCntMotion, nCntKey, nCntParts, KEY_POS_X);
				m_aKey[nCntMotion][nCntKey][nCntParts][KEY_POS_Y] = pDataPlayer->GetKeyInfo((MOTIONTYPE)nCntMotion, nCntKey, nCntParts, KEY_POS_Y);
				m_aKey[nCntMotion][nCntKey][nCntParts][KEY_POS_Z] = pDataPlayer->GetKeyInfo((MOTIONTYPE)nCntMotion, nCntKey, nCntParts, KEY_POS_Z);
				m_aKey[nCntMotion][nCntKey][nCntParts][KEY_ROT_X] = pDataPlayer->GetKeyInfo((MOTIONTYPE)nCntMotion, nCntKey, nCntParts, KEY_ROT_X);
				m_aKey[nCntMotion][nCntKey][nCntParts][KEY_ROT_Y] = pDataPlayer->GetKeyInfo((MOTIONTYPE)nCntMotion, nCntKey, nCntParts, KEY_ROT_Y);
				m_aKey[nCntMotion][nCntKey][nCntParts][KEY_ROT_Z] = pDataPlayer->GetKeyInfo((MOTIONTYPE)nCntMotion, nCntKey, nCntParts, KEY_ROT_Z);
			}
		}
	}

	// プレイヤーの位置・向きの設定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 影のサイズ設定
	D3DXVECTOR2 shadowSize = D3DXVECTOR2(15.0f,15.0f);

	// 影の設定
	m_pShadow = CShadow::Create(shadowSize);

	return S_OK;
}

//==============================================================================
// プレイヤーの終了処理
//==============================================================================
void CPlayer::Uninit(void)
{
	// モデル情報の破棄
	if (m_apModel != NULL)
	{
		delete m_apModel;
		m_apModel = NULL;
	}

	// 親情報の破棄
	if (m_aIndexParent != NULL)
	{
		delete m_aIndexParent;
		m_aIndexParent = NULL;
	}

	// 過去の位置情報の破棄
	if (m_posMemo != NULL)
	{
		delete m_posMemo;
		m_posMemo = NULL;
	}

	// 過去の向き情報情報の破棄
	if (m_rotMemo != NULL)
	{
		delete m_rotMemo;
		m_rotMemo = NULL;
	}

	// フレームの破棄
	for (int nCntMotion = 0; nCntMotion < MOTIONTYPE_MAX; nCntMotion++)
	{
		if (m_pFrame[nCntMotion] != NULL)
		{
			delete m_pFrame[nCntMotion];
			m_pFrame[nCntMotion] = NULL;
		}
	}

	// オフセット情報の破棄
	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_aOffset[nCnt] != NULL)
		{
			delete[] m_aOffset[nCnt];
		}
	}
	if (m_aOffset != NULL)
	{
		delete m_aOffset;
		m_aOffset = NULL;
	}

	// キー情報の破棄
	for (int nCntMotion = 0; nCntMotion < MOTIONTYPE_MAX; nCntMotion++)
	{
		if (m_aKey[nCntMotion] != NULL)
		{
			for (int nCntKey = 0; nCntKey < m_nNumKey[nCntMotion]; nCntKey++)
			{
				for (int nCntParts = 0; nCntParts < KEY_MAX; nCntParts++)
				{
					delete[] m_aKey[nCntMotion][nCntKey][nCntParts];
				}

				delete[] m_aKey[nCntMotion][nCntKey];
			}

			delete[] m_aKey[nCntMotion];
			m_aKey[nCntMotion] = NULL;
		}
	}
}

//==============================================================================
// プレイヤーの更新処理
//==============================================================================
void CPlayer::Update(void)
{
	// キーボードの取得
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// ゲームパッドの取得
	CGamepad *gamepad = CManager::GetInputGamepad();

	// 移動処理
	MovePlayer();

	// デバッグ用モーション管理
	if (keyboard->GetTrigger(CInput::KEYINFO_MINUS_MOTION) == true)
	{
		m_motionType = (MOTIONTYPE)(m_motionType - 1);

		if (m_motionType < 0)
		{
			// 項目の1周
			m_motionType = (MOTIONTYPE)(MOTIONTYPE_MAX - 1);
		}
	}

	if (keyboard->GetTrigger(CInput::KEYINFO_PLUS_MOTION) == true)
	{
		m_motionType = (MOTIONTYPE)(m_motionType + 1);

		if (m_motionType == MOTIONTYPE_MAX)
		{
			// 項目の1周
			m_motionType = (MOTIONTYPE)0;
		}
	}

	// モーションの更新(試用ニュートラル)
	UpdateMotion(m_motionType);

	// 影の追従
	if (m_pShadow != NULL)
	{
		CCollision *pCollision;
		pCollision = CManager::GetCollision();

		if (pCollision->GetOnObject() == false)
		{
			m_pShadow->SetPosition(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z));
		}		
	}

	// 位置の更新
	SetPosition(m_pos);
	SetRotation(m_rot);
}

//==============================================================================
// プレイヤーの描画処理
//==============================================================================
void CPlayer::Draw(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;										// 計算用マトリックス
	D3DMATERIAL9 matDef;												// 現在のマテリアル保存用

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// モデルの描画
	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Draw();
		}
	}
}

//==============================================================================
// 生成処理
//==============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	// ローカル変数宣言
	CPlayer *pPlayer;
	pPlayer = new CPlayer;	// インスタンス

	// 初期化
	if (pPlayer != NULL)
	{
		pPlayer->Init();
		pPlayer->SetPosition(pos);
	}

	return pPlayer;
}

//==============================================================================
// モーションの更新
//==============================================================================
void CPlayer::UpdateMotion(MOTIONTYPE motionType)
{
	// テキストデータの取得
	CTextDataPlayer *pDataPlayer = CTextDataPlayer::GetDataPlayer();

	// ブレンド用フレーム数
	int nBlendFrame = 10;

	// モーション変化によるカウントの初期化
	if (m_motionTypeOld != motionType)
	{
		m_nKeyCnt = 0;
		m_nFrameCnt = 0;
		m_bBlendMotion = true;
	}

	// ループ情報
	m_bLoop = pDataPlayer->GetLoop(motionType);

	// フレームのカウント
	if (m_nFrameCnt < m_pFrame[motionType][m_nKeyCnt] || motionType != MOTIONTYPE_JUMP) 
	{
		m_nFrameCnt++;
	}

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		// 位置・角度の取得
		D3DXVECTOR3 pos = m_apModel[nCnt]->GetPosition();
		D3DXVECTOR3 rot = m_apModel[nCnt]->GetRotation();

		if (m_bLoop == true && m_nKeyCnt == m_nNumKey[motionType] - 1)
		{// ループするときの折り返し
			pos.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X] + (m_aKey[motionType][0][nCnt][KEY_POS_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			pos.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y] + (m_aKey[motionType][0][nCnt][KEY_POS_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			pos.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z] + (m_aKey[motionType][0][nCnt][KEY_POS_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			rot.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X] + (m_aKey[motionType][0][nCnt][KEY_ROT_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			rot.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y] + (m_aKey[motionType][0][nCnt][KEY_ROT_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			rot.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z] + (m_aKey[motionType][0][nCnt][KEY_ROT_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);			
			m_posMemo[nCnt] = pos;
			m_rotMemo[nCnt] = rot;
		}
		else if (m_bLoop == false && m_nKeyCnt == m_nNumKey[motionType] - 1)
		{// ループせず終了する時
			if (motionType == MOTIONTYPE_LANDING)
			{// ニュートラルへ
				pos.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X] + (m_aKey[MOTIONTYPE_NEUTRAL][0][nCnt][KEY_POS_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
				pos.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y] + (m_aKey[MOTIONTYPE_NEUTRAL][0][nCnt][KEY_POS_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
				pos.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z] + (m_aKey[MOTIONTYPE_NEUTRAL][0][nCnt][KEY_POS_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
				rot.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X] + (m_aKey[MOTIONTYPE_NEUTRAL][0][nCnt][KEY_ROT_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
				rot.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y] + (m_aKey[MOTIONTYPE_NEUTRAL][0][nCnt][KEY_ROT_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
				rot.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z] + (m_aKey[MOTIONTYPE_NEUTRAL][0][nCnt][KEY_ROT_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
				m_posMemo[nCnt] = pos;
				m_rotMemo[nCnt] = rot;
			}
			//else if (motionType == MOTIONTYPE_DAMAGE)
			//{// 着地へ
			//	pos.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X] + (m_aKey[MOTIONTYPE_STEP][0][nCnt][KEY_POS_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			//	pos.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y] + (m_aKey[MOTIONTYPE_STEP][0][nCnt][KEY_POS_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			//	pos.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z] + (m_aKey[MOTIONTYPE_STEP][0][nCnt][KEY_POS_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			//	rot.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X] + (m_aKey[MOTIONTYPE_STEP][0][nCnt][KEY_ROT_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			//	rot.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y] + (m_aKey[MOTIONTYPE_STEP][0][nCnt][KEY_ROT_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			//	rot.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z] + (m_aKey[MOTIONTYPE_STEP][0][nCnt][KEY_ROT_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			//	m_posMemo[nCnt] = pos;
			//	m_rotMemo[nCnt] = rot;
			//}
		}
		else if (m_bBlendMotion == true)
		{// モーションが途中で切り替わる(モーションブレンド)
			pos.x = m_posMemo[nCnt].x + (m_aKey[motionType][0][nCnt][KEY_POS_X] - m_posMemo[nCnt].x) * ((float)m_nFrameCnt / (float)nBlendFrame);
			pos.y = m_posMemo[nCnt].y + (m_aKey[motionType][0][nCnt][KEY_POS_Y] - m_posMemo[nCnt].y) * ((float)m_nFrameCnt / (float)nBlendFrame);
			pos.z = m_posMemo[nCnt].z + (m_aKey[motionType][0][nCnt][KEY_POS_Z] - m_posMemo[nCnt].z) * ((float)m_nFrameCnt / (float)nBlendFrame);
			rot.x = m_rotMemo[nCnt].x + (m_aKey[motionType][0][nCnt][KEY_ROT_X] - m_rotMemo[nCnt].x) * ((float)m_nFrameCnt / (float)nBlendFrame);
			rot.y = m_rotMemo[nCnt].y + (m_aKey[motionType][0][nCnt][KEY_ROT_Y] - m_rotMemo[nCnt].y) * ((float)m_nFrameCnt / (float)nBlendFrame);
			rot.z = m_rotMemo[nCnt].z + (m_aKey[motionType][0][nCnt][KEY_ROT_Z] - m_rotMemo[nCnt].z) * ((float)m_nFrameCnt / (float)nBlendFrame);
		}
		else
		{// 通常時の再生
			pos.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X] + (m_aKey[motionType][m_nKeyCnt + 1][nCnt][KEY_POS_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			pos.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y] + (m_aKey[motionType][m_nKeyCnt + 1][nCnt][KEY_POS_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			pos.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z] + (m_aKey[motionType][m_nKeyCnt + 1][nCnt][KEY_POS_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_POS_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			rot.x = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X] + (m_aKey[motionType][m_nKeyCnt + 1][nCnt][KEY_ROT_X] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_X]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			rot.y = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y] + (m_aKey[motionType][m_nKeyCnt + 1][nCnt][KEY_ROT_Y] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Y]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			rot.z = m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z] + (m_aKey[motionType][m_nKeyCnt + 1][nCnt][KEY_ROT_Z] - m_aKey[motionType][m_nKeyCnt][nCnt][KEY_ROT_Z]) * ((float)m_nFrameCnt / (float)m_pFrame[motionType][m_nKeyCnt]);
			m_posMemo[nCnt] = pos;
			m_rotMemo[nCnt] = rot;
		}

		// 位置・角度の反映
		m_apModel[nCnt]->SetPosition(pos);
		m_apModel[nCnt]->SetRotation(rot);
	}

	// モーションの変わり目
	if (m_bBlendMotion == false)
	{
		if (m_nFrameCnt >= m_pFrame[motionType][m_nKeyCnt] && motionType != MOTIONTYPE_JUMP)
		{
			m_nFrameCnt = 0;

			if (m_nKeyCnt < m_nNumKey[motionType] - 1)
			{// カウントの加算
				m_nKeyCnt++;
			}
			else
			{// カウントのリセット
				if (m_bLoop == false)
				{
					if (motionType == MOTIONTYPE_LANDING)
					{// アクション、着地の次
						m_motionType = MOTIONTYPE_NEUTRAL;
					}
				}
				else
				{
					m_nKeyCnt = 0;
				}
			}
		}
	}
	else
	{// ブレンド時
		if (m_nFrameCnt >= nBlendFrame)
		{
			m_nFrameCnt = 0;
			m_nKeyCnt = 0;

			// ブレンドの終了
			m_bBlendMotion = false;
		}
	}

	// 旧モーションの保存
	m_motionTypeOld = motionType;
}

//==============================================================================
// 挙動処理
//==============================================================================
void CPlayer::MovePlayer(void)
{
	// キーボードの取得
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// ゲームパッドの取得
	CGamepad *gamepad = CManager::GetInputGamepad();

	// カメラの取得
	CCamera *pCamera = CManager::GetCamera();

	// カメラの方向
	D3DXVECTOR3 rotCamera = pCamera->GetRotation();



	// メッシュ
	CTerrain *pTerrain = CGame::GetTerrain();

	// メッシュとの当たり判定
	if (pTerrain != NULL)
	{
		if (pTerrain->FallCollider(this) == true && m_bLand == false)
		{
			m_pos.y = 0;
			m_bLand = true;
		}
	}

	// 他オブジェクトとの当たり判定
	CCollision *pCollision;
	pCollision = CManager::GetCollision();

	if (pCollision != NULL)
	{
		CTextDataObject *pDataObject;
		pDataObject = CTextData::GetDataObject();

		int nNumObject = pDataObject->GetNumObject();

		for (int nCntObject = 0; nCntObject < nNumObject; nCntObject++)
		{
			CModel *pModel = CGame::GetPointObject(nCntObject)->GetModel();

			if (pCollision->Collision3D(this, pModel) == true && m_bLand == false)
			{
				m_bLand = true;
			}
		}
	}

	// 過去位置の更新
	m_posOld = m_pos;

	// 重力の発生
	if (m_pos.y > 0.0f && m_bLand == false)
	{
		m_move.y -= GRAVITY_SCALE;
	}

	// プレイヤーの着地判定
	if (m_bLand == false)
	{
		//if (m_pos.y < 0.0f)
		//{// 最も低い位置
		//	m_bLand = true;
		//	//m_nKeyCnt = 0;
		//	//m_nFrameCnt = 0;
		//}
	}
	else if (m_bLand == true)
	{// 着地状態
		//if (m_pos.y < 0.0f)
		//{
		//	m_pos.y = 0.0f;
		//}

		if (m_bJump == true)
		{
			if (m_motionType == MOTIONTYPE_JUMP || m_motionType == MOTIONTYPE_RUN)
			{
				m_motionType = MOTIONTYPE_LANDING;
			}
		}

		m_bJump = false;
		m_move.y = 0.0f;
	}

	// ジャンプ：着地している
	if (keyboard->GetTrigger(CInput::KEYINFO_JUMP) == true ||
		gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		if (m_bLand == true)
		{
			m_nKeyCnt = 0;
			m_nFrameCnt = 0;
			m_motionType = MOTIONTYPE_JUMP;
		}

		m_bLand = false;
	}
	if (keyboard->GetPress(CInput::KEYINFO_JUMP) == true ||
		gamepad->GetPress(CInput::KEYINFO_OK) == true)
	{
		if (m_bJump == false)
		{
			if (m_nJumpCnt == 1)
			{
				m_move.y = 5.0f;
			}
			if (m_nJumpCnt < 9)
			{// 限界値
				m_nJumpCnt++;
				m_move.y += 1.0f;
			}
		}
	}
	if (keyboard->GetRelease(CInput::KEYINFO_JUMP) == true ||
		gamepad->GetRelease(CInput::KEYINFO_OK) == true)
	{
		m_nJumpCnt = 0;
		m_bJump = true;
	}

	// 移動
	m_pos += m_move;

	// 移動処理
	// 歩く
	if (keyboard->GetPress(CInput::KEYINFO_WALK_UP) == true ||
		keyboard->GetPress(CInput::KEYINFO_WALK_DOWN) == true ||
		keyboard->GetPress(CInput::KEYINFO_WALK_LEFT) == true ||
		keyboard->GetPress(CInput::KEYINFO_WALK_RIGHT) == true ||
		gamepad->GetPress(CInput::KEYINFO_WALK_UP) == true ||
		gamepad->GetPress(CInput::KEYINFO_WALK_DOWN) == true ||
		gamepad->GetPress(CInput::KEYINFO_WALK_LEFT) == true ||
		gamepad->GetPress(CInput::KEYINFO_WALK_RIGHT) == true)
	{
		if (keyboard->GetPress(CInput::KEYINFO_WALK_UP) == true ||
			gamepad->GetPress(CInput::KEYINFO_WALK_UP) == true)
		{// 上方向
			if (keyboard->GetPress(CInput::KEYINFO_WALK_LEFT) == true ||
				gamepad->GetPress(CInput::KEYINFO_WALK_LEFT) == true)
			{// 左上方向
				m_move.x -= cosf(rotCamera.y + D3DX_PI / 4) * WALK_SPEED;
				m_move.z += sinf(rotCamera.y + D3DX_PI / 4) * WALK_SPEED;
				m_rotDest.y = rotCamera.y + (D3DX_PI * 3 / 4);
			}
			else if (keyboard->GetPress(CInput::KEYINFO_WALK_RIGHT) == true ||
				gamepad->GetPress(CInput::KEYINFO_WALK_RIGHT) == true)
			{// 右上方向
				m_move.x += cosf(rotCamera.y - D3DX_PI / 4) * WALK_SPEED;
				m_move.z -= sinf(rotCamera.y - D3DX_PI / 4) * WALK_SPEED;
				m_rotDest.y = rotCamera.y - (D3DX_PI * 3 / 4);
			}
			else
			{// 上方向
				m_move.x += sinf(rotCamera.y) * WALK_SPEED;
				m_move.z += cosf(rotCamera.y) * WALK_SPEED;
				m_rotDest.y = rotCamera.y + D3DX_PI;
			}
		}
		else if (keyboard->GetPress(CInput::KEYINFO_WALK_DOWN) == true ||
			gamepad->GetPress(CInput::KEYINFO_WALK_DOWN) == true)
		{
			if (keyboard->GetPress(CInput::KEYINFO_WALK_LEFT) == true ||
				gamepad->GetPress(CInput::KEYINFO_WALK_LEFT) == true)
			{// 左下方向
				m_move.x += cosf(rotCamera.y + D3DX_PI * 3 / 4) * WALK_SPEED;
				m_move.z -= sinf(rotCamera.y + D3DX_PI * 3 / 4) * WALK_SPEED;
				m_rotDest.y = rotCamera.y + D3DX_PI / 4;
			}
			else if (keyboard->GetPress(CInput::KEYINFO_WALK_RIGHT) == true ||
				gamepad->GetPress(CInput::KEYINFO_WALK_RIGHT) == true)
			{// 右下方向
				m_move.x -= cosf(rotCamera.y - D3DX_PI * 3 / 4) * WALK_SPEED;
				m_move.z += sinf(rotCamera.y - D3DX_PI * 3 / 4) * WALK_SPEED;
				m_rotDest.y = rotCamera.y + D3DX_PI / -4;
			}
			else
			{// 下方向
				m_move.x += sinf(rotCamera.y - D3DX_PI) * WALK_SPEED;
				m_move.z += cosf(rotCamera.y - D3DX_PI) * WALK_SPEED;
				m_rotDest.y = rotCamera.y;
			}
		}
		else if (keyboard->GetPress(CInput::KEYINFO_WALK_LEFT) == true ||
			gamepad->GetPress(CInput::KEYINFO_WALK_LEFT) == true)
		{
			m_move.x -= cosf(rotCamera.y) * WALK_SPEED;
			m_move.z += sinf(rotCamera.y) * WALK_SPEED;
			m_rotDest.y = rotCamera.y + (D3DX_PI / 2);
		}
		else if (keyboard->GetPress(CInput::KEYINFO_WALK_RIGHT) == true ||
			gamepad->GetPress(CInput::KEYINFO_WALK_RIGHT) == true)
		{
			m_move.x += cosf(rotCamera.y) * WALK_SPEED;
			m_move.z -= sinf(rotCamera.y) * WALK_SPEED;
			m_rotDest.y = rotCamera.y + (D3DX_PI / -2);
		}
	}

	// 走る
	if (keyboard->GetPress(CInput::KEYINFO_UP) == true ||
		keyboard->GetPress(CInput::KEYINFO_DOWN) == true ||
		keyboard->GetPress(CInput::KEYINFO_LEFT) == true ||
		keyboard->GetPress(CInput::KEYINFO_RIGHT) == true ||
		gamepad->GetPress(CInput::KEYINFO_UP) == true ||
		gamepad->GetPress(CInput::KEYINFO_DOWN) == true ||
		gamepad->GetPress(CInput::KEYINFO_LEFT) == true ||
		gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
	{
		m_nDashCnt++;

		if (keyboard->GetPress(CInput::KEYINFO_UP) == true ||
			gamepad->GetPress(CInput::KEYINFO_UP) == true)
		{// 上方向
			if (keyboard->GetPress(CInput::KEYINFO_LEFT) == true ||
				gamepad->GetPress(CInput::KEYINFO_LEFT) == true)
			{// 左上方向
				m_move.x -= cosf(rotCamera.y + D3DX_PI / 4) * m_fDashPower;
				m_move.z += sinf(rotCamera.y + D3DX_PI / 4) * m_fDashPower;
				m_rotDest.y = rotCamera.y + (D3DX_PI * 3 / 4);
			}
			else if (keyboard->GetPress(CInput::KEYINFO_RIGHT) == true ||
				gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
			{// 右上方向
				m_move.x += cosf(rotCamera.y - D3DX_PI / 4) * m_fDashPower;
				m_move.z -= sinf(rotCamera.y - D3DX_PI / 4) * m_fDashPower;
				m_rotDest.y = rotCamera.y - (D3DX_PI * 3 / 4);
			}
			else
			{// 上方向
				m_move.x += sinf(rotCamera.y) * m_fDashPower;
				m_move.z += cosf(rotCamera.y) * m_fDashPower;
				m_rotDest.y = rotCamera.y + D3DX_PI;
			}
		}
		else if (keyboard->GetPress(CInput::KEYINFO_DOWN) == true ||
			gamepad->GetPress(CInput::KEYINFO_DOWN) == true)
		{
			if (keyboard->GetPress(CInput::KEYINFO_LEFT) == true ||
				gamepad->GetPress(CInput::KEYINFO_LEFT) == true)
			{// 左下方向
				m_move.x += cosf(rotCamera.y + D3DX_PI * 3 / 4) * m_fDashPower;
				m_move.z -= sinf(rotCamera.y + D3DX_PI * 3 / 4) * m_fDashPower;
				m_rotDest.y = rotCamera.y + D3DX_PI / 4;
			}
			else if (keyboard->GetPress(CInput::KEYINFO_RIGHT) == true ||
				gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
			{// 右下方向
				m_move.x -= cosf(rotCamera.y - D3DX_PI * 3 / 4) * m_fDashPower;
				m_move.z += sinf(rotCamera.y - D3DX_PI * 3 / 4) * m_fDashPower;
				m_rotDest.y = rotCamera.y + D3DX_PI / -4;
			}
			else
			{// 下方向
				m_move.x += sinf(rotCamera.y - D3DX_PI) * m_fDashPower;
				m_move.z += cosf(rotCamera.y - D3DX_PI) * m_fDashPower;
				m_rotDest.y = rotCamera.y;
			}
		}
		else if (keyboard->GetPress(CInput::KEYINFO_LEFT) == true ||
			gamepad->GetPress(CInput::KEYINFO_LEFT) == true)
		{
			m_move.x -= cosf(rotCamera.y) * m_fDashPower;
			m_move.z += sinf(rotCamera.y) * m_fDashPower;
			m_rotDest.y = rotCamera.y + (D3DX_PI / 2);
		}
		else if (keyboard->GetPress(CInput::KEYINFO_RIGHT) == true ||
			gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
		{
			m_move.x += cosf(rotCamera.y) * m_fDashPower;
			m_move.z -= sinf(rotCamera.y) * m_fDashPower;
			m_rotDest.y = rotCamera.y + (D3DX_PI / -2);
		}
	}
	else
	{
		m_nDashCnt = 0;
		m_fDashPower = 0.0f;
	}

	if (m_nDashCnt < 60)
	{
		m_fDashPower = 1.0f;
	}
	else if (m_nDashCnt < 120)
	{
		m_fDashPower = 1.5f;
	}
	else
	{
		m_fDashPower = 2.0f;
	}

	// 目的の回転角の上限
	if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2.0f;
	}
	else if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2.0f;
	}

	// 向きの更新
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;

	// 現在の回転角の上限
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	// 加速後の減速処理
	m_move.x += (0.0f - m_move.x) * SPEED_DOWN;
	m_move.z += (0.0f - m_move.z) * SPEED_DOWN;

	// モーションの切り替え
	if (m_move.x > MOVE_MOTION || m_move.z > MOVE_MOTION || m_move.x < -MOVE_MOTION || m_move.z < -MOVE_MOTION)
	{// 移動力でモーションを維持
		if (m_bLand == true)
		{// 地上にいる時
			if (m_move.x > RUN_MOTION || m_move.z > RUN_MOTION || m_move.x < -RUN_MOTION || m_move.z < -RUN_MOTION)
			{
				// 走るモーション
				SetMotion(MOTIONTYPE_RUN);
			}
			else
			{
				// 歩くモーション
				SetMotion(MOTIONTYPE_WALK);
			}		
		}		
	}
	else if(m_motionType == MOTIONTYPE_RUN || m_motionType == MOTIONTYPE_WALK)
	{
		SetMotion(MOTIONTYPE_NEUTRAL);
	}
}