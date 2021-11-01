//=============================================================================
//
// �I�u�W�F�N�g�N���X [scene.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// �w�b�_�[�̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "Renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCENE_PRIORITY_MAX (5)
#define SCENE_PRIORITY_DEFAULT (3)

//*****************************************************************************
// �I�u�W�F�N�g�N���X (����)
//*****************************************************************************
class CScene
{
public:
	// �I�u�W�F�N�g�̎��
	typedef enum {
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_SCAFFOLD,

		OBJTYPE_MAX,
	} OBJTYPE;

	CScene(int nPriority = SCENE_PRIORITY_DEFAULT);
	virtual ~CScene();

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	// SET
	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	virtual void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetPriority(int nPriority);
	void SetObjType(OBJTYPE type) { m_objType = type; }

	// GET
	virtual D3DXVECTOR3 GetPos(void) { return m_pos; }
	virtual D3DXVECTOR3 GetRot(void) { return m_rot; }
	virtual D3DXVECTOR3 GetSize(void) { return m_size; }
	OBJTYPE GetObjType(void) { return m_objType; }
	int GetPriority(void) { return m_nPriority; }

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static vector<CScene*> *CScene::GetSceneList(int nPriority);

protected:
	void Release(void);		// Scene2D��Uninit����ĂԂ���protected

private:
	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_size;						// �T�C�Y
	int m_nPriority;						// �D�揇�ʂ̔ԍ�
	OBJTYPE m_objType;						// �I�u�W�F�N�g�̎��

	static vector<CScene*> m_aSceneVc[SCENE_PRIORITY_MAX];	// �V�[���̃��X�g
	static int m_nNumAll;									// �S�̂̐�����
};

#endif
