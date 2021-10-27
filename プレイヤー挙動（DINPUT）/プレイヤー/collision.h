//=============================================================================
//
// “–‚½‚è”»’èŠÇ— [collision.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"
#include "model.h"
#include "player.h"

//==============================================================================
// “–‚½‚è”»’èŠÇ—ƒNƒ‰ƒX
//==============================================================================
class CCollision
{
public:

	CCollision();
	~CCollision();

	static CCollision *Create(void);

	// 3Dƒ‚ƒfƒ‹ŠÔ‚Ì“–‚½‚è”»’è
	bool Collision3D(CPlayer *pPlayer, CModel *pObject);

	bool GetCollisionBool(void) { return m_bCollision; }

private:
	bool m_bCollision;			// G‚ê‚Ä‚¢‚é”»’è
};

#endif