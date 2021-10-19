//=============================================================================
//
// 3D���f���̐ݒ� [sceneX.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include "main.h"
#include "scene3D.h"

//==============================================================================
// SceneX�N���X
//==============================================================================
class CSceneX : public CScene3D
{
public:
	typedef enum
	{
		X_TYPE_METEOR = 0,	// 覐΃��f��
		X_TYPE_DEBRI_0,		// �F���S�~0
		X_TYPE_DEBRI_1,		// �F���S�~1
		X_TYPE_MAX
	}X_TYPE;

	CSceneX(int nPriority = PRIORITY_BG);
	~CSceneX();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rotMove,int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSceneX *Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR3 rotMove,int nType);

private:
	D3DXVECTOR3 m_move;				// �ړ���
	D3DXVECTOR3 m_rotMove;			// ��]��
	LPD3DXMESH m_pMesh;				// ���b�V���|�C���^
	LPD3DXBUFFER m_pBuffMat;		// �}�e���A���o�b�t�@
	DWORD m_nNumMat;				// �}�e���A����
	D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 *m_pTexture;	// �e�N�X�`���_�u���|�C���^
	//LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`�����
	X_TYPE m_type;					// ���
};
#endif