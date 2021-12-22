//=============================================================================
//
// �I�u�W�F�N�g�`�揈�� [scene.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

// �O��
class CScene2D;
class CSound;

//=============================================================================
// �}�N����`
//=============================================================================
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// ���_�t�H�[�}�b�g
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//==============================================================================
// ���_�t�H�[�}�b�g�ɍ��킹���\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// 1.0�ŌŒ�
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_3D;

//==============================================================================
// �I�u�W�F�N�g�N���X
//==============================================================================
class CScene
{
public:
	// �I�u�W�F�N�g�̎��
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BG,			// �w�i
		OBJTYPE_PLAYER,		// �v���C���[
		OBJTYPE_OBJECT,		// �I�u�W�F�N�g
		OBJTYPE_BULLET,		// �e
		OBJTYPE_ITEM,		// �A�C�e��
		OBJTYPE_EXPLOSION,	// ����
		OBJTYPE_EFFECT,		// �G�t�F�N�g
		OBJTYPE_UI,			// UI�n
		OBJTYPE_MAX
	}OBJTYPE;

	// �`��D�揇��
	typedef enum
	{
		PRIORITY_BG = 0,	// �w�i
		PRIORITY_CHARA,		// �L�����N�^�[
		PRIORITY_DEFAULT,	// �f�t�H���g�l
		PRIORITY_ITEM,		// �A�C�e��
		PRIORITY_EXPLOSION,	// ����
		PRIORITY_UI,		// UI
		PRIORITY_EFFECT,	// �G�t�F�N�g		
		PRIORITY_PAUSE,		// �|�[�Y
		PRIORITY_SHADOW,	// �ۉe
		PRIORITY_EFFECT_ON,	// �G�t�F�N�g
		PRIORITY_MAX
	}Priority;

	CScene(int nPriority = PRIORITY_DEFAULT);
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	// �I�u�W�F�N�g��ސݒ�
	OBJTYPE GetObjType(void) { return m_objType; }
	void SetObjType(OBJTYPE objType) { m_objType = objType; }

	// �V�[���̎擾
	static CScene *GetScene(int nPriority) { return m_pTop[nPriority]; }
	static CScene *GetSceneNext(CScene *pScene) { return pScene->m_pNext; }
	
	// ���擾
	virtual D3DXVECTOR3 GetPosition(void) { return m_pos; }
	virtual D3DXVECTOR3 GetRotation(void) { return m_rot; }

	// ���ݒ�
	virtual void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	// �I�u�W�F�N�g�����̎擾
	static int GetNumAll(void) { return m_nNumAll; }

protected:
	// ���S�t���O�̐���
	void Release(void) { this->m_bDeath = true; }
	CSound *m_pSound;

private:
	static CScene *m_pTop[PRIORITY_MAX];	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene *m_pCur[PRIORITY_MAX];	// ����(�Ō��)�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pPrev;						// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext;						// ���̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeath;							// ���S�t���O

	static int m_nNumAll;					// ������
	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_rot;						// �p�x
	OBJTYPE m_objType;						// �I�u�W�F�N�g�̎��
};

#endif