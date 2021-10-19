
//=============================================================================
//
// �r���{�[�h�̐ݒ� [sceneBillboard.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _SCENEBILLBOARD_H_
#define _SCENEBILLBOARD_H_

#include "main.h"
#include "scene.h"

//==============================================================================
// �r���{�[�h�V�[���N���X
//==============================================================================
class CSceneBillboard : public CScene
{
public:
	CSceneBillboard(int nPriority = PRIORITY_DEFAULT);
	~CSceneBillboard();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSceneBillboard *Create(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetRot(void) { return m_rot; }

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

private:
	D3DXVECTOR3 m_pos;								// �ʒu
	D3DXVECTOR3 m_rot;								// ����
	D3DXVECTOR2 m_size;								// �傫��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// �o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;							// ���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^
};
#endif