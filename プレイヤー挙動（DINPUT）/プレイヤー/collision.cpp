//==============================================================================
//
// 当たり判定管理〔collision.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"
#include "shadow.h" 

//==============================================================================
// コンストラクタ
//==============================================================================
CCollision::CCollision()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CCollision::~CCollision()
{

}

//==============================================================================
// 当たり判定ポインタの生成
//==============================================================================
CCollision *CCollision::Create(void)
{
	// 当たり判定
	CCollision *pCollision;
	pCollision = new CCollision;

	return pCollision;
}

//==============================================================================
// 3Dモデル間の当たり判定処理
//==============================================================================
bool CCollision::Collision3D(CPlayer *pPlayer, CModel *pObject)
{
	// ローカル変数宣言
	D3DXVECTOR3 aVec[4];							// 矩形頂点から判定対象へのベクトル
	D3DXVECTOR3 posPlayer = pPlayer->GetPosition();	// 判定対象の位置
	D3DXVECTOR3 posOld = pPlayer->GetPosOld();		// プレイヤーの過去の位置
	float fRadius = pPlayer->GetRadius();			// プレイヤー半径の取得
	float fHeight = pPlayer->GetHeight();			// プレイヤー高さの取得
	CShadow *pShadow = pPlayer->GetShadow();		// プレイヤーの影

	D3DXVECTOR3 posObject = pObject->GetPosition();	// オブジェクトの位置
	D3DXVECTOR3 vtxMin = pObject->GetVtxMin();		// オブジェクト6方の最小値
	D3DXVECTOR3 vtxMax = pObject->GetVtxMax();		// オブジェクト6方の最大値

	float fPlayerVec[COLLISION_NUM];				// プレイヤーへのベクトル数値

	m_bCollision = false;

	// オブジェクトとの当たり判定
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		// ローカル変数宣言
		D3DXVECTOR3 posVtx = pObject->GetPosVtx(nCnt);
		D3DXVECTOR3 vecVtx = pObject->GetVecVtx(nCnt);

		if (nCnt == 0)
		{// 左面
			aVec[nCnt] = posPlayer + D3DXVECTOR3(fRadius, 0.0f, 0.0f) - posVtx;
		}
		else if (nCnt == 1)
		{// 奥側
			aVec[nCnt] = posPlayer + D3DXVECTOR3(0.0f, 0.0f, -fRadius) - posVtx;
		}
		else if (nCnt == 2)
		{// 右面
			aVec[nCnt] = posPlayer + D3DXVECTOR3(-fRadius, 0.0f, 0.0f) - posVtx;
		}
		else if (nCnt == 3)
		{// 手前
			aVec[nCnt] = posPlayer + D3DXVECTOR3(0.0f, 0.0f, fRadius) - posVtx;
		}

		// 数値が「+」の時、当たり判定が有効
		fPlayerVec[nCnt] = (vecVtx.z * aVec[nCnt].x) - (vecVtx.x * aVec[nCnt].z);
	}

	// 当たり判定
	if (fPlayerVec[0] > 0.0f && fPlayerVec[1] > 0.0f && fPlayerVec[2] > 0.0f && fPlayerVec[3] > 0.0f)
	{// 算出したベクトルの範囲内判定
		if (posPlayer.y >= posObject.y + vtxMax.y)
		{
			// 影の反映
			pShadow->SetPosition(D3DXVECTOR3(posPlayer.x, posObject.y + vtxMax.y + 1.0f, posPlayer.z));
			m_bCollision = true;
		}
		
		if (posPlayer.y <= (posObject.y + vtxMax.y) && posPlayer.y > posObject.y + vtxMin.y - fHeight)
		{
			if (posPlayer.y <= (posObject.y + vtxMax.y) && posOld.y >= posObject.y + vtxMax.y)
			{// 上側
				if (posPlayer.y < posObject.y + vtxMax.y)
				{
					pPlayer->SetLanding(true);
				}

				m_bCollision = true;

				// 位置の反映
				posPlayer.y = posObject.y + vtxMax.y;	
			}
			else if (posPlayer.y + fHeight > posObject.y + vtxMin.y)
			{// 下側
				posPlayer.y = posObject.y + vtxMin.y - fHeight;
				
			}
			else if (posPlayer.x > posOld.x && posOld.x < posObject.x + vtxMin.x)
			{// 左側	
				posPlayer.x = posObject.x + vtxMin.x - fRadius;
			}
			else if (posPlayer.x < posOld.x && posOld.x > posObject.x + vtxMax.x)
			{// 右側	
				posPlayer.x = posObject.x + vtxMax.x + fRadius;
			}
			else if (posPlayer.z <= posOld.z && posPlayer.z > posObject.z)
			{// 奥側
				posPlayer.z = posObject.z + vtxMax.z + fRadius;
			}
			else if (posPlayer.z >= posOld.z && posPlayer.z < posObject.z)
			{// 手前
				posPlayer.z = posObject.z + vtxMin.z - fRadius;
			}
		}

		// 位置の反映
		pPlayer->SetPosition(posPlayer);
	}
	else
	{
		if (posPlayer.y <= (posObject.y + vtxMax.y) && posOld.y >= posObject.y + vtxMax.y)
		{// 乗っていた場合
			pPlayer->SetLanding(false);
		}

		m_bCollision = false;
	}

	return m_bCollision;
}